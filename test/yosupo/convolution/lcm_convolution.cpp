#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include <bits/stdc++.h>
using namespace std;

#include "math/modint.hpp"
#include "math/zeta_moebius_transform.hpp"

using mint = modint998;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<mint> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto c = lcm_convolution(a, b);
    for (int i = 1; i <= n; i++) cout << c[i] << " \n"[i == n];
}
