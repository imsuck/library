#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "graph/ael.hpp"
#include "graph/scc.hpp"

int main() {
    int n, m;
    cin >> n >> m;

    AEL<int> g(n);
    for (int u, v; m--;) {
        cin >> u >> v;
        g.add_edge(u, v);
    }

    auto scc = find_scc(g);

    cout << scc.size() << "\n";
    for (auto comp : move(scc)) {
        cout << comp.size();
        for (int v : comp) cout << " " << v;
        cout << "\n";
    }
}
