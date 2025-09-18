#pragma once

#include "../other/st_alloc.hpp"

template<class M, class I = int> struct DynLazySegTree {
    using T = typename M::T;
    using F = typename M::F;

    struct node;
    using ptr = node *;
    struct node : st_alloc<node> {
        ptr l = 0, r = 0;
        T x = M::id();
        F lz = M::fid();

        node() {}

        ptr ch(bool z) {
            auto &c = !z ? l : r;
            return c = c ?: new node();
        }
    };

    I n;
    ptr root = 0;

    DynLazySegTree() {}
    DynLazySegTree(I _n) : n(_n), root(new node()) {}

    T operator()(I l, I r) const {
        assert(0 <= l && l <= r && r <= n);
        auto rec = [&](auto &self, ptr t, I tl, I tr) {
            if (r <= tl || tr <= l) return M::id();
            if (l <= tl && tr <= r) return t->x;
            push(t, tl, tr);
            I tm = (tl + tr) / 2;
            if (r <= tm) return self(self, t->l, tl, tm);
            if (tm <= l) return self(self, t->r, tm, tr);
            return M::op(self(self, t->l, tl, tm), self(self, t->r, tm, tr));
        };
        return rec(rec, root, 0, n);
    }
    void apply(I l, I r, const F &f) const {
        assert(0 <= l && l <= r && r <= n);
        auto rec = [&](auto &self, ptr t, I tl, I tr) {
            if (r <= tl || tr <= l) return;
            if (l <= tl && tr <= r) return all_apply(t, f, tl, tr);
            push(t, tl, tr);
            I tm = (tl + tr) / 2;
            if (r <= tm) {
                self(self, t->l, tl, tm);
            } else if (tm <= l) {
                self(self, t->r, tm, tr);
            } else {
                self(self, t->l, tl, tm), self(self, t->r, tm, tr);
            }
            update(t);
        };
        rec(rec, root, 0, n);
    }
    template<class G> I max_right(I l, G &&g) const {
        assert(0 <= l && l <= n);
        assert(g(M::id()));
        if (l == n) return n;
        I r = l;
        T sm = M::id();
        auto rec = [&](auto &self, ptr t, I tl, I tr) {
            if (tr - tl == 1) return r = g(M::op(sm, t->x)) ? tr : tl, t->x;
            if (l <= tl && g(M::op(sm, t->x))) return r = tr, t->x;
            push(t, tl, tr);
            I tm = (tl + tr) / 2;
            if (tm <= l) return self(self, t->r, tm, tr);
            auto lx = self(self, t->l, tl, tm);
            if (!g(M::op(sm, lx))) return lx;
            sm = M::op(sm, lx);
            return self(self, t->r, tm, tr);
        };
        rec(rec, root, 0, n);
        return r;
    }

  private:
    static void update(ptr t) { t->x = M::op(t->l->x, t->r->x); }
    static void all_apply(ptr t, const F &f, I tl, I tr) {
        t->x = M::map(f, t->x, tl, tr);
        t->lz = M::comp(f, t->lz);
    }
    static void push(ptr t, I tl, I tr) {
        I tm = (tl + tr) / 2;
        all_apply(t->ch(0), t->lz, tl, tm);
        all_apply(t->ch(1), t->lz, tm, tr);
        t->lz = M::fid();
    }
};
