#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root"

#include <bits/stdc++.h>
using namespace std;

#include "ds/static_top_tree.hpp"
#include "math/modint.hpp"
#include "other/y_combinator.hpp"

using mint = modint998;

struct edge {
    int to, eid;
    operator int() { return to; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<basic_string<edge>> g(n);
    vector<mint> a(n), b(n), c(n);
    for (mint &i : a) cin >> i;
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v >> b[i] >> c[i];
        g[u] += {v, i};
        g[v] += {u, i};
    }
    b[n - 1] = 1, c[n - 1] = 0;

    // convert to arborescence
    vector<int> v_e(n, n - 1), e_v(n, n - 1); // vert to edge/edge to vert
    y_comb([&](auto &dfs, int v, int p) -> void {
        auto it = find(begin(g[v]), end(g[v]), p);
        if (it != g[v].end()) g[v].erase(it);
        for (auto &[u, eid] : g[v]) {
            v_e[u] = eid, e_v[eid] = u;
            dfs(u, v);
        }
    })(0, -1);

    STT stt(g);

    using Point = array<mint, 2>; // sum, size
    using Path = array<mint, 4>;  // sum, size, b, c (for f(x) = bx + c)
    vector<Point> point(stt.size());
    vector<Path> path(stt.size());

    // vertex with an edge attached to it
    auto vertex = [&](int v) -> Path {
        int e = v_e[v];
        return {b[e] * a[v] + c[e], 1, b[e], c[e]};
    };
    // we already applied the point cluster's affine function
    // so just add it to a[v]
    auto add_vertex = [&](Point t, int v) -> Path {
        int e = v_e[v];
        return {b[e] * (a[v] + t[0]) + c[e] * (1 + t[1]), 1 + t[1], b[e], c[e]};
    };
    auto add_edge = [&](Path t) -> Point { return {t[0], t[1]}; };
    // how does child affect the top boundary vertex?
    auto compress = [&](Path p, Path ch) -> Path {
        return {
            p[0] + p[2] * ch[0] + p[3] * ch[1],
            p[1] + ch[1],
            p[2] * ch[2],
            p[2] * ch[3] + p[3],
        };
    };
    // simply combine sum and size
    auto rake = [&](Point l, Point r) -> Point {
        return {l[0] + r[0], l[1] + r[1]};
    };

    auto pull = [&](int v) -> void {
        if (stt[v].t == Vertex) {
            path[v] = vertex(v);
        } else if (stt[v].t == AddVertex) {
            path[v] = add_vertex(point[stt[v].l], v);
        } else if (stt[v].t == AddEdge) {
            point[v] = add_edge(path[stt[v].l]);
        } else if (stt[v].t == Compress) {
            path[v] = compress(path[stt[v].l], path[stt[v].r]);
        } else if (stt[v].t == Rake) {
            point[v] = rake(point[stt[v].l], point[stt[v].r]);
        }
    };

    y_comb([&](auto &dfs, int v) -> void {
        if (stt[v].l != -1) dfs(stt[v].l);
        if (stt[v].r != -1) dfs(stt[v].r);
        pull(v);
    })(stt.rt);

    auto pull_from = [&](int v) {
        for (; v != -1; v = stt[v].p) pull(v);
    };

    while (q--) {
        int op, x, y, z;
        cin >> op;
        if (op == 0) {
            cin >> x >> y;
            a[x] = y;
            pull_from(x);
        } else if (op == 1) {
            cin >> x >> y >> z;
            b[x] = y, c[x] = z;
            pull_from(e_v[x]);
        }
        cout << path[stt.rt][0] << "\n";
    }
}
