//
// Part of Metta OS. Check http://metta.exquance.com for latest version.
//
// Copyright 2007 - 2012, Stanislav Karchebnyy <berkus@exquance.com>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "types.h"

extern "C"  address_t read_instruction_pointer();
extern "C"  address_t read_stack_pointer();
extern "C"  address_t read_base_pointer();

extern "C"  void write_stack_pointer(address_t ptr);
extern "C"  void write_base_pointer(address_t ptr);
