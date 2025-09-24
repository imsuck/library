#pragma once

#include "../other/update_proxy.hpp"

// M: T M::id(), F M::fid(), T op(T, T), F comp(F, F), bool map(F, &T)
template<class M> struct LazySegTree {
    using T = typename M::T;
    using F = typename M::F;

    int n, lg, m;
    vector<T> t;
    vector<char> upd;
    vector<F> lz;

    LazySegTree() = default;
    LazySegTree(int _n) :
        n(_n), lg(_lg(n)), m(1 << lg), t(2 * m, M::id()), upd(m),
        lz(m, M::fid()) {}
    template<class G> LazySegTree(int _n, G &&gen) : LazySegTree(_n) {
        for (int i = 0; i < n; i++) t[i + m] = gen(i);
        for (int i = m; --i;) update(i);
    }
    template<class V>
    LazySegTree(const V &v) :
        LazySegTree((int)v.size(), [&](int i) { return T(v[i]); }) {}

    vector<T> to_vec() {
        vector<T> r(n);
        for (int i = 0; i < n; i++) r[i] = (*this)[i];
        return r;
    }
    void set(int p, const T &x) {
        assert(0 <= p && p < n);
        push_to(p), t[p + m] = x, update_from(p);
    }
    void mul(int p, const T &x) {
        assert(0 <= p && p < n);
        push_to(p), t[p + m] = M::op(t[p + m], x), update_from(p);
    }
    auto operator[](int p) {
        assert(0 <= p && p < n);
        UpdateProxy up(t[p + m], [this, p]() { update_from(p); });
        return push_to(p), up;
    }
    T get(int p) { return (*this)[p]; }

    T operator()(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::id();
        int li = __builtin_ctz(l + m), ri = __builtin_ctz(r + m);
        push_to(l, li), push_to(r - 1, ri);
        T sml = M::id(), smr = M::id();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }

    T pref(int r) { return (*this)(0, r); }
    T suff(int l) { return (*this)(l, n); }
    T prod(int l, int r) { return (*this)(l, r); }
    T all_prod() const { return t[1]; }

    void apply(int p, const F &f) {
        assert(0 <= p && p < n);
        push_to(p), M::map(f, t[p + m]), update_from(p);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        int li = __builtin_ctz(l + m), ri = __builtin_ctz(r + m);
        push_to(l, li), push_to(r - 1, ri);
        for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        update_from(l, li), update_from(r - 1, ri);
    }

    template<class G> int max_right(int l, G &&g) {
        assert(0 <= l && l <= n);
        assert(g(M::id()));
        if (l == n) return n;
        push_to(l), l += m;
        T sm = M::id();
        do {
            for (; l % 2 == 0; l >>= 1);
            if (!g(M::op(sm, t[l]))) {
                while (l < m) {
                    push(l), l = l << 1;
                    if (g(M::op(sm, t[l]))) sm = M::op(sm, t[l++]);
                }
                return l - m;
            }
            sm = M::op(sm, t[l++]);
        } while ((l & -l) != l);
        return n;
    }
    template<class G> int min_left(int r, G &&g) {
        assert(0 <= r && r <= n);
        assert(g(M::id()));
        push_to(r - 1), r += m;
        T sm = M::id();
        do {
            for (r--; r > 1 && r % 2; r >>= 1);
            if (!g(M::op(t[r], sm))) {
                while (r < m) {
                    push(r), r = r << 1 | 1;
                    if (g(M::op(t[r], sm))) sm = M::op(t[r--], sm);
                }
                return r + 1 - m;
            }
            sm = M::op(t[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    // clang-format off
    static int _lg(int n) { int l = 0; while (1 << l < n) l++; return l; }
    // clang-format on
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
    void update_from(int p, int l = 0) {
        p += m;
        for (int i = l + 1; i <= lg; i++) update(p >> i);
    }
    void all_apply(int p, const F &f) {
        bool ok = M::map(f, t[p]);
        assert(p < m || ok);
        if (p < m) {
            lz[p] = M::comp(f, lz[p]), upd[p] = true;
            if (!ok) push(p), update(p);
        }
    }
    void push(int p) {
        if (!upd[p]) return;
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = M::fid(), upd[p] = false;
    }
    void push_to(int p, int l = 0) {
        p += m;
        for (int i = lg; i >= l + 1; i--) push(p >> i);
    }
};
