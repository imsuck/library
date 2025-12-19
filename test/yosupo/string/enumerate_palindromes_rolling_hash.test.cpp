#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <bits/stdc++.h>
using namespace std;

#include "ds/disjoint_sparse_table.hpp"
#include "ds/rolling_hash_static.hpp"
#include "other/types.hpp"

struct Monoid {
    using hasher = RollingHashStatic<>;
    using T = array<u64, 3>;
    static T id() { return {}; }
    static T op(const T &l, const T &r) {
        return {
            hasher::concat(l[0], r[0], (i32)r[2]),
            hasher::concat(r[1], l[1], (i32)l[2]),
            l[2] + r[2],
        };
    }
};

template<class F, class I = i32> void binary_search(I &l, I &r, F &&pred) {
    while (r - l > 1) {
        I m = l + (r - l) / 2;
        (pred(m) ? l : r) = m;
    }
}

void solve() {
    string _s, s = "#";
    cin >> _s;
    for (char c : _s) s += c + "#"s;
    i32 n = (i32)s.size();
    DisjointSparseTable<Monoid> st((i32)s.size(), [&](i32 i) -> Monoid::T {
        return {(u64)s[i], (u64)s[i], 1};
    });
    for (i32 i = 1; i < n - 1; i++) {
        i32 l = 1, r = max({1, min(i + 1, n - i)}) + 1;
        binary_search(l, r, [&](i32 x) -> bool {
            auto cur = st.prod(i - x + 1, i + x);
            return cur[0] == cur[1];
        });
        cout << l - 1 << " \n"[i == n - 2];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
