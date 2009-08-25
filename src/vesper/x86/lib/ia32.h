//
// Architecture-dependent defines.
// Do not put any functions in this file: used with assembler.
//
#pragma once

//======================================================================================================================
// MMU
//======================================================================================================================

#define IA32_PAGE_PRESENT        (1<<0)
#define IA32_PAGE_WRITABLE       (1<<1)
#define IA32_PAGE_USER           (1<<2)
#define IA32_PAGE_WRITE_THROUGH  (1<<3)
#define IA32_PAGE_CACHE_DISABLE  (1<<4)
#define IA32_PAGE_ACCESSED       (1<<5)
#define IA32_PAGE_DIRTY          (1<<6)
#define IA32_PAGE_SUPER          (1<<7)
#define IA32_PAGE_GLOBAL         (1<<8)
