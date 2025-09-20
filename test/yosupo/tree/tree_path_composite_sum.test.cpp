#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include <bits/stdc++.h>
using namespace std;

#include "graph/rerooting.hpp"
#include "math/modint.hpp"

using mint = modint998;

struct Monoid {
    using T = array<mint, 2>;
    using Cost = array<mint, 2>;

    static T id() { return {0, 0}; }
    static T op(const T &l, const T &r) { return {l[0] + r[0], l[1] + r[1]}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<mint> a(n);
    for (mint &i : a) cin >> i;
    Rerooting<Monoid> dp(n);
    for (int i = 0, u, v, b, c; i < n - 1; i++) {
        cin >> u >> v >> b >> c;
        dp.add_edge(u, v, {b, c});
    }
    using T = Monoid::T;
    using Cost = Monoid::Cost;
    auto res = dp.run(
        [](const T &x, int, int, const Cost &c) -> T {
            return {x[0] * c[0] + x[1] * c[1], x[1]};
        },
        [&a](const T &x, int v) -> T { return {x[0] + a[v], x[1] + 1}; }
    );
    for (int i = 0; i < n; i++) cout << res[i][0] << " \n"[i == n - 1];
}
