#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "graph/csr.hpp"
#include "graph/hld.hpp"

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> es(n - 1);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        es[i - 1] = {p, i};
    }
    CSR<int> g(n, move(es));
    HLD hld(g);
    while (q--) {
        int u, v;
        cin >> u >> v, cout << hld.lca(u, v) << "\n";
    }
}
