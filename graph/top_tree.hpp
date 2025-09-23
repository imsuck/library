#pragma once

// reference:
// https://ei1333.github.io/library/structure/dynamic-tree/top-tree.hpp
template<class TreeDP> struct TopTree {
    using Info = typename TreeDP::Info;
    using Point = typename TreeDP::Point;
    using Path = typename TreeDP::Path;

    struct node;
    using ptr = node *;
    vector<node> nodes;

    TopTree(int n = 0) : nodes(n) { for (int i = 0; i < n; i++); }
    TopTree(const vector<Info> &v) : nodes(v.size()) {
        for (int i = 0; i < v.size(); i++) {
            nodes[i].id = i;
            nodes[i].info = v[i];
            nodes[i].pull();
        }
    }
    ~TopTree() {
        for (auto &n : nodes) {
            auto del = [](auto f, auto t) {
                if (!t) return;
                f(f, t->l), f(f, t->r);
                delete t;
            };
            del(del, n.light);
            n.light = n.point = 0;
        }
    }

    auto operator[](int i) { return &nodes[i]; }

    void splay(int v) { splay(&nodes[v]); }
    void expose(int v) { expose(&nodes[v]); }
    void evert(int v) { evert(&nodes[v]); }
    void link(int v, int p) { link(&nodes[v], &nodes[p]); }
    void cut(int v) { cut(&nodes[v]); }
    void cut(int v, int r) { evert(r), cut(v); }
    void set(int v, const Info &x) {
        apply(v, [&x](auto &info) { info = x; });
    }
    template<class F> void apply(int v, F &&f) {
        expose(v), f(nodes[v].info), nodes[v].pull();
    }
    int lca(int u, int v) {
        ptr l = lca(&nodes[u], &nodes[v]);
        return l ? l->id : -1;
    }
    Path fold(int v) { return evert(v), nodes[v].sum; }
    Path fold_path(int v) { return expose(v), nodes[v].sum; }
    Path fold_path(int u, int v) { return evert(u), fold_path(v); }
    Path fold_subtree(int v) {
        expose(v);
        ptr l = nodes[v].l;
        nodes[v].l = 0, nodes[v].pull();
        Path ret = nodes[v].sum;
        nodes[v].l = l, nodes[v].pull();
        return ret;
    }
    Path fold_subtree(int v, int r) { return evert(r), fold_subtree(v); }

    struct rake_node {
        using rptr = rake_node *;
        rptr p = 0, l = 0, r = 0;
        Point val{}, sum{};

        rake_node(const Point &x) : val(x), sum(x) {}

        void pull() {
            sum = val;
            if (l) sum = TreeDP::rake(sum, l->sum);
            if (r) sum = TreeDP::rake(sum, r->sum);
        }

        rptr &ch(bool d) { return !d ? l : r; }
        static bool dir(rptr t) { return t == t->p->r; }
        static void rot(rptr t) {
            rptr p = t->p;
            int d = dir(t);
            t->p = p->p;
            if (p->p) p->p->ch(dir(p)) = t;
            if ((p->ch(d) = t->ch(!d))) p->ch(d)->p = p;
            t->ch(!d) = p, p->p = t;
            p->pull(), t->pull();
        }
        static void splay(rptr t) {
            for (; t->p; rot(t))
                if (t->p->p) dir(t) == dir(t->p) ? rot(t->p) : rot(t);
        }

        rptr rightmost() {
            rptr cur = this;
            while (cur->r) cur = cur->r;
            return cur;
        }
        friend rptr insert(rptr t, const Point &x) {
            rptr z = new rake_node(x);
            if (!t) return z;
            splay(t = t->rightmost());
            t->r = z, z->p = t;
            t->pull();
            return splay(z), z;
        }
        friend rptr erase(rptr t) {
            splay(t);
            rptr l = t->l, r = t->r;
            delete t;
            if (l) l->p = 0;
            if (r) r->p = 0;
            if (!l) {
                t = r;
            } else if (!r) {
                t = l;
            } else {
                splay(t = l->rightmost());
                t->r = r, r->p = t;
                t->pull();
            }
            return t;
        }
    };
    struct node {
        ptr p = 0, l = 0, r = 0;
        rake_node *light = 0, *point = 0;
        int id;
        bool rev = 0;
        Info info{};
        Path sum{}, mus{};

        void pull() {
            Point raked = light ? TreeDP::add_vertex(light->sum, info)
                                : TreeDP::vertex(info);
            sum = mus = raked;
            if (l) {
                sum = TreeDP::compress(l->sum, sum);
                mus = TreeDP::compress(mus, l->mus);
            }
            if (r) {
                sum = TreeDP::compress(sum, r->sum);
                mus = TreeDP::compress(r->mus, mus);
            }
        }
        void flip() { swap(l, r), swap(sum, mus), rev ^= 1; }
        void push() {
            if (exchange(rev, 0)) {
                if (l) l->flip();
                if (r) r->flip();
            }
        }

        ptr &ch(bool d) { return !d ? l : r; }
        static bool is_root(ptr t) {
            return !t->p || (t != t->p->l && t != t->p->r);
        }
        static bool dir(ptr t) { return t == t->p->r; }
        static void rot(ptr t) {
            ptr p = t->p;
            int d = dir(t);
            t->p = p->p;
            if (!is_root(p)) p->p->ch(dir(p)) = t;
            if ((p->ch(d) = t->ch(!d))) p->ch(d)->p = p;
            t->ch(!d) = p, p->p = t;
            p->pull(), t->pull();
        }
        static void splay(ptr t) {
            t->push();
            {
                ptr cur = t;
                while (!is_root(cur)) cur = cur->p;
                t->point = cur->point;
                if (t != cur) cur->point = 0;
            }
            for (; !is_root(t); rot(t)) {
                ptr p = t->p, g = p->p;
                if (g) g->push();
                p->push(), t->push();
                if (!is_root(p)) rot(dir(t) == dir(p) ? p : t);
            }
        }
    };

    static ptr expose(ptr t) {
        ptr prv = 0;
        for (ptr cur = t; cur; cur = cur->p) {
            node::splay(cur);
            if (cur->r) {
                cur->light = insert(cur->light, TreeDP::add_edge(cur->r->sum));
                cur->r->point = cur->light;
            }
            if (prv) {
                prv->push();
                cur->light = erase(prv->point);
            }
            cur->r = exchange(prv, cur), cur->pull();
        }
        node::splay(t);
        return prv;
    }
    static void evert(ptr t) { expose(t), t->flip(); }
    static void link(ptr v, ptr p) {
        evert(v), expose(p);
        assert(!p->r);
        p->r = v, v->p = p, p->pull();
    }
    static void cut(ptr v) {
        expose(v);
        assert(v->l);
        v->l = v->l->p = 0, v->pull();
    }
    static ptr lca(ptr u, ptr v) {
        if (u == v) return u;
        expose(u);
        ptr l = expose(v);
        return u->p ? l : 0;
    }
};
