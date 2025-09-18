#pragma once

#include "./bst_base.hpp"

namespace treap {
    template<class T> using key_t = decltype(declval<T>().key);
    template<class T> struct node : bst::node<T> {
        uint64_t pr = rng();

        static uint64_t rng() {
            static mt19937_64 mt(
                chrono::steady_clock::now().time_since_epoch().count());
            return mt();
        }
    };

    template<class T> T *merge(node<T> *_l, node<T> *_r) {
        T *l = (T *)_l, *r = (T *)_r;
        if (!l || !r) return l ? l : r;
        if (l->pr > r->pr) {
            l->r = merge(l->r, r), l->pull();
            return l;
        } else {
            r->l = merge(l, r->l), r->pull();
            return r;
        }
    }
    template<class T>
    pair<T *, T *> split(node<T> *_t, const key_t<T> &k, bool include = true) {
        T *t = (T *)_t;
        if (!t) return {nullptr, nullptr};
        if (k < t->key || (k == t->key && !include)) {
            auto s = split(t->l, k, include);
            t->l = s.second, t->pull();
            return {s.first, t};
        } else {
            auto s = split(t->r, k, include);
            t->r = s.first, t->pull();
            return {t, s.second};
        }
    }
} // namespace treap
