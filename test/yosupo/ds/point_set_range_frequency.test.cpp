#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include <bits/stdc++.h>
using namespace std;

#include "ds/ordered_set.hpp"

template<class T> struct PointSetRangeFreq {
    vector<T> a;
    ordered_set<pair<T, int>> s;

    PointSetRangeFreq(const vector<T> &v) : a(v) {
        for (int i = 0; i < a.size(); i++) s.insert({a[i], i});
    }
    void set(int p, T x) {
        s.erase({a[p], p});
        s.insert({a[p] = x, p});
    }
    int query(int l, int r, T x) {
        return s.order_of({x, r}) - s.order_of({x, l}, false);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    PointSetRangeFreq<int> rf(a);
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int k, v;
            cin >> k >> v;
            rf.set(k, v);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            cout << rf.query(l, r, x) << "\n";
        }
    }
}
