//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// class multimap

// template <class... Args>
//   iterator emplace_hint(const_iterator position, Args&&... args);

#include <map>
#include <cassert>

#include "../../../Emplaceable.h"
#include "../../../DefaultOnly.h"

int main()
{
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    {
        typedef std::multimap<int, DefaultOnly> M;
        typedef M::iterator R;
        M m;
        assert(DefaultOnly::count == 0);
        R r = m.emplace_hint(m.cend());
        assert(r == m.begin());
        assert(m.size() == 1);
        assert(m.begin()->first == 0);
        assert(m.begin()->second == DefaultOnly());
        assert(DefaultOnly::count == 1);
        r = m.emplace_hint(m.cend(), 1);
        assert(r == next(m.begin()));
        assert(m.size() == 2);
        assert(next(m.begin())->first == 1);
        assert(next(m.begin())->second == DefaultOnly());
        assert(DefaultOnly::count == 2);
        r = m.emplace_hint(m.cend(), 1);
        assert(r == next(m.begin(), 2));
        assert(m.size() == 3);
        assert(next(m.begin(), 2)->first == 1);
        assert(next(m.begin(), 2)->second == DefaultOnly());
        assert(DefaultOnly::count == 3);
    }
    assert(DefaultOnly::count == 0);
    {
        typedef std::multimap<int, Emplaceable> M;
        typedef M::iterator R;
        M m;
        R r = m.emplace_hint(m.cend(), 2);
        assert(r == m.begin());
        assert(m.size() == 1);
        assert(m.begin()->first == 2);
        assert(m.begin()->second == Emplaceable());
        r = m.emplace_hint(m.cbegin(), 1, 2, 3.5);
        assert(r == m.begin());
        assert(m.size() == 2);
        assert(m.begin()->first == 1);
        assert(m.begin()->second == Emplaceable(2, 3.5));
        r = m.emplace_hint(m.cbegin(), 1, 3, 3.5);
        assert(r == m.begin());
        assert(m.size() == 3);
        assert(r->first == 1);
        assert(r->second == Emplaceable(3, 3.5));
    }
    {
        typedef std::multimap<int, double> M;
        typedef M::iterator R;
        M m;
        R r = m.emplace_hint(m.cend(), M::value_type(2, 3.5));
        assert(r == m.begin());
        assert(m.size() == 1);
        assert(m.begin()->first == 2);
        assert(m.begin()->second == 3.5);
    }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
}
