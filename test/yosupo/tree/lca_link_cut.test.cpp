#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;

#include "tree/link_cut.hpp"

struct node : lct_node<node> {
    void pull() {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    LCT<node> lct(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        lct.link(i, p);
    }
    lct.evert(0);
    while (q--) {
        int u, v;
        cin >> u >> v, cout << lct.lca(u, v) << "\n";
    }
}

