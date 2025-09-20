#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <bits/stdc++.h>
using namespace std;

#include "graph/dinitz.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int l, r, m;
    cin >> l >> r >> m;

    Dinitz<int> g(l + r + 2);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v + l, 1);
    }

    for (int i = 0; i < l; i++) g.add_edge(l + r, i, 1);
    for (int i = l; i < l + r; i++) g.add_edge(i, l + r + 1, 1);

    cout << g.max_flow(l + r, l + r + 1) << "\n";
    for (int i = 0; i < l; i++)
        for (auto &e : g.g[i])
            if (e.cap == 0 && e.to < l + r)
                cout << i << " " << e.to - l << "\n";
}
