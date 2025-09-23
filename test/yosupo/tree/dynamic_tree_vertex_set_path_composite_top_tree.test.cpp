#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;

#include "graph/top_tree.hpp"
#include "math/modint.hpp"
#include "other/types.hpp"

using mint = modint998;

struct TreeDP {
    struct Info {
        mint a, b;
    };
    struct Point {};
    struct Path {
        mint a, b;
    };
    static Path vertex(Info x) { return {x.a, x.b}; }
    static Path add_vertex(Point, Info) { return {1, 0}; }
    static Point add_edge(Path t) { return {}; }
    static Path compress(Path p, Path c) {
        return {c.a * p.a, c.a * p.b + c.b};
    }
    static Point rake(Point, Point) { return {}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, q;
    cin >> n >> q;
    vector<TreeDP::Info> a(n);
    for (auto &[b, c] : a) cin >> b >> c;
    TopTree<TreeDP> tr(a);
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
            tr.set(p, {c, d});
        } else {
            i32 u, v, x;
            cin >> u >> v >> x;
            auto [a, b] = tr.fold_path(u, v);
            cout << a * x + b << "\n";
        }
    }
}
