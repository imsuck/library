#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <bits/stdc++.h>
using namespace std;

#include "graph/csr.hpp"
#include "graph/scc.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> es(m);
    for (auto &[u, v] : es) cin >> u >> v;
    CSR<int> g(n, move(es));

    auto scc = find_scc(g);

    cout << scc.size() << "\n";
    for (auto comp : move(scc)) {
        cout << comp.size();
        for (int v : comp) cout << " " << v;
        cout << "\n";
    }
}
