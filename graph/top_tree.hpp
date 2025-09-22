#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../other/st_alloc.hpp"
#include "link_cut.hpp"

// reference: https://ei1333.github.io/library/structure/dynamic-tree/top-tree.hpp
template<class TreeDP> struct TopTree {
    using Info = typename TreeDP::Info;
    using Point = typename TreeDP::Point;
    using Path = typename TreeDP::Path;

    struct node;
    LCT<node> tr;

    TopTree(int n) : tr(n) {}

    void link(int v, int p) { link(tr[v], tr[p]); }
    void cut(int v, int p) { cut(tr[v], tr[p]); }
    bool connected(int u, int v) { return connected(tr[u], tr[v]); }
    Path query(int v) {
        evert(tr[v]);
        return tr[v]->sum;
    }
    Path query_path(int v) {
        expose(tr[v]);
        return tr[v]->sum;
    }
    Path query_path(int u, int v) {
        evert(tr[u]);
        return query_path(v);
    }
    Path query_subtree(int v) {
        expose(tr[v]);
        ptr l = exchange(tr[v]->l, 0);
        tr[v]->pull();
        Path ret = tr[v]->sum;
        tr[v]->l = l;
        tr[v]->pull();
        return ret;
    }
    Path query_subtree(int v, int r) {
        evert(tr[r]);
        return query_subtree(v);
    }

    struct splay_node : st_alloc<splay_node> {
        using ptr = splay_node *;
        ptr p = 0, l = 0, r = 0;
        Point key{}, sum{};

        splay_node(const Point &x) : key(x), sum(x) {}

        int state() {
            if (!p) return 0;
            return this == p->l ? -1 : this == p->r ? 1 : 0;
        }
        ptr &ch(bool d) { return !d ? l : r; }
        ptr rightmost() {
            ptr cur = this;
            while (cur->r) cur = cur->r;
            return cur;
        }
        void pull() {
            sum = key;
            if (l) sum = TreeDP::rake(sum, l);
            if (r) sum = TreeDP::rake(sum, r);
        }
        void attach(ptr c, bool d) {
            if (c) c->p = this;
            p->ch(d) = c, pull();
        }
        void rot() {
            int d = state() == 1, dp = p->state();
            p = p->p;
            if (dp) p->p->attach(dp == 1, this);
            p->attach(ch(!d), d);
            attach(p, !d);
        }
        void splay() {
            for (; state(); rot())
                if (p->state()) state() == p->state() ? p->rot() : rot();
        }

        static ptr insert(ptr t, const Point &x) {
            ptr z = new splay_node(x);
            if (!t) return z;
            t = t->rightmost();
            t->r = z, t->pull();
            return z->splay(), z;
        }
        static ptr erase(ptr t) {
            t->splay();
            ptr l = t->l, r = t->r;
            delete t;
            if (!l) {
                t = r;
                if (t) t->p = 0;
            } else if (!r) {
                t = l;
                t->p = 0;
            } else {
                l->p = 0;
                t = l->rightmost();
                t->splay();
                t->r = r, r->p = t;
                t->pull();
            }
            return t;
        }
    };
    struct node : lct_node<node> {
        using base = lct_node<node>;
        using base::base, base::l, base::r;

        using ptr = node *;
        Info info;
        Path sum, mus;
        splay_node *light = 0, *point = 0;

        void pull() {
            Path sub = light ? TreeDP::add_vertex(light->sum, info)
                             : TreeDP::vertex(info);
            sum = mus = sub;
            if (l) {
                sum = TreeDP::compress(l->sum, sum);
                mus = TreeDP::compress(mus, l->mus);
            }
            if (r) {
                sum = TreeDP::compress(sum, r->sum);
                mus = TreeDP::compress(r->mus, mus);
            }
        }
        void flip() { swap(sum, mus); }
        void add_light(ptr c) {
            light = light->insert(TreeDP::add_edge(c->sum));
            c->point = light;
        }
        void sub_light(ptr c) {
            c->_push();
            light = light->erase(c->point);
        }
    };
    using ptr = typename node::ptr;
    static ptr expose(ptr t) {
        ptr cur = t;
        while (!cur->state()) cur = cur->p;
        t->point = cur->point;
        if (t != cur) cur->point = 0;
        LCT<node>::expose(t);
    }
    static void evert(ptr t) { expose(t), t->_flip(); }
    static void link(ptr v, ptr p) {
        evert(v), expose(p);
        assert(!v->p && !p->r);
        LCT<node>::attach(p, 1, v);
    }
    static void cut(ptr v, ptr p) {
        evert(p), expose(v);
        assert(!v->p && v->l == p);
        attach(v, 0, p->p = 0);
    }
    static bool connected(ptr u, ptr v) {
        expose(u), expose(v);
        return u == v || u->p;
    }
};
