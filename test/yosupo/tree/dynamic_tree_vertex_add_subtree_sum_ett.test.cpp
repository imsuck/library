#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;

#include "graph/ett.hpp"
#include "other/types.hpp"

struct M {
    using T = i64;
    static T id() { return 0; }
    static T op(T l, T r) { return l + r; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, q;
    cin >> n >> q;
    ETT<M> tr(n);
    for (i32 i = 0, a; i < n; i++) cin >> a, tr.set(i, a);
    for (i32 i = 0, u, v; i < n - 1; i++) cin >> u >> v, tr.link(u, v);
    while (q--) {
        i32 t;
        cin >> t;
        if (t == 0) {
            i32 a, b, c, d;
            cin >> a >> b >> c >> d;
            tr.cut(a, b), tr.link(c, d);
        } else if (t == 1) {
            i32 p, x;
            cin >> p >> x;
            tr.set(p, tr.get(p) + x);
        } else {
            i32 v, p;
            cin >> v >> p;
            cout << tr.subtree_prod(v, p) << "\n";
        }
    }
}
