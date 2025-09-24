#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include <bits/stdc++.h>
using namespace std;

#include "other/compressor.hpp"
#include "other/mo.hpp"

struct fenwick_tree {
    int n;
    vector<int> t;

    fenwick_tree(int _n) : n(_n), t(n + 1) {}

    void add(int p, int d) {
        for (p++; p <= n; p += p & -p) t[p] += d;
    }
    int pref(int r) const {
        int s = 0;
        for (; r; r &= r - 1) s += t[r];
        return s;
    }
    int suf(int l) const { return pref(n) - pref(l); }
    int sum(int l, int r) const { return pref(r) - pref(l); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    Compressor comp;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    comp.push(a);
    int m = comp.build();
    vector<pair<int, int>> qs(q);
    for (auto &[l, r] : qs) cin >> l >> r;
    Mo mo(n, move(qs));

    int64_t inv = 0;
    fenwick_tree tr(m);
    vector<int64_t> ans(q);
    mo.run(
        [&](int i) { ans[i] = inv; },
        [&](int i) { inv += tr.pref(a[i]), tr.add(a[i], +1); },
        [&](int i) { inv -= tr.pref(a[i]), tr.add(a[i], -1); },
        [&](int i) { inv += tr.suf(a[i] + 1), tr.add(a[i], +1); },
        [&](int i) { inv -= tr.suf(a[i] + 1), tr.add(a[i], -1); }
    );
    for (auto i : ans) cout << i << "\n";
}
