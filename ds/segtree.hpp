#pragma once

#include "../other/update_proxy.hpp"

// Modified version of atcoder library's segtree.hpp
template<class M> struct SegTree {
    using T = typename M::T;

    int n, m;
    vector<T> t;

    SegTree() = default;
    SegTree(int _n) : n(_n), m(bit_ceil(n)), t(2 * m, M::id()) {}
    template<class G> SegTree(int _n, G &&gen) : SegTree(_n) {
        for (int i = 0; i < n; i++) t[i + m] = gen(i);
        for (int i = m; --i;) update(i);
    }
    template<class V>
    SegTree(const V &v) :
        SegTree((int)v.size(), [&](int i) { return T(v[i]); }) {}

    vector<T> to_vec() {
        vector<T> r(n);
        for (int i = 0; i < n; i++) r[i] = t[i + m];
        return r;
    }
    void set(int p, const T &x) {
        assert(0 <= p && p < n);
        t[p + m] = x, update_from(p);
    }
    void mul(int p, const T &x) {
        assert(0 <= p && p < n);
        t[p + m] = M::op(t[p + m], x), update_from(p);
    }
    auto operator[](int p) {
        assert(0 <= p && p < n);
        UpdateProxy up(t[p + m], [this, p]() { update_from(p); });
        return up;
    }
    T operator[](int p) const {
        assert(0 <= p && p < n);
        return t[p + m];
    }
    T get(int p) const { return (*this)[p]; }
    T operator()(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        T resl = M::id(), resr = M::id();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }
    T pref(int r) const { return (*this)(0, r); }
    T suff(int l) const { return (*this)(l, n); }
    T prod(int l, int r) const { return (*this)(l, r); }
    T all_prod() const { return t[1]; }
    template<class G> int max_right(int l, G &&g) const {
        assert(0 <= l && l <= n);
        assert(g(M::id()));
        if (l == n) return n;
        l += m;
        T sm = M::id();
        do {
            for (; l % 2 == 0; l >>= 1);
            if (!g(M::op(sm, t[l]))) {
                while (l < m) {
                    l = l << 1;
                    if (g(M::op(sm, t[l]))) sm = M::op(sm, t[l++]);
                }
                return l - m;
            }
            sm = M::op(sm, t[l++]);
        } while ((l & -l) != l);
        return n;
    }
    template<class G> int min_left(int r, G &&g) const {
        assert(0 <= r && r <= n);
        assert(g(M::id()));
        if (r == 0) return 0;
        r += m;
        T sm = M::id();
        do {
            for (r--; r > 1 && r & 1; r >>= 1);
            if (!g(M::op(t[r], sm))) {
                while (r < m) {
                    r = r << 1 | 1;
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
    static int bit_ceil(int n) { int m = 1; while (m < n) m *= 2; return m; }
    // clang-format on
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
    void update_from(int p) {
        for (p += m; p >>= 1;) update(p);
    }
};
