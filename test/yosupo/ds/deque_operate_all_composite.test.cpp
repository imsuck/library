#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/deque_aggregation.hpp"
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
    int q;
    cin >> q;
    DequeAggregation<M> dq;
    while (q--) {
        int op, a, b, x;
        cin >> op;
        if (op == 0 || op == 1) {
            cin >> a >> b;
            op == 0 ? dq.push_front({a, b}) : dq.push_back({a, b});
        } else if (op == 2 || op == 3) {
            op == 2 ? dq.pop_front() : dq.pop_back();
        } else {
            cin >> x;
            cout << (int)dq.query()(x) << "\n";
        }
    }
}
