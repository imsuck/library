#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root"

#include <bits/stdc++.h>
using namespace std;

#include "tree/static_top_tree.hpp"
#include "tree/dynamic_tree_dp.hpp"
#include "math/modint.hpp"
#include "other/y_combinator.hpp"

using mint = modint998;

struct edge {
    int to, eid;
    operator int() { return to; }
};

struct TreeDP {
    struct Info {
        mint a, b, c;
    };
    struct Point {
        mint sum, sz;
    };
    struct Path {
        mint sum, sz, b, c;
    };
    static Path vertex(Info x) { return {x.b * x.a + x.c, 1, x.b, x.c}; }
    static Path add_vertex(Point t, Info x) {
        return {x.b * (x.a + t.sum) + x.c * (1 + t.sz), 1 + t.sz, x.b, x.c};
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
    vector<basic_string<edge>> g(n);
    vector<mint> a(n), b(n), c(n);
    for (mint &i : a) cin >> i;
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v >> b[i] >> c[i];
        g[u] += {v, i}, g[v] += {u, i};
    }
    b[n - 1] = 1, c[n - 1] = 0;

    vector<int> v_e(n, n - 1), e_v(n, n - 1);
    y_comb([&](auto &dfs, int v, int p) -> void {
        auto it = find(begin(g[v]), end(g[v]), p);
        if (it != end(g[v])) g[v].erase(it);
        for (auto [u, eid] : g[v]) v_e[u] = eid, e_v[eid] = u, dfs(u, v);
    })(0, -1);

    STT stt(g);
    DDP ddp(n, stt, TreeDP());
    for (int i = 0; i < n; i++) {
        int e = v_e[i];
        ddp.info[i] = {a[i], b[e], c[e]};
    }
    ddp.build();

    while (q--) {
        int op, x, y, z;
        cin >> op;
        if (op == 0) {
            cin >> x >> y;
            ddp.info[x].a = y;
            ddp.pull_from(x);
        } else {
            cin >> x >> y >> z;
            int v = e_v[x];
            ddp.info[v].b = y, ddp.info[v].c = z;
            ddp.pull_from(v);
        }
        cout << ddp.query().sum << "\n";
    }
}
