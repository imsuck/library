#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/ordered_set.hpp"

int main() {
    int n, q;
    cin >> n >> q;

    ordered_set<int> s;
    for (int i = 0, a; i < n; i++) cin >> a, s.insert(a);

    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 0) {
            s.insert(x);
        } else if (t == 1) {
            s.erase(x);
        } else if (t == 2) {
            cout << s.kth_order(x).value_or(-1) << "\n";
        } else if (t == 3) {
            cout << s.order_of(x) << "\n";
        } else if (t == 4) {
            cout << s.pre_upper_bound(x).value_or(-1) << "\n";
        } else {
            cout << s.lower_bound(x).value_or(-1) << "\n";
        }
    }
}

