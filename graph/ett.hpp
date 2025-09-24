#pragma once

#include "../other/st_alloc.hpp"

template<class M> struct ETT {
    using T = typename M::T;
    struct node;
    using ptr = node *;
    struct node : st_alloc<node> {
        ptr p = 0, l = 0, r = 0;
        int sz = 1;
        T prd = M::id(), val = M::id();
        uint64_t pr = gen();

        node() {}
        node(const T &x) : prd(x), val(x) {}

        static uint64_t gen() {
            static mt19937_64 mt(uint64_t(make_unique<char>().get()));
            return mt();
        }
    };

    static int sz(ptr t) { return t ? t->sz : 0; }
    static T prd(ptr t) { return t ? t->prd : 0; }
    static ptr &par(ptr t) {
        static ptr null = new node();
        return t ? t->p : null;
    }
    static ptr pull(ptr t) {
        t->sz = sz(t->l) + 1 + sz(t->r);
        t->prd = M::op(M::op(prd(t->l), t->val), prd(t->r));
        return t;
    }
    static ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        if (l->pr < r->pr) {
            l->r = merge(l->r, r), par(l->r) = l;
            return pull(l);
        } else {
            r->l = merge(l, r->l), par(r->l) = r;
            return pull(r);
        }
    }
    static pair<ptr, ptr> split(ptr t, int k) {
        if (!t) return {};
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
    static ptr root(ptr t) { return t->p ? root(t->p) : t; }
    static int ord(ptr t) {
        int o = sz(t->l);
        for (; t->p; t = t->p)
            if (t == t->p->r) o += sz(t->p->l) + 1;
        return o;
    }

    vector<map<int, ptr>> edges;

    ptr &edge(int u, int v) { return edges[u][v] = edges[u][v] ?: new node(); }
    ptr rot(int u, int v, bool rev) {
        ptr e = edge(u, v), a, b;
        tie(a, b) = split(root(e), ord(e) + rev);
        return merge(b, a);
    }

    ETT(int n) : edges(n) {}

    T get(int v) { return edge(v, v)->val; }
    void set(int v, const T &x) {
        ptr e = edge(v, v);
        for (e->val = x; e; e = e->p) pull(e);
    }
    bool connected(int u, int v) {
        return root(edge(u, u)) == root(edge(v, v));
    }
    void link(int u, int v) {
        if (connected(u, v)) return;
        ptr a = rot(u, u, 0), b = rot(v, v, 1);
        merge(merge(a, edge(u, v)), merge(b, edge(v, u)));
    }
    void cut(int u, int v) {
        if (!connected(u, v)) return;
        ptr a, b;
        tie(a, b) = split(rot(u, v, 0), 1);
        tie(a, b) = split(b, ord(edge(v, u)));
        split(b, 1);
    }
    int subtree_size(int v, int p = -1) {
        if (p != -1) cut(v, p);
        int ret = root(edge(v, v))->sz;
        if (p != -1) link(v, p);
        return ret;
    }
    T subtree_prod(int v, int p = -1) {
        if (p != -1) cut(v, p);
        T ret = root(edge(v, v))->prd;
        if (p != -1) link(v, p);
        return ret;
    }
};
