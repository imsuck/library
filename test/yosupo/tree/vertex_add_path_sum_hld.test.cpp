#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/segtree.hpp"
#include "graph/hld.hpp"
#include "other/types.hpp"

struct M {
    using T = i64;
    static T id() { return 0; };
    static T op(T l, T r) { return l + r; }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<basic_string<int>> g(n);

    for (int &i : a) cin >> i;
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u] += v, g[v] += u;
    }
    HLD hld(g);
    vector<int> inv(n);
    for (int i = 0; i < n; i++) inv[hld[i]] = i;
    SegTree<M> st(n, [&](int i) { return a[inv[i]]; });

    while (q--) {
        int t, p, x, u, v;
        cin >> t;
        if (t == 0) {
            cin >> p >> x;
            st[hld[p]] += x;
        } else {
            cin >> u >> v;
            int w = hld.lca(u, v);
            i64 sm = 0;
            for (auto [l, r] : hld.path(u, w)) sm += st(l, r);
            for (auto [l, r] : hld.path(v, w, 1)) sm += st(l, r);
            cout << sm << "\n";
        }
    }
}
