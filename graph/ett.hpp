#pragma once

#include "../other/st_alloc.hpp"

namespace _ETT {
    struct node;
    using ptr = node *;
    struct node : st_alloc<node> {
        ptr p = 0, l = 0, r = 0;
        int val = 0, sum = 0;
        int sz = 1;
        uint64_t pr = gen_pr();

        node() {}
        node(int x) : val(x), sum(x) {}

        static uint64_t gen_pr() {
            static mt19937_64 mt(uint64_t(make_unique<char>().get()));
            return mt();
        }
    };
    static int sz(ptr t) { return t ? t->sz : 0; }
    static int _sm(ptr t) { return t ? t->sum : 0; }
    static ptr &par(ptr t) {
        static ptr null = new node();
        return t ? t->p : null;
    }
    ptr pull(ptr t) {
        t->sz = sz(t->l) + 1 + sz(t->r);
        t->sum = _sm(t->l) + t->val + _sm(t->r);
        return t;
    }
    ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        if (l->pr < r->pr) {
            l->r = merge(l->r, r);
            par(l->r) = l;
            return pull(l);
        } else {
            r->l = merge(l, r->l);
            par(r->l) = r;
            return pull(r);
        }
    }
    pair<ptr, ptr> split(ptr t, int k) {
        if (k < 0 || sz(t) < k) return {};
        if (!t) return {0, 0};
        int w = sz(t->l);
        ptr a;
        if (k <= w) {
            tie(a, t->l) = split(t->l, k);
            par(t->l) = t, par(a) = 0;
            return {a, pull(t)};
        } else {
            tie(t->r, a) = split(t->r, k - w - 1);
            par(t->r) = t, par(a) = 0;
            return {pull(t), a};
        }
    }
    int ord(ptr t) {
        int o = sz(t->l);
        for (; t->p; t = t->p)
            if (t == t->p->r) o += sz(t->p->l) + 1;
        return o;
    }
    ptr root(ptr t) {
        while (t->p) t = t->p;
        return t;
    }

    struct ETT {
        ETT(int _n) : n(_n), edges(n) {
            for (int i = 0; i < n; i++) edges[i][i] = new node(1);
        }

        void add_vertex() {
            edges.emplace_back(), edges[n][n] = new node(1), n++;
        }
        void link(int u, int v) {
            if (same(u, v)) return;
            ptr a = reroot(u, u), b = reroot(v, v, 1);
            merge(merge(a, edge(u, v)), merge(b, edge(v, u)));
        }
        void cut(int u, int v) {
            if (!same(u, v)) return;
            ptr a, b;
            tie(a, b) = split(reroot(u, v), 1);
            tie(a, b) = split(b, ord(edge(v, u)));
            split(b, 1);
        }
        bool same(int u, int v) { return root(edge(u, u)) == root(edge(v, v)); }
        int sub_size(int v, int p = -1) {
            if (p != -1) cut(v, p);
            int ret = root(edge(v, v))->sum;
            if (p != -1) link(v, p);
            return ret;
        }

        int n;
        vector<map<int, ptr>> edges;
        ptr &edge(int u, int v) {
            return edges[u][v] = edges[u][v] ?: new node();
        }

        ptr reroot(int u, int v, bool rev = false) {
            ptr e = edge(u, v), a, b;
            tie(a, b) = split(root(e), ord(e) + rev);
            return merge(b, a);
        }
    };
} // namespace _ETT
using _ETT::ETT;
