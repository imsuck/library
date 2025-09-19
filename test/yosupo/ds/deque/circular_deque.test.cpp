#define PROBLEM "https://judge.yosupo.jp/problem/deque"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "ds/circular_deque.hpp"

CircularDeque<int, 500'000> dq;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    
    while (q--) {
        int t, x;
        cin >> t;
        if (t == 0) {
            cin >> x;
            dq.push_front(x);
        } else if (t == 1) {
            cin >> x;
            dq.push_back(x);
        } else if (t == 2) {
            dq.pop_front();
        } else if (t == 3) {
            dq.pop_back();
        } else {
            cin >> x;
            cout << dq[x] << "\n";
        }
    }
}
