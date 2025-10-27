#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "other/types.hpp"
#include "tree/top_tree_ecnerwala.hpp"

using mint = modint998;

struct affine {
    mint a = 1, b = 0;
    affine operator()(const affine &g) { return {a * g.a, a * g.b + b}; }
    mint operator()(mint x) { return a * x + b; }
};

struct node : top_tree_node_base<node> {
    affine val;
    array<affine, 2> f;

    void flip() { swap(f[0], f[1]); }

    void pull() {
        f.fill(is_vert ? val : affine{1, 0});
        if (c[0]) {
            f[0] = f[0](c[0]->f[0]);
            f[1] = c[0]->f[1](f[1]);
        }
        if (c[1]) {
            f[0] = c[1]->f[0](f[0]);
            f[1] = f[1](c[1]->f[1]);
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<node> a(n);
    for (auto &x : a) {
        cin >> x.val.a >> x.val.b;
        x.set_vert();
    }

    map<pair<i32, i32>, node> edges;
    auto es = [&](i32 u, i32 v) { return &edges[minmax(u, v)]; };

    for (i32 i = 0; i < n - 1; i++) {
        i32 u, v;
        cin >> u >> v;
        link(es(u, v), &a[u], &a[v]);
    }

    while (q--) {
        i32 op;
        cin >> op;
        if (op == 0) {
            i32 u, v, w, x;
            cin >> u >> v >> w >> x;
            auto it = edges.find(minmax(u, v));
            cut(&it->second);
            edges.erase(it);
            link(es(w, x), &a[w], &a[x]);
        } else if (op == 1) {
            i32 p, c, d;
            cin >> p >> c >> d;
            a[p].expose();
            a[p].val = {c, d};
            a[p].pull_all();
        } else {
            i32 u, v, x;
            cin >> u >> v >> x;
            a[u].evert();
            affine f = get_path(&a[v])->f[0];
            cout << f(x) << "\n";
        }
    }
}
