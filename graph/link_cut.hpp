#pragma once
#include <bits/stdc++.h>
using namespace std;

template<class node> struct LCT {
    using ptr = node *;
    vector<node> nodes;

    LCT(int n = 0) {
        nodes.reserve(n);
        for (int i = 0; i < n; i++) nodes.emplace_back(i);
    }

    auto operator[](int i) { return &nodes[i]; }

    void splay(int v) { splay(&nodes[v]); }
    void expose(int v) { expose(&nodes[v]); }
    void expose_path(int u, int v) { evert(u), expose(v); }
    void evert(int v) { evert(&nodes[v]); }
    void link(int v, int p) { link(&nodes[v], &nodes[p]); }
    void cut(int v, int p) { cut(&nodes[v], &nodes[p]); }
    int lca(int u, int v) {
        ptr l = lca(&nodes[u], &nodes[v]);
        return l ? l->id : -1;
    }
    template<class... T> void set(int v, T &&...x) {
        expose(v), nodes[v].set(x...);
    }
    template<class... T> void add(int v, T &&...x) {
        expose(v), nodes[v].add(x...);
    }

    static void splay(ptr t) {
        for (t->_push(); state(t); rot(t)) {
            ptr p = t->p, g = p->p;
            if (g) g->_push();
            p->_push(), t->_push();
            if (state(p)) rot(state(t) == state(p) ? p : t);
        }
    }
    static void expose(ptr t) {
        ptr prv = 0, cur = t;
        for (; cur; cur = cur->p) {
            splay(cur);
            if (cur->r) cur->_add_light(cur->r);
            if (prv) cur->_sub_light(prv);
            attach(cur, 1, exchange(prv, cur));
        }
        splay(t);
    }
    static void evert(ptr t) { expose(t), t->_flip(); }
    static void link(ptr v, ptr p) {
        evert(v), expose(p);
        assert(!v->p && !p->r);
        attach(p, 1, v);
    }
    static void cut(ptr v, ptr p) {
        evert(p), expose(v);
        assert(!v->p && v->l == p);
        attach(v, 0, p->p = 0);
    }
    static ptr lca(ptr u, ptr v) {
        if (u == v) return u;
        expose(u), expose(v);
        if (!u->p) return 0;
        splay(u);
        return u->p ?: u;
    }

    static ptr &ch(ptr t, bool d) { return d ? t->r : t->l; }
    static void attach(ptr p, int d, ptr c) {
        if (c) c->p = p;
        ch(p, d) = c, p->pull();
    }
    static int state(ptr t) {
        if (!t->p) return 0;
        return t == t->p->l ? -1 : t == t->p->r ? 1 : 0;
    }
    static void rot(ptr t) {
        ptr p = t->p, g = p->p;
        int d = state(t) == 1, dp = state(p);
        t->p = p->p;
        if (g) dp ? attach(g, dp == 1, t) : g->_change_light(p, t);
        attach(p, d, ch(t, !d));
        attach(t, !d, p);
    }
};

template<class node> struct lct_node {
    using ptr = node *;
    static ptr $(ptr t) {
        static node nil;
        return t ?: &nil;
    }
    ptr p = 0, l = 0, r = 0;
    int id = -1;
    bool rev = 0;
    lct_node(int i = -1) : id(i) {}

    node *as_derived() { return (node *)this; };
    void _push() {
        if (exchange(rev, 0)) $(l)->_flip(), $(r)->_flip();
        if constexpr (has_push<node>) as_derived()->push();
    }
    void _flip() {
        swap(l, r), rev ^= 1;
        if constexpr (has_flip<node>) as_derived()->flip();
    }

    void _add_light(ptr c) {
        if constexpr (has_add_light<node>) as_derived()->add_light(c);
    }
    void _sub_light(ptr c) {
        if constexpr (has_sub_light<node>) as_derived()->sub_light(c);
    }
    void _change_light(ptr p, ptr c) {
        if constexpr (has_change_light<node>) as_derived()->change_light(p, c);
    }

// rip compile time
#define CHECK(a) \
    template<class T, class = void> struct has_##a##_t : false_type {}; \
    template<class T> struct has_##a##_t<T, void_t<decltype(&T::a)>> : true_type {}; \
    template<class T> static constexpr bool has_##a = has_##a##_t<T>::value;
    CHECK(push) CHECK(flip)
    CHECK(add_light) CHECK(sub_light) CHECK(change_light)
#undef CHECK
};
