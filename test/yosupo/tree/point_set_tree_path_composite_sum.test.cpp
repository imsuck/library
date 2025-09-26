#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum"

#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "tree/top_tree.hpp"

using mint = modint998;

struct TreeDP {
    struct Info {
        bool is_vertex;
        mint a, b;
    };
    struct Point {
        mint sum, sz;
    };
    struct Path {
        mint sum, sz, b, c;
    };
    static Path vertex(Info x) {
        if (x.is_vertex) return {x.a, 1, 1, 0};
        return {0, 0, x.a, x.b};
    }
    static Path add_vertex(Point t, Info x) {
        if (x.is_vertex) return {t.sum + x.a, t.sz + 1, 1, 0};
        return {x.a * t.sum + x.b * t.sz, t.sz, x.a, x.b};
    }
    static Point add_edge(Path t) { return {t.sum, t.sz}; }
    // how does child affect the top boundary vertex?
    static Path compress(Path p, Path c) {
        return {
            p.sum + p.b * c.sum + p.c * c.sz,
            p.sz + c.sz,
            p.b * c.b,
            p.b * c.c + p.c
        };
    }
    static Point rake(Point l, Point r) { return {l.sum + r.sum, l.sz + r.sz}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    TopTree<TreeDP> tr(2 * n - 1);
    for (int i = 0, a; i < n; i++) cin >> a, tr.set(i, {true, a, 0});
    for (int i = 0, u, v, b, c; i < n - 1; i++) {
        cin >> u >> v >> b >> c;
        tr.set(i + n, {false, b, c});
        tr.link(u, i + n);
        tr.link(v, i + n);
    }
    while (q--) {
        int op, r;
        cin >> op;
        if (op == 0) {
            int w, x;
            cin >> w >> x >> r;
            tr.set(w, {true, x, 0});
        } else {
            int e, y, z;
            cin >> e >> y >> z >> r;
            tr.set(e + n, {false, y, z});
        }
        cout << tr.fold(r).sum << "\n";
    }
}
