#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;

#include "tree/top_tree_ecnerwala.hpp"

struct node : top_tree_node_base<node> {};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<node> a(2 * n - 1);
    for (int i = 0; i < n; i++) a[i].set_vert();
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        link(&a[n + i - 1], &a[i], &a[p]);
    }
    a[0].evert();
    while (q--) {
        int u, v;
        cin >> u >> v, cout << int(lca(&a[u], &a[v]) - &a[0]) << "\n";
    }
}
