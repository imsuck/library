#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite_large_array"

#include <bits/stdc++.h>
using namespace std;

#include "ds/dynsegtree.hpp"
#include "math/modint.hpp"

using mint = modint998;
struct M {
    struct T {
        mint a = 1, b = 0;
        mint operator()(mint x) { return a * x + b; }
    };
    static T id() { return {}; }
    static T op(T l, T r) { return {r.a * l.a, r.a * l.b + r.b}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    DynSegTree<M> st(n);
    while (q--) {
        int t, a, b, c;
        cin >> t >> a >> b >> c;
        if (t == 0) {
            st.set(a, {b, c});
        } else {
            cout << st(a, b)(c) << "\n";
        }
    }
}
