#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/lazysegtree.hpp"
#include "math/modint.hpp"

using mint = modint998;
struct M {
    using T = array<mint, 2>;
    using F = array<mint, 2>;
    static T id() { return {0, 0}; }
    static F fid() { return {1, 0}; }
    static T op(T l, T r) { return {l[0] + r[0], l[1] + r[1]}; }
    static F comp(F l, F r) { return {l[0] * r[0], l[0] * r[1] + l[1]}; }
    static bool map(F f, T &x) {
        x[0] *= f[0];
        x[0] += f[1] * x[1];
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    LazySegTree<M> st(n, [](int x) { return cin >> x, M::T{x, 1}; });
    while (q--) {
        int t, l, r, b, c;
        cin >> t >> l >> r;
        if (t == 0) {
            cin >> b >> c;
            st.apply(l, r, {b, c});
        } else {
            cout << (int)st(l, r)[0] << "\n";
        }
    }
}
