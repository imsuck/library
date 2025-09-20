#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include <bits/stdc++.h>
using namespace std;

#include "math/stern_brocot_tree.hpp"

using node = sbt_node<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;

    while (q--) {
        string op;
        cin >> op;
        if (op == "ENCODE_PATH") {
            int a, b;
            cin >> a >> b;
            auto path = node(a, b).path();
            cout << path.size();
            for (auto [d, n] : path)
                cout << ' ' << (!d ? 'L' : 'R') << ' ' << n;
            cout << '\n';
        } else if (op == "DECODE_PATH") {
            int k;
            cin >> k;
            node::sbt_path path(k);
            for (int i = 0; i < k; i++) {
                char d;
                int n;
                cin >> d >> n;
                path[i] = {d == 'R', n};
            }
            auto [a, b] = node(path).get();
            cout << a << ' ' << b << '\n';
        } else if (op == "LCA") {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            auto [f, g] = lca(node(a, b), node(c, d)).get();
            cout << f << ' ' << g << '\n';
        } else if (op == "ANCESTOR") {
            int k, a, b;
            cin >> k >> a >> b;
            auto x = node(a, b);
            if (x.go_up(x.depth() - k)) {
                tie(a, b) = x.get();
                cout << a << ' ' << b << '\n';
            } else {
                cout << "-1\n";
            }
        } else if (op == "RANGE") {
            int a, b;
            cin >> a >> b;
            auto [l, r] = node(a, b).range();
            auto [f, g] = l;
            auto [h, k] = r;
            cout << f << ' ' << g << ' ' << h << ' ' << k << '\n';
        }
    }
}
