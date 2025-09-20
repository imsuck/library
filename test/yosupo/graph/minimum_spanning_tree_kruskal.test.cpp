#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"

#include <bits/stdc++.h>
using namespace std;

#include "graph/dsu.hpp"
#include "other/types.hpp"

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    struct Edge {
        i32 u, v;
        i64 w;
    };
    i32 n, m;
    cin >> n >> m;

    vector<Edge> es(m);
    vector<i32> id(m);
    iota(begin(id), end(id), 0);

    for (auto &[u, v, w] : es) cin >> u >> v >> w;
    sort(begin(id), end(id), [&](i32 i, i32 j) { return es[i].w < es[j].w; });
    DSU dsu(n);

    i64 cost = 0;
    vector<i32> mst;
    for (int i : id) {
        if (dsu.merge(es[i].u, es[i].v)) {
            cost += es[i].w;
            mst.push_back(i);
        }
    }
    cout << cost << "\n";
    for (int i = 0; i < n - 1; i++) cout << mst[i] << " \n"[i == n - 2];
}
