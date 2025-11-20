#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum"

#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "tree/top_tree_ecnerwala.hpp"

using mint = modint998;
struct affine {
    mint a = 1, b = 0;
    affine operator()(const affine &g) const { return {a * g.a, a * g.b + b}; }
    mint operator()(mint x) const { return a * x + b; }
};

struct node : top_tree_node_base<node> {
    mint val;
    affine f;
    int subtree_size;
    array<affine, 2> path_affine;
    array<mint, 2> ans;

    void flip() { swap(path_affine[0], path_affine[1]), swap(ans[0], ans[1]); }
    void pull() {
        subtree_size = is_vert;
        path_affine.fill({});
        ans.fill(0);
        for (int i = 0; i <= 2; i++) {
            if (!c[i]) continue;
            subtree_size += c[i]->subtree_size;
        }
        if (is_vert) { // add_vertex(self, rake(c[0], c[1]))
            ans[0] = val;
            for (int i = 0; i < 2; i++) {
                if (!c[i]) continue;
                ans[0] += c[i]->ans[0];
            }
            ans[1] = ans[0];
        } else if (is_path) { // compress(c[0], self, c[1])
            for (int i = 0; i < 2; i++) {
                affine tmp = c[i]->path_affine[i](f);
                path_affine[i] = tmp(c[!i]->path_affine[i]);
                ans[i] = c[i]->ans[i] + tmp.a * c[!i]->ans[i] +
                         tmp.b * c[!i]->subtree_size;
            }
        } else { // rake(c[0], add_edge(self, c[2]), c[1])
            for (int i = 0; i < 2; i++) {
                if (!c[i]) continue;
                ans[0] += c[i]->ans[0];
            }
            ans[0] += f.a * c[2]->ans[0] + f.b * c[2]->subtree_size;
            ans[1] = ans[0];
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<node> t(2 * n - 1);
    for (int i = 0; i < n; i++) {
        cin >> t[i].val;
        t[i].set_vert();
    }
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v >> t[i + n].f.a >> t[i + n].f.b;
        link(t[i + n], t[u], t[v]);
    }
    for (int qi = 0; qi < q; qi++) {
        int op, r;
        cin >> op;
        if (op == 0) {
            int w, x;
            cin >> w >> x;
            t[w].expose();
            t[w].val = x;
            t[w].pull_all();
        } else if (op == 1) {
            int e, y, z;
            cin >> e >> y >> z;
            auto &edge = t[e + n];
            edge.expose_edge();
            edge.f = {y, z};
            edge.pull_all();
        }
        cin >> r;
        t[r].evert();
        cout << t[r].ans[0] << "\n";
    }
}
