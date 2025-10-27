#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;

#include "other/types.hpp"
#include "tree/top_tree_ecnerwala.hpp"

struct node : top_tree_node_base<node> {
    int sz = 0;
    i64 val = 0, sum = 0, lz = 0;

    void apply(i64 x) {
        lz += x;
        sum += x * sz;
        if (is_vert) val += x;
    }

    void push() {
        for (int i = 0; i < 3; i++) {
            if (!c[i]) continue;
            c[i]->apply(lz);
        }
        lz = 0;
    }

    void pull() {
        sum = is_vert ? val : 0;
        sz = is_vert;
        for (int i = 0; i < 3; i++) {
            if (!c[i]) continue;
            sum += c[i]->sum;
            sz += c[i]->sz;
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<node> vert(n);
    for (int i = 0; i < n; i++) {
        cin >> vert[i].val;
        vert[i].set_vert();
    }

    map<pair<int, int>, node> edges;
    auto es = [&edges](int u, int v) { return &edges[minmax(u, v)]; };

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        link(es(u, v), &vert[u], &vert[v]);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            auto it = edges.find(minmax(u, v));
            cut(&it->second);
            edges.erase(it);
            link(es(w, x), &vert[w], &vert[x]);
        } else if (op == 1) {
            int v, p, x;
            cin >> v >> p >> x;
            vert[p].evert();
            node *sub = get_subtree(&vert[v]);
            sub->apply(x);
            sub->pull_all();
        } else {
            int v, p;
            cin >> v >> p;
            vert[p].evert();
            auto sub = get_subtree(&vert[v]);
            cout << sub->sum << "\n";
        }
    }
}
