//
// Part of Metta OS. Check http://metta.exquance.com for latest version.
//
// Copyright 2007 - 2011, Stanislav Karchebnyy <berkus@exquance.com>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Kernel startup initialisation.
//
#include "config.h"

#include "default_console.h"
#include "bootinfo.h"
#include "bootimage.h"
#include "infopage.h"
#include "frames_module_v1_interface.h"
#include "timer_v1_interface.h"
#include "continuation.h"
#include "cpu.h"
#include "c++ctors.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "root_domain.h"
#include "registers.h"
#include "new.h"
#include "debugger.h"

static void parse_cmdline(bootinfo_t* bi)
{
    const char* cmdline;

    if (bi->get_cmdline(cmdline))
    {
        kconsole << "Command line is: " << cmdline << endl;

        // supported cmdline params:
        // "debug"
        // "noapic"
        // "maxmem="

/*#define PARSENUM(name, var, msg, massage...)            \
        if ((p = strstr(mbi->cmdline, name"=")) != NULL)    \
        {                           \
            var = strtoul(p+strlen(name)+1, &p, 10);        \
            if (*p == 'K') var*=1024;               \
            if (*p == 'M') var*=1024*1024;          \
            if (*p == 'G') var*=1024*1024*1024;         \
            massage;                        \
            printf(msg,                     \
                   var >= 1<<30 ? var>>30 :         \
                   var >= 1<<20 ? var>>20 :         \
                   var >= 1<<10 ? var>>10 : var,        \
                   var >= 1<<30 ? "G" :             \
                   var >= 1<<20 ? "M" :             \
                   var >= 1<<10 ? "K" : "");            \
        }*/

/*#define PARSEBOOL(name, var, msg)               \
    if ((p = strstr (mbi->cmdline, name"=")) != NULL)   \
    {                           \
        p = strchr (p, '=') + 1;                \
        if (strncmp (p, "yes", 3) == 0 ||           \
        strncmp (p, "on", 2) == 0 ||            \
        strncmp (p, "enable", 6) == 0)          \
        {                           \
        if (! var) printf ("Enabling %s\n", msg);   \
        var = true;                 \
        }                           \
        else if (strncmp (p, "no", 2) == 0 ||       \
             strncmp (p, "off", 3) == 0 ||      \
             strncmp (p, "disable", 7) == 0)        \
        {                           \
        if (var) printf ("Disabling %s\n", msg);    \
        var = false;                    \
        }                           \
    }*/

//         PARSENUM("maxmem",
//                  max_phys_mem,
//                  "Limiting physical memory to %d%sB\n");
//         PARSENUM("kmem",
//                  additional_kmem_size,
//                  "Reserving %d%sB for kernel memory\n",
//                  additional_kmem_size &= ~(kip.get_min_pagesize()-1));
    }
}

//     // Protect all user-level modules.
//     for (L4_Word_t i = 3; i < mbi->modcount; i++)
//     kip.dedicate_memory (mbi->mods[i].start, mbi->mods[i].end - 1,
//                  L4_BootLoaderSpecificMemoryType,
//                  kip_manager_t::desc_boot_module);

static void SECTION(".init.cpu") check_cpu_features()
{
    uint32_t req_features = X86_32_FEAT_FPU;
#if CONFIG_X86_PSE
    req_features |= X86_32_FEAT_PSE;
#endif
#if CONFIG_X86_PGE
    req_features |= X86_32_FEAT_PGE;
#endif
#if CONFIG_X86_FXSR
    req_features |= X86_32_FEAT_FXSR;
#endif
#if CONFIG_X86_SYSENTER
    req_features |= X86_32_FEAT_SEP;
#endif
#if CONFIG_IOAPIC
    req_features |= X86_32_FEAT_APIC;
#endif

    uint32_t avail_features = x86_cpu_t::features();

//     bochs:
//     CPU does not support all required features 0xffffffff (? psn ? ds acpi ss ht tm ia64 pbe missing)

    if ((req_features & avail_features) != req_features)
    {
        kconsole << "CPU does not support all required features " << req_features << " (";
        const char* x86_32_features[] = {
            "fpu",  "vme",    "de",   "pse",   "tsc",  "msr", "pae",  "mce",
            "cx8",  "apic",   "?",    "sep",   "mtrr", "pge", "mca",  "cmov",
            "pat",  "pse-36", "psn",  "cflsh", "?",    "ds",  "acpi", "mmx",
            "fxsr", "sse",    "sse2", "ss",    "ht",   "tm",  "ia64", "pbe"
        };
        for (int i = 0; i < 32; i++)
            if ((req_features & 1 << i) && (!(avail_features & 1 << i)))
                kconsole << x86_32_features[i] << " ";
        kconsole << "missing)" << endl;
        PANIC("unsupported CPU!");
    }

    uint32_t max_cpuid, family, dummy;

    if (x86_cpu_t::has_cpuid())
        x86_cpu_t::cpuid(0, &max_cpuid, &dummy, &dummy, &dummy);
    else
        max_cpuid = 0;

    if (max_cpuid >= 1)
    {
        x86_cpu_t::cpuid(1, &family, &dummy, &dummy, &dummy);
        family = (family >> 8) & 0xf;
    }
    else
    {
        family = 0;
    }

    if (avail_features & X86_32_FEAT_PSE)
    {
        kconsole << "Enabling page size extension" << endl;
        ia32_mmu_t::enable_4mb_pages();
    }

    if (avail_features & X86_32_FEAT_PGE)
    {
        kconsole << "Enabling global pages" << endl;
        ia32_mmu_t::enable_global_pages();
    }

    /* If we have a 486 or above enable alignment checking */
    if (family >= 4)
    {
        kconsole << "Enabling alignment checking" << endl;
        x86_cpu_t::enable_alignment_checks();
    }

    /* If we have a Pentium or above enable the cache */
    if (family >= 5)
    {
        kconsole << "Enabling cache" << endl;
        x86_cpu_t::init_cache();
    }

    /* If we have a PPro or above, enable user-level reading of PMCTRs */
    /* Not supported in bochs. */
    if (family >= 6)
    {
        kconsole << "Enabling performance counters" << endl;
        x86_cpu_t::init_pmctr();
        x86_cpu_t::enable_user_pmctr();
    }

    INFO_PAGE.cpu_features = avail_features;
}

/* Clear out the information page */
static void prepare_infopage()
{
    INFO_PAGE.pervasives = 0;
    INFO_PAGE.scheduler_heartbeat = 0; // Scheduler passes
    INFO_PAGE.irqs_heartbeat      = 0; // IRQ calls
    INFO_PAGE.glue_heartbeat      = 0; // glue code calls
    INFO_PAGE.faults_heartbeat    = 0; // protection faults
    INFO_PAGE.cpu_features        = 0;
}

extern timer_v1::closure_t* init_timer(); // YIKES external declaration! FIXME
static continuation_t new_context;

static void dump_regs(registers_t* regs)
{
    kconsole << endl << RED 
        << "=================================================================================================" << endl
        << "Interrupt " << regs->int_no << ", error code " << regs->err_code << endl
        << "     EAX:" << regs->eax << " EBX:" << regs->ebx << " ECX:" << regs->ecx << " EDX:" << regs->edx << endl
        << "     ESI:" << regs->esi << " EDI:" << regs->edi << " EBP:" << regs->ebp << " ESP:" << regs->esp << endl
        << "user ESP:" << regs->useresp << " CS:" << regs->cs << " DS:" << regs->ds << " SS:" << regs->ss << endl
        << "     EIP:" << regs->eip << " EFLAGS:" << regs->eflags;

    // EFLAGS bits names from msb (bit 31) to lsb (bit 0)
    static const char* eflags_bits[] = {
        "<31>", "<30>", "<29>", "<28>", "<27>", "<26>", "<25>", "<24>",
        "<23>", "<22>", "ID", "VIP", "VIF", "AC", "VM", "RF",
        "<15>", "NT", "IOPL1", "IOPL0", "OF", "DF", "IF", "TF",
        "SF", "ZF", "<5>", "AF", "<3>", "PF", "<1>", "CF"
    };
    for (int i = 0; i < 32; i++)
        if (regs->eflags & (1 << (31 - i)))
            kconsole << " " << eflags_bits[i];

    kconsole << endl;
    debugger_t::print_backtrace(regs->ebp, regs->eip, 20);

    kconsole << "=================================================================================================" << endl;    
}

class general_fault_handler_t : public interrupt_service_routine_t
{
public:
    virtual void run(registers_t* regs)
    {
        dump_regs(regs);
        PANIC("GENERAL PROTECTION FAULT");
    }
};

class invalid_opcode_handler_t : public interrupt_service_routine_t
{
public:
    virtual void run(registers_t* regs)
    {
        dump_regs(regs);
        PANIC("INVALID OPCODE");
    }
};

class dummy_handler_t : public interrupt_service_routine_t
{
public:
    virtual void run(registers_t* regs)
    {
        dump_regs(regs);
        PANIC("CATCH-ALL");
    }
};

general_fault_handler_t gpf_handler;
invalid_opcode_handler_t iop_handler;
dummy_handler_t all_exceptions_handler;

/*!
 * Get the system going.
 *
 * Prepare all system-specific structures and initialise BP and APs. Enter root domain and continue there.
 *
 * TODO: relate Pistachio SMP startup routines here.
 */
extern "C" void kernel_startup()
{
    // No dynamic memory allocation here yet, global objects not constructed either.
    run_global_ctors();

    global_descriptor_table_t gdt;
    kconsole << "Created GDT." << endl;
    interrupt_descriptor_table_t::instance().install();
    interrupt_descriptor_table_t::instance().set_isr_handler(0x0, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x2, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x3, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x4, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x5, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x6, &iop_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x7, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x8, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x9, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0xa, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0xb, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0xc, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0xd, &gpf_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0xe, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0xf, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x10, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x11, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x12, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x13, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x14, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x15, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x16, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x17, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x18, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x19, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1a, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1b, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1c, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1d, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1e, &all_exceptions_handler);
    interrupt_descriptor_table_t::instance().set_isr_handler(0x1f, &all_exceptions_handler);
    kconsole << "Created IDT." << endl;

    // Grab the bootinfo page and discover where is our bootimage.
    bootinfo_t* bi = new(bootinfo_t::ADDRESS) bootinfo_t;

    address_t start, end;
    const char* name;
    if (!bi->get_module(1, start, end, name))
    {
        PANIC("Bootimage not found!");
    }

    bootimage_t bootimage(name, start, end);

    parse_cmdline(bi);
    prepare_infopage(); // <-- init domain info page
    check_cpu_features(); // cmdline might affect used CPU feats? (i.e. noacpi flag)
    
    // TODO: CREATE INITIAL MEMORY MAPPINGS PROPERLY HERE
    // TEMPORARY: just map all mem 0..min(16Mb, RAMtop) to 1-1 mapping? for simplicity
//    int ramtop = 16*MiB;
    bi->append_vmap(0, 0, 16*MiB);//min(16*MiB, ramtop));

    timer_v1::closure_t* timer = init_timer();
    timer->enable(0); // enable timer interrupts
    kconsole << "Timer interrupt enabled." << endl;
    x86_cpu_t::enable_fpu();
    kconsole << "FPU enabled." << endl;

//    kconsole << WHITE << "...in the living memory of V2_OS" << LIGHTGRAY << endl;

    root_domain_t root_dom(bootimage);

//     kconsole << "+ root_domain entry @ 0x" << root_dom.entry() << endl;

    // Create an execution context and activate it.
    continuation_t::gpregs_t gpregs;
    gpregs.esp = read_stack_pointer();
    gpregs.eax = 0;
    gpregs.ebx = 0;
    gpregs.eflags = 0x03002; /* Flags for root domain: interrupts disabled, IOPL=3 (program can use IO ports) */
    new_context.set_gpregs(gpregs);
    new_context.set_entry(root_dom.entry());//FIXME: depends on gpregs being set before this call!
    new_context.activate(); // we have a liftoff!

    /* Never reached */
    PANIC("root domain returned!");
}

// kate: indent-width 4; replace-tabs on;
// vim: set et sw=4 ts=4 sts=4 cino=(4 :
