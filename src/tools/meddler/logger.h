//
// Part of Metta OS. Check http://metta.exquance.com for latest version.
//
// Copyright 2007 - 2012, Stanislav Karchebnyy <berkus@exquance.com>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "config.h"

#if TOOLS_DEBUG && MEDDLER_DEBUG
#define L(...) __VA_ARGS__
#else
#define L(...)
#endif // TOOLS_DEBUG && MEDDLER_DEBUG
