//
// Part of Metta OS. Check http://metta.exquance.com for latest version.
//
// Copyright 2007 - 2012, Stanislav Karchebnyy <berkus@exquance.com>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Minimal operator new/delete implementation.
//
#include <new>
#include "macros.h"
#include "panic.h"

void* operator new(size_t size) throw()
{
    PANIC("Default new called!");
    return 0;
}

void operator delete(void*) throw()
{
    PANIC("Default delete called!");
}
