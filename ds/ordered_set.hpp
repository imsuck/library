#pragma once

#include "../ds/treap_base.hpp"

// NOTE: The copy constructor only copies the pointer. Be careful when doing
// `ordered_set<> s2 = s1;`
namespace oset {
    using treap::merge, treap::split;
    template<class T> struct ordered_set {
        ordered_set() {}

        void insert(const T &k) {
            if (contains(k)) return;
            auto [a, b] = split(root, k, false);
            root = merge(a, merge(new node(k), b));
        }
        void erase(const T &k) {
            if (!contains(k)) return;
            node *a, *b, *c;
            tie(a, b) = split(root, k, false);
            tie(b, c) = split(b, k, true);
            root = merge(a, c);
        }
        optional<T> kth_order(int k) const {
            if (empty() || k > size()) return nullopt;
            int ord = 0;
            for (auto t = root; t;) {
                int w = ord + size(t->l) + 1;
                if (w == k) return t->key;
                t = k < w ? t->l : (ord = w, t->r);
            };
            return nullopt;
        }
        int order_of(const T &k, bool include = true) const {
            if (empty()) return 0;
            int ord = 0;
            for (auto t = root; t;) {
                if (k < t->key || (k == t->key && !include)) {
                    t = t->l;
                } else {
                    ord += size(t->l) + 1, t = t->r;
                }
            }
            return ord;
        }
        optional<T> pre_upper_bound(const T &k) const {
            return kth_order(order_of(k));
        }
        optional<T> lower_bound(const T &k) const {
            return kth_order(order_of(k, false) + 1);
        }

        int size() const { return size(root); }
        bool empty() const { return size() == 0; }
        bool contains(const T &k) const {
            for (auto t = root; t; t = k < t->key ? t->l : t->r)
                if (k == t->key) return true;
            return false;
        }

      private:
        struct node : treap::node<node> {
            using base = treap::node<node>;
            using base::l, base::r;

            T key;
            int sz = 1;
            node() {}
            node(const T k) : key(k) {}
            void _pull() { sz = size(l) + 1 + size(r); }
        };
        node *root = nullptr;
        static int size(node *t) { return t ? t->sz : 0; }
    };
} // namespace oset
using oset::ordered_set;
