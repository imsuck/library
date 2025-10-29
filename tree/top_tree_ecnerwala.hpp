#pragma once

/**
 * Convenient memo:
 *   Creating vertices:
 *     n->val = ...;
 *     n->set_vert();
 *
 *   Creating edges:
 *     link(e, va, vb);
 *
 *   Updates:
 *     auto cur = get_path(va, vb); // or get_subtree(va, vb)
 *     cur->do_stuff();
 *     cur->pull_all();
 *
 * Node types:
 *   path edges: compress(c[0], self, c[1])
 *     assert(is_path && !is_vert);
 *     assert(c[0] && c[1]);
 *     assert(c[0]->is_path && c[1]->is_path);
 *     assert(!c[2]);
 *   (path) vertices: self + rake(c[0], c[1])
 *     assert(is_path && is_vert);
 *     assert(!c[2]);
 *     if (c[0]) assert(!c[0]->is_path);
 *     if (c[1]) assert(!c[1]->is_path);
 *   non-path edges: rake(c[0], self + c[2], c[1])
 *     assert(!is_path && !is_vert);
 *     assert(c[2])
 *     assert(c[2]->is_path);
 *     if (c[0]) assert(!c[0]->is_path);
 *     if (c[1]) assert(!c[1]->is_path);
 */
template<class node> struct top_tree_node_base {
    using ptr = node *;

  private:
    ptr as_derived() { return (ptr)this; }
    auto as_derived() const { return (const ptr)this; }

  public:
    bool rev = false;
    ptr p = 0;
    array<ptr, 3> c{0, 0, 0};

    int d() const {
        assert(p);
        if (this == p->c[0]) return 0;
        if (this == p->c[1]) return 1;
        if (this == p->c[2]) return 2;
        assert(false);
    }
    ptr &p_c() { return p->c[d()]; }

    bool is_vert, is_path;
    void set_vert() { is_path = is_vert = true, _pull(); }

    bool r() const { return !p || p->is_path != is_path; }

  private:
#define CHECK(a) \
    template<class T, class = void> struct has_##a##_t : false_type {}; \
    template<class T> struct has_##a##_t<T, void_t<decltype(&T::a)>> : true_type {}; \
    template<class T> static constexpr bool has_##a = has_##a##_t<T>::value;
    CHECK(push) CHECK(flip) CHECK(pull)
#undef CHECK
    void _flip() {
        assert(is_path);
        swap(c[0], c[1]), rev ^= 1;
        if constexpr (has_flip<node>) as_derived()->flip();
    }
    void _push() {
        if (rev) {
            assert(is_path);
            if (!is_vert) {
                c[0]->_flip();
                c[1]->_flip();
            }
            rev = false;
        }
        if constexpr (has_push<node>) as_derived()->push();
    }
    void _pull() {
        if constexpr (has_pull<node>) as_derived()->pull();
    }

  public:
    void push_all() {
        if (p) p->push_all();
        _push();
    }
    ptr pull_all() {
        ptr cur = as_derived();
        cur->_push(), cur->_pull();
        for (; cur->p; cur->_pull()) cur = cur->p;
        return cur;
    }

  private:
    static inline void attach(ptr pa, int c_d, ptr ch) {
        pa->c[c_d] = ch;
        if (ch) ch->p = pa;
    }
    void rot() {
        assert(!is_vert);
        assert(!r());

        ptr pa = p;
        int x = d();
        assert(x != 2);
        ptr ch = c[!x];

        if (pa->p) pa->p_c() = as_derived();
        this->p = pa->p;

        attach(pa, x, ch);
        attach(as_derived(), !x, pa);

        pa->_pull();
    }
    void rot2(int c_d) {
        assert(!is_vert);
        assert(!r());
        assert(c[c_d]);
        assert(!c[c_d]->is_vert);

        if (d() == c_d) return rot();

        ptr pa = p;
        int x = d();
        assert(x != 2);
        assert(c_d == !x);
        ptr ch = c[c_d]->c[!x];

        if (pa->p) pa->p_c() = as_derived();
        this->p = pa->p;

        attach(pa, x, ch);
        attach(c[c_d], !x, pa);

        pa->_pull();
    }

    void splay_dir(int x) {
        for (; !r() && d() == x; rot())
            if (!p->r() && p->d() == x) p->rot();
    }

    void splay() {
        assert(!is_vert);
        for (; !r(); rot())
            if (!p->r()) p->d() == d() ? p->rot() : rot();
    }

    void splay2(int c_d) {
        assert(!is_vert && is_path);
        assert(c[c_d] && !c[c_d]->is_vert);
        for (; !r(); rot2(c_d))
            if (!p->r()) p->d() == d() ? p->rot() : rot2(c_d);
    }

    void splay2() {
        assert(!is_vert && is_path);
        assert(!r());
        p->splay2(d());
    }

    void splay_vert() {
        assert(is_vert);

        if (r()) return;

        p->splay_dir(d());
        if (p->r()) return;
        assert(p->d() != d());

        if (d() == 1) p->rot();
        assert(d() == 0);

        p->splay2();
        assert(d() == 0);
        assert(p->d() == 1);
        assert(p->p->r());
    }

    ptr cut_right() {
        assert(is_vert && is_path);
        splay_vert();

        if (r() || d() == 1) {
            assert(r() || (d() == 1 && p->r()));
            assert(!c[0]);
            return 0;
        }

        ptr pa = p;
        assert(pa->r() || (pa->d() == 1 && pa->p->r()));
        assert(!pa->is_vert);
        assert(pa->is_path);
        assert(pa->c[0] == this);
        assert(!pa->c[2]);

        if (pa->p) pa->p_c() = as_derived();
        this->p = pa->p;

        pa->is_path = false;
        pa->c[2] = pa->c[1];

        attach(pa, 0, c[0]);
        attach(pa, 1, c[1]);

        c[0] = 0;
        attach(as_derived(), 1, pa);
        assert(!c[2]);

        return pa->_pull(), pa;
    }

    ptr splice_non_path() {
        assert(!is_vert);
        assert(!is_path);

        splay();
        assert(p && p->is_vert && p->is_path);
        p->cut_right();

        if (!p->is_path) rot();
        assert(p && p->is_vert && p->is_path);
        assert(p->r() || (p->d() == 1 && p->p->r()));
        assert(p->c[d()] == this && !p->c[!d()]);

        ptr pa = p;

        if (pa->p) pa->p_c() = as_derived();
        this->p = pa->p;

        attach(pa, 0, c[0]);
        attach(pa, 1, c[1]);

        assert(c[2] && c[2]->is_path);
        attach(as_derived(), 0, pa);
        c[1] = c[2], c[2] = 0;

        is_path = true;

        return pa->_pull(), pa;
    }

    ptr splice_all() {
        ptr res = as_derived();
        for (ptr cur = as_derived(); cur; cur = cur->p) {
            if (!cur->is_path) res = cur->splice_non_path();
            assert(cur->is_path);
        }
        return res;
    }

  public:
    ptr expose() {
        assert(is_vert);

        push_all();

        ptr res = splice_all();
        cut_right(), pull_all();

        return res;
    }

    ptr expose_edge() {
        assert(!is_vert);

        push_all();

        ptr v = is_path ? c[1] : c[2];
        for (v->_push(); !v->is_vert; v->_push()) v = v->c[0];

        ptr res = v->splice_all();
        v->cut_right(), v->pull_all();

        assert(!p);
        assert(v == c[1]);

        return res == v ? as_derived() : res;
    }

    ptr meld_path_end() {
        assert(!p);
        ptr rt = as_derived();
        while (true) {
            rt->_push();
            if (rt->is_vert) break;
            rt = rt->c[1];
        }
        rt->splay_vert();
        if (rt->c[0] && rt->c[1]) {
            ptr ch = rt->c[1];
            while (true) {
                ch->_push();
                if (!ch->c[0]) break;
                ch = ch->c[0];
            }
            ch->splay();
            assert(!ch->c[0]);

            attach(ch, 0, rt->c[0]), rt->c[0] = 0;

            ch->_pull();
        } else if (rt->c[0]) {
            rt->c[1] = rt->c[0], rt->c[0] = 0;
        }
        return rt->pull_all();
    }

    void evert() {
        expose();

        ptr rt = as_derived();
        while (rt->p) {
            assert(rt->d() == 1);
            rt = rt->p;
        }

        rt->_flip();
        rt->meld_path_end();

        expose();

        assert(!p);
    }

    friend void link(ptr e, ptr v, ptr p) {
        assert(e && v && p);
        assert(!e->c[0] && !e->c[1] && !e->c[2]);
        v->evert(), p->expose();
        while (p->p) p = p->p;

        assert(!v->p);

        e->is_path = true, e->is_vert = false;
        attach(e, 0, p);
        attach(e, 1, v);
        e->_pull();
    }

    // Link v's root as a child of p with edge e
    // Returns false if they're already in the same subtree
    friend bool link_root(ptr e, ptr v, ptr p) {
        assert(e && v && p);
        assert(!e->c[0] && !e->c[1] && !e->c[2]);
        v->expose();
        p->expose();

        while (v->p) v = v->p;
        while (p->p) p = p->p;
        if (v == p) return false;

        e->is_path = true, e->is_vert = false;
        attach(e, 0, p);
        attach(e, 1, v);
        e->_pull();

        return true;
    }

    friend pair<ptr, ptr> cut(ptr e) {
        assert(!e->is_vert);
        e->expose_edge();

        assert(!e->p);
        assert(e->is_path);

        ptr l = e->c[0], r = e->c[1];
        assert(l && r);
        assert(!e->c[2]);

        e->c[0] = e->c[1] = 0;
        l->p = r->p = 0;

        l->meld_path_end();

        return {l, r};
    }

    friend ptr get_path(ptr v) {
        assert(v->is_vert);
        v->expose();
        if (!v->p) return v;
        assert(!v->p->p);
        return v->p;
    }

    friend ptr get_subtree(ptr v) {
        v->expose();
        return v;
    }

    friend ptr lca(ptr u, ptr v) {
        u->expose();
        auto up = u->p;
        ptr l = v->expose();
        if (u != v && up == u->p && (!up || !up->p)) return 0;
        return l;
    }
};
