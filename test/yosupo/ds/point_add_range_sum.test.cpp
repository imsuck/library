#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;

#include "ds/segtree.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    struct M {
        using T = int64_t;
        static inline constexpr T id() { return 0; }
        static inline T op(T l, T r) { return l + r; }
    };
    SegTree<M> st(n, [](int x) { return cin >> x, x; });
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, x;
            cin >> p >> x;
            st[p] += x;
        } else {
            int l, r;
            cin >> l >> r, cout << st(l, r) << "\n";
        }
    }
}
