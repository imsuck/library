#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;

#include "tree/link_cut.hpp"
#include "math/modint.hpp"
#include "other/types.hpp"

using mint = modint998;

struct node : lct_node<node> {
    using lct_node<node>::lct_node;

    using T = array<mint, 2>;
    T val{1, 0};
    array<T, 2> path{
        {{1, 0}, {1, 0}}
    };

    void set(i32 a, i32 b) { val = {a, b}; }

    T op(T l, T r) { return {l[0] * r[0], l[0] * r[1] + l[1]}; }
    void pull() {
        path[0] = op(op($(r)->path[0], val), $(l)->path[0]);
        path[1] = op(op($(l)->path[1], val), $(r)->path[1]);
    }
    void flip() { swap(path[0], path[1]); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, q;
    cin >> n >> q;
    LCT<node> tr(n);
    for (i32 i = 0, a, b; i < n; i++) cin >> a >> b, tr[i]->set(a, b);
    for (i32 i = 0, u, v; i < n - 1; i++) cin >> u >> v, tr.link(u, v);
    while (q--) {
        i32 t;
        cin >> t;
        if (t == 0) {
            i32 a, b, c, d;
            cin >> a >> b >> c >> d;
            tr.cut(a, b), tr.link(c, d);
        } else if (t == 1) {
            i32 p, c, d;
            cin >> p >> c >> d;
            tr.set(p, c, d);
        } else {
            i32 u, v, x;
            cin >> u >> v >> x;
            tr.expose_path(u, v);
            auto [a, b] = tr[v]->path[0];
            cout << a * x + b << "\n";
        }
    }
}
