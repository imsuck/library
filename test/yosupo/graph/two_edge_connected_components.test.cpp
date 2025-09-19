#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "graph/bridge_tree.hpp"

int main() {
    int n, m;
    cin >> n >> m;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u] += v, g[v] += u;
    }

    auto id = two_cc(g);
    int k = *max_element(begin(id), end(id)) + 1;
    vector<basic_string<int>> ccs(k);
    for (int i = 0; i < n; i++) ccs[id[i]] += i;
    cout << ccs.size() << "\n";
    for (auto cc : ccs) {
        cout << cc.size();
        for (int v : cc) cout << " " << v;
        cout << "\n";
    }
}
