#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include <bits/stdc++.h>
using namespace std;

#include "ds/swag.hpp"
#include "math/modint.hpp"

using mint = modint998;

struct M {
    struct T {
        mint a = 1, b = 0;
        mint operator()(mint x) { return a * x + b; }
    };
    static T id() { return {}; }
    static T op(T l, T r) { return {r.a * l.a, r.a * l.b + r.b}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    SWAG<M> swag;
    while (q--) {
        int op, a, b, x;
        cin >> op;
        if (op == 0) {
            cin >> a >> b;
            swag.push({a, b});
        } else if (op == 1) {
            swag.pop();
        } else {
            cin >> x;
            cout << swag.query()(x) << "\n";
        }
    }
}
