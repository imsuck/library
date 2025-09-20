#define PROBLEM "https://judge.yosupo.jp/problem/incremental_minimum_spanning_forest"

#include <bits/stdc++.h>
using namespace std;

#include "graph/link_cut.hpp"

struct node : lct_node<node> {
    using lct_node<node>::lct_node;

    pair<int, int> val{0, -1}, path{0, -1};

    void pull() { path = max({$(l)->path, val, $(r)->path}); }

    void set(pair<int, int> a) { val = a; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    LCT<node> tr(n + m);
    vector<int> v(m), u(m);
    for (int i = 0, w; i < m; i++) {
        cin >> u[i] >> v[i] >> w;
        tr.set(i + n, pair{w, i});
        int ans = -1;
        if (u[i] == v[i]) {
            cout << i << "\n";
            continue;
        }
        if (tr.lca(u[i], v[i]) == -1) {
            cout << -1 << " \n"[i == m - 1];
            tr.link(u[i], i + n);
            tr.link(v[i], i + n);
            continue;
        }
        tr.expose_path(u[i], v[i]);
        auto [mx, id] = tr[v[i]]->path;
        if (w > mx) {
            ans = i;
        } else {
            ans = id;
            tr.cut(u[id], id + n), tr.cut(v[id], id + n);
        }
        cout << ans << " \n"[i == m - 1];
        if (ans != i) {
            tr.link(u[i], i + n);
            tr.link(v[i], i + n);
        }
    }
}
