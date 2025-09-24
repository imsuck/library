#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>
using namespace std;

#include "ds/wavelet_matrix.hpp"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    int mx = 0;
    for (int &i : v) cin >> i, mx = max(mx, i);
    WaveletMatrix<int> wm(v);
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << wm.kth_smallest(l, r, k) << "\n";
    }
}
