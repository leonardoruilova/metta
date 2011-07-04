//
// Part of Metta OS. Check http://metta.exquance.com for latest version.
//
// Copyright 2007 - 2011, Stanislav Karchebnyy <berkus@exquance.com>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "idt.h"
#include "cpu.h"
#include "segs.h"

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C"
{
    void isr0 ();
    void isr1 ();
    void isr2 ();
    void isr3 ();
    void isr4 ();
    void isr5 ();
    void isr6 ();
    void isr7 ();
    void isr8 ();
    void isr9 ();
    void isr10();
    void isr11();
    void isr12();
    void isr13();
    void isr14();
    void isr15();
    void isr16();
    void isr17();
    void isr18();
    void isr19();
    void isr20();
    void isr21();
    void isr22();
    void isr23();
    void isr24();
    void isr25();
    void isr26();
    void isr27();
    void isr28();
    void isr29();
    void isr30();
    void isr31();

    void irq0 ();
    void irq1 ();
    void irq2 ();
    void irq3 ();
    void irq4 ();
    void irq5 ();
    void irq6 ();
    void irq7 ();
    void irq8 ();
    void irq9 ();
    void irq10();
    void irq11();
    void irq12();
    void irq13();
    void irq14();
    void irq15();
}

// Remap the irq table so that IRQ interrupts start at MASTER_VEC
static inline void reprogram_pic() // FIXME: move to ia32_pic_t
{
#define PICM 0x20
#define PICS 0xA0
#define ICW1 0x11
#define PICMI 0x21
#define PICSI 0xA1
#define MASTER_VEC 0x20
#define SLAVE_VEC  0x28
#define ICW4 0x01

    x86_cpu_t::outb(PICM, ICW1);
    x86_cpu_t::outb(PICS, ICW1);
    x86_cpu_t::outb(PICMI, MASTER_VEC);
    x86_cpu_t::outb(PICSI, SLAVE_VEC);
    x86_cpu_t::outb(PICMI, 4);
    x86_cpu_t::outb(PICSI, 2);
    x86_cpu_t::outb(PICMI, ICW4);
    x86_cpu_t::outb(PICSI, ICW4);
    x86_cpu_t::outb(PICMI, 0xff);//0?
    x86_cpu_t::outb(PICSI, 0xff);//0?
}

interrupt_descriptor_table_t& interrupt_descriptor_table_t::instance()
{
    static interrupt_descriptor_table_t interrupts_table;
    return interrupts_table;
}

#define IDT_ENTRY(n, type) \
    idt_entries[n].set(KERNEL_CS, isr##n, idt_entry_t::type, 3)

#define IRQ_ENTRY(n, m) \
    idt_entries[n].set(KERNEL_CS, irq##m, idt_entry_t::interrupt, 3)

void interrupt_descriptor_table_t::install()
{
    limit = sizeof(idt_entries)-1;
    base = (address_t)&idt_entries;

    // DPL is 3 to allow kernel isrs to work in user-mode.
    IDT_ENTRY(0, interrupt);
    IDT_ENTRY(1, interrupt);
    IDT_ENTRY(2, interrupt);
    IDT_ENTRY(3, trap);
    IDT_ENTRY(4, trap);
    IDT_ENTRY(5, interrupt);
    IDT_ENTRY(6, interrupt);
    IDT_ENTRY(7, interrupt);
    IDT_ENTRY(8, interrupt);
    IDT_ENTRY(9, interrupt);
    IDT_ENTRY(10, interrupt);
    IDT_ENTRY(11, interrupt);
    IDT_ENTRY(12, interrupt);
    IDT_ENTRY(13, interrupt);
    IDT_ENTRY(14, interrupt);
    IDT_ENTRY(15, interrupt);
    IDT_ENTRY(16, interrupt);
    IDT_ENTRY(17, interrupt);
    IDT_ENTRY(18, interrupt);
    IDT_ENTRY(19, interrupt);
    // Nothing useful defined on intel below this line
    IDT_ENTRY(20, interrupt);
    IDT_ENTRY(21, interrupt);
    IDT_ENTRY(22, interrupt);
    IDT_ENTRY(23, interrupt);
    IDT_ENTRY(24, interrupt);
    IDT_ENTRY(25, interrupt);
    IDT_ENTRY(26, interrupt);
    IDT_ENTRY(27, interrupt);
    IDT_ENTRY(28, interrupt);
    IDT_ENTRY(29, interrupt);
    IDT_ENTRY(30, interrupt);
    IDT_ENTRY(31, interrupt);

    reprogram_pic();

    // 32-47 are IRQs.
    // DPL is 3 so that interrupts can happen from user mode.
    IRQ_ENTRY(32, 0);
    IRQ_ENTRY(33, 1);
    IRQ_ENTRY(34, 2);
    IRQ_ENTRY(35, 3);
    IRQ_ENTRY(36, 4);
    IRQ_ENTRY(37, 5);
    IRQ_ENTRY(38, 6);
    IRQ_ENTRY(39, 7);
    IRQ_ENTRY(40, 8);
    IRQ_ENTRY(41, 9);
    IRQ_ENTRY(42, 10);
    IRQ_ENTRY(43, 11);
    IRQ_ENTRY(44, 12);
    IRQ_ENTRY(45, 13);
    IRQ_ENTRY(46, 14);
    IRQ_ENTRY(47, 15);

    asm volatile("lidtl %0\n" :: "m"(*this));
}

// kate: indent-width 4; replace-tabs on;
// vim: set et sw=4 ts=4 sts=4 cino=(4 :
