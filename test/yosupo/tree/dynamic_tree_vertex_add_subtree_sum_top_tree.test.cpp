#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;

#include "tree/top_tree.hpp"
#include "other/types.hpp"

struct TreeDP {
    using Info = i64;
    using Point = i64;
    using Path = i64;
    static Path vertex(Info x) { return x; }
    static Path add_vertex(Point t, Info x) { return t + x; }
    static Point add_edge(Path t) { return t; }
    static Path compress(Path p, Path c) { return p + c; }
    static Point rake(Point l, Point r) { return l + r; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, q;
    cin >> n >> q;
    TopTree<TreeDP> tree(n);
    for (i32 i = 0, a; i < n; i++) cin >> a, tree.set(i, a);
    for (i32 i = 0, u, v; i < n - 1; i++) cin >> u >> v, tree.link(u, v);

    while (q--) {
        i32 op, a, b, c, d;
        cin >> op;
        if (op == 0) {
            cin >> a >> b >> c >> d;
            tree.cut(a, b), tree.link(c, d);
        } else if (op == 1) {
            cin >> a >> b;
            tree.apply(a, [b](auto &x) { x += b; });
        } else {
            cin >> a >> b;
            cout << tree.fold_subtree(a, b) << "\n";
        }
    }
}
