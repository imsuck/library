#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;

#include "tree/lazy_ett.hpp"
#include "other/types.hpp"

struct M {
    struct T {
        int64_t sm = 0;
        int sz = 0;
    };
    using F = int64_t;
    static T id() { return {}; }
    static F fid() { return 0; }
    static T op(const T &l, const T &r) { return {l.sm + r.sm, l.sz + r.sz}; }
    static F comp(F l, F r) { return l + r; }
    static T map(F f, const T &x) { return {x.sm + f * x.sz, x.sz}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, q;
    cin >> n >> q;
    LazyETT<M> tr(n);
    for (i32 i = 0, a; i < n; i++) cin >> a, tr.set(i, {a, 1});
    for (i32 i = 0, u, v; i < n - 1; i++) cin >> u >> v, tr.link(u, v);
    while (q--) {
        i32 t;
        cin >> t;
        if (t == 0) {
            i32 a, b, c, d;
            cin >> a >> b >> c >> d;
            tr.cut(a, b), tr.link(c, d);
        } else if (t == 1) {
            i32 v, p, x;
            cin >> v >> p >> x;
            tr.apply(v, p, x);
        } else {
            i32 v, p;
            cin >> v >> p;
            cout << tr.subtree_prod(v, p).sm << "\n";
        }
    }
}
