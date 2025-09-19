#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include <bits/stdc++.h>
using namespace std;
#include "other/blazingio.hpp"

#include "other/two_sat.hpp"

int main() {
    int n, m;
    string buf;
    cin >> buf >> buf >> n >> m;
    TwoSAT solver(n);
    while (m--) {
        int x, y;
        cin >> x >> y >> buf;
        x = x < 0 ? ~(-x - 1) : x - 1;
        y = y < 0 ? ~(-y - 1) : y - 1;
        solver.add_or(x, y);
    }
    auto assignment = solver.run();
    if (assignment.empty()) {
        cout << "s UNSATISFIABLE\n";
        return 0;
    }
    cout << "s SATISFIABLE\nv ";
    for (int i = 0; i < n; i++)
        cout << (assignment[i] ? 1 : -1) * (i + 1) << " ";
    cout << "0\n";
}
