#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include <bits/stdc++.h>
using namespace std;

#include "other/blazingio.hpp"

#include "ds/hashmap.hpp"

int main() {
    int q;
    cin >> q;
    hash_map<int64_t, int64_t, chash> m;
    m.set_load_factor(90);
    m.reserve(q);
    while (q--) {
        int t;
        int64_t k, v;
        cin >> t >> k;
        if (t == 0) {
            cin >> v;
            m[k] = v;
        } else {
            cout << m[k] << "\n";
        }
    }
}
