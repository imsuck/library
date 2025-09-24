#pragma once

#include "../other/st_alloc.hpp"

template<class M> struct LazyETT {
    using T = typename M::T;
    using F = typename M::F;

    struct node;
    using ptr = node *;
    struct node : st_alloc<node> {
        ptr p = 0, l = 0, r = 0;
        int sz = 1;
        uint64_t pr = gen_pr();
        T val = M::id(), sm = M::id();
        bool upd = false;
        F lz = M::fid();

        node() {}

        static uint64_t gen_pr() {
            static mt19937_64 mt((size_t)make_unique<char>().get());
            return mt();
        }
    };
    static int sz(ptr t) { return t ? t->sz : 0; }
    static ptr &par(ptr t) {
        static ptr null = new node();
        return t ? t->p : null;
    }
    static ptr pull(ptr t) {
        t->sz = sz(t->l) + 1 + sz(t->r), t->sm = t->val;
        if (t->l) t->sm = M::op(t->l->sm, t->sm);
        if (t->r) t->sm = M::op(t->sm, t->r->sm);
        return t;
    }
    static void all_apply(ptr t, const F &f) {
        if (!t) return;
        t->val = M::map(f, t->val), t->sm = M::map(f, t->sm);
        t->lz = M::comp(f, t->lz), t->upd = true;
    }
    static void push(ptr t) {
        if (!t->upd) return;
        all_apply(t->l, t->lz), all_apply(t->r, t->lz);
        pull(t);
        t->lz = M::fid(), t->upd = false;
    }
    static int ord(ptr t) {
        int res = sz(t->l);
        for (; t->p; t = t->p)
            if (t == t->p->r) res += sz(t->p->l) + 1;
        return res;
    }
    static ptr root(ptr t) {
        while (t->p) t = t->p;
        return t;
    }
    static ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
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
    static pair<ptr, ptr> split(ptr t, int k) {
        if (!t) return {};
        push(t);
        int w = sz(t->l) + 1;
        ptr a;
        if (k < w) {
            tie(a, t->l) = split(t->l, k);
            par(t->l) = t, par(a) = 0;
            return {a, pull(t)};
        } else {
            tie(t->r, a) = split(t->r, k - w);
            par(t->r) = t, par(a) = 0;
            return {pull(t), a};
        }
    }

    vector<map<int, ptr>> edges;
    ptr edge(int u, int v) { return edges[u][v] = edges[u][v] ?: new node(); }
    ptr vert(int v) { return edge(v, v); }
    ptr reroot(ptr e, bool rev) {
        auto [a, b] = split(root(e), ord(e) + rev);
        return merge(b, a);
    }

    LazyETT(int n) : edges(n) {}
    LazyETT(const vector<T> &val) : LazyETT((int)val.size()) {
        for (int i = 0; i < val.size(); i++)
            vert(i)->val = vert(i)->sm = val[i];
    }

    bool same(int u, int v) { return root(vert(u)) == root(vert(v)); }
    void link(int u, int v) {
        assert(!same(u, v));
        ptr a = reroot(vert(u), 0), b = reroot(vert(v), 1);
        merge(merge(a, edge(u, v)), merge(b, edge(v, u)));
    }
    void cut(int u, int v) {
        assert(same(u, v));
        ptr a, b;
        tie(a, b) = split(reroot(edge(u, v), 0), 1);
        tie(a, b) = split(b, ord(edge(v, u)));
        split(b, 1);
    }

    void set(int v, const T &x) {
        ptr p = vert(v);
        stack<ptr> st;
        while (p->p) p = p->p, st.push(p);
        while (st.size()) push(st.top()), st.pop();
        p = vert(v), p->val = x;
        for (pull(p); p->p;) pull(p = p->p);
    }
    T subtree_prod(int v, int p) {
        if (p != -1) cut(p, v);
        T ret = root(vert(v))->sm;
        if (p != -1) link(p, v);
        return ret;
    }
    void apply(int v, int p, const F &f) {
        if (p != -1) cut(p, v);
        all_apply(root(vert(v)), f);
        if (p != -1) link(p, v);
    }
};
