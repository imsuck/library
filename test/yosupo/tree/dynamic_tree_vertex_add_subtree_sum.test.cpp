#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "graph/link_cut.hpp"
#include "other/types.hpp"

struct node : lct_node<node> {
    using lct_node<node>::lct_node;

    i64 val = 0, sum = 0, light = 0;

    void set(i32 x) { val = x; }
    void add(i32 x) { val += x; }

    void pull() { sum = $(l)->sum + $(r)->sum + val + light; }
    void add_light(ptr c) { light += c->sum; }
    void sub_light(ptr c) { light -= c->sum; }
};

int main() {
    i32 n, q;
    cin >> n >> q;
    LCT<node> tr(n);
    for (i32 i = 0, a; i < n; i++) cin >> a, tr[i]->set(a);
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
            tr.add(p, x);
        } else {
            i32 v, p;
            cin >> v >> p;
            tr.cut(v, p);
            cout << tr[v]->sum << "\n";
            tr.link(v, p);
        }
    }
}
