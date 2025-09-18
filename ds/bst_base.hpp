#pragma once

#include "../other/st_alloc.hpp"

namespace bst {
    template<class T> struct node : st_alloc<T> {
        T *l = nullptr, *r = nullptr;
        void pull() { ((T *)this)->_pull(); }
    };
} // namespace bst
