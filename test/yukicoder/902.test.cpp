#define PROBLEM "https://yukicoder.me/problems/no/902"

#include <bits/stdc++.h>
using namespace std;

#include "other/types.hpp"
#include "tree/top_tree_ecnerwala.hpp"

struct node : top_tree_node_base<node> {
    bool open = false, has_open = false;
    i32 weight = 0;
    i64 path_weight = 0, ans = 0;
    array<i64, 2> lweight{0, 0};

    void flip() { swap(lweight[0], lweight[1]); }

    void pull() {
        has_open = open;
        path_weight = 0;
        lweight.fill(0);
        ans = 0;
        for (int z = 0; z <= 2; z++) {
            if (!c[z]) continue;
            has_open |= c[z]->has_open;
            ans += c[z]->ans;
        }
        if (!is_vert && is_path) {
            path_weight = c[0]->path_weight + weight + c[1]->path_weight;
            for (int z = 0; z < 2; z++) {
                lweight[z] = c[!z]->has_open ? c[z]->path_weight + weight +
                                                   c[!z]->lweight[z]
                                             : c[z]->lweight[z];
            }
        } else if (!is_path) {
            ans += c[2]->lweight[0] + c[2]->has_open * weight;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n;
    cin >> n;
    vector<node> t(2 * n - 1);
    map<pair<int, int>, int> edge_id;
    for (i32 i = 0; i < n; i++) t[i].set_vert();
    for (i32 i = n; i < 2 * n - 1; i++) {
        i32 u, v;
        cin >> u >> v >> t[i].weight;
        link(t[i], t[u], t[v]);
        edge_id[minmax(u, v)] = i;
    }
    i32 q;
    cin >> q;
    while (q--) {
        i32 op;
        cin >> op;
        if (op == 1) {
            i32 u, v, w, x;
            cin >> u >> v >> w >> x;
            auto it = edge_id.find(minmax(u, v));
            int z = it->second;
            edge_id.erase(it);
            cut(t[z]);
            t[z].weight = x;
            link(t[z], t[v], t[w]);
            edge_id[minmax(v, w)] = z;
        } else if (op == 2) {
            int k;
            cin >> k;
            vector<int> xs(k);
            for (int &x : xs) {
                cin >> x;
                t[x].expose();
                t[x].open = true;
                t[x].pull_all();
            }
            t[xs[0]].evert();
            cout << t[xs[0]].ans << "\n";
            for (int x : xs) {
                t[x].expose();
                t[x].open = false;
                t[x].pull_all();
            }
        }
    }
}
