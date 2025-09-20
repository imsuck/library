#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "math/zeta_moebius_transform.hpp"

using mint = modint998;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<mint> a(n), b(n);
    for (mint &i : a) cin >> i;
    for (mint &i : b) cin >> i;
    auto c = gcd_convolution(a, b);
    for (int i = 0; i < n; i++) cout << c[i] << " \n"[i == n - 1];
}
