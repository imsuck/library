#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/disjoint_sparse_table.hpp"

struct M {
    using T = int;
    static T id() { return 1.1e9; }
    static T op(T l, T r) { return min(l, r); }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    DisjointSparseTable<M> st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.prod(l, r) << "\n";
    }
}
