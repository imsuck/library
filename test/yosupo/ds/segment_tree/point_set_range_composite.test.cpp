#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/segtree.hpp"
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
    int n, q;
    cin >> n >> q;
    SegTree<M> st(n, [](int) {
        int a, b;
        cin >> a >> b;
        return M::T{a, b};
    });
    while (q--) {
        int t, a, b, c;
        cin >> t >> a >> b >> c;
        if (t == 0) {
            st[a] = {b, c};
        } else {
            cout << (int)st(a, b)(c) << "\n";
        }
    }
}
