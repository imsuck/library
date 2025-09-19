#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum_large_array"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/dynlazysegtree.hpp"
#include "math/modint.hpp"

using mint = modint998;
struct M {
    using T = mint;
    using F = array<mint, 2>;
    static T id() { return 0; }
    static F fid() { return {1, 0}; }
    static T op(T l, T r) { return l + r; }
    static F comp(const F &l, const F &r) {
        return {l[0] * r[0], l[0] * r[1] + l[1]};
    }
    static T map(const F &f, T x, int l, int r) {
        x = x * f[0] + (r - l) * f[1];
        return x;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    DynLazySegTree<M> st(n);
    while (q--) {
        int t, l, r, b, c;
        cin >> t >> l >> r;
        if (t == 0) {
            cin >> b >> c;
            st.apply(l, r, {b, c});
        } else {
            cout << (int)st(l, r) << "\n";
        }
    }
}
