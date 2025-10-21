#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include <bits/stdc++.h>
using namespace std;

#include "graph/block_cut.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < m; i++) cin >> u >> v, g[u] += v, g[v] += u;
    auto bct = block_cut(g);
    cout << bct.size() - n << "\n";
    for (int i = n; i < bct.size(); i++) {
        cout << bct[i].size();
        for (int v : bct[i]) cout << " " << v;
        cout << "\n";
    }
}
