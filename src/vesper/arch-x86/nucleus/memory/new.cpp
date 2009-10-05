//
// Copyright 2007 - 2009, Stanislav Karchebnyy <berkus+metta@madfire.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "memory/new.h"
#include "macros.h"
#include "nucleus.h"

using nucleus_n::nucleus;

void* page_table_t::operator new(size_t size)
{
    return operator new(size, false, 0);
}

void* page_table_t::operator new(size_t size, bool, address_t* physical_address)
{
    kconsole << "using custom operator new("<<size<<")";
    address_t ret = nucleus.mem_mgr().page_frame_allocator().alloc_frame();
    kconsole << ".. allocated at "<<ret<<endl;
    nucleus.mem_mgr().get_current_directory()->enter_mapping(ret, ret);
    if (physical_address)
        *physical_address = ret;
    return (void*)ret;
}

// 1. use mem_mgr().page_frame_allocator().alloc_frame()
// 2. copy small object allocator code from c++boot.cpp
// 3. split off specific implementation of placement_alloc and small_alloc and use common code for new/delete.
// (if possible at all, see nucleus dep below)

static inline void* placement_alloc(size_t size)
{
    uint32_t tmp = nucleus.mem_mgr().get_placement_address();
    nucleus.mem_mgr().set_placement_address(tmp+size);
    return (void *)tmp;
}

void* operator new(UNUSED_ARG size_t size, uint32_t place)
{
    return (void *)place;
}

void* operator new(size_t size, bool page_align, address_t* physical_address)
{
    if (nucleus.mem_mgr().is_heap_initialized())
    {
        return nucleus.mem_mgr().allocate(size, page_align, physical_address);
    }
    else
    {
        if (page_align)
            nucleus.mem_mgr().align_placement_address();
        void *tmp = placement_alloc(size);
        if (physical_address)
            *physical_address = (address_t)tmp;
        return tmp;
    }
}

void* operator new(size_t size)
{
    return operator new(size, false, NULL);
}

void* operator new[](size_t size)
{
    return operator new(size, false, NULL);
}

void* operator new[](size_t size, bool page_align, address_t* physical_address)
{
    return operator new(size, page_align, physical_address);
}

void operator delete(void* p)
{
    if (nucleus.mem_mgr().is_heap_initialized())
        nucleus.mem_mgr().free(p);
}

void operator delete[](void* p)
{
    if (nucleus.mem_mgr().is_heap_initialized())
        nucleus.mem_mgr().free(p);
}

// kate: indent-width 4; replace-tabs on;
// vim: set et sw=4 ts=4 sts=4 cino=(4 :