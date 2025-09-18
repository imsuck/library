#pragma once

#include "../graph/scc.hpp"

struct TwoSAT {
    int n;
    vector<basic_string<int>> g;

    TwoSAT(int _n) : n(_n), g(2 * n) {}

    void add_if(int x, int y) { g[ev(x)] += ev(y), g[ev(~y)] += ev(~x); }
    void add_or(int x, int y) { add_if(~x, y); }
    void add_nand(int x, int y) { add_if(x, ~y); }
    void set_true(int x) { add_if(~x, x); }
    void set_false(int x) { add_if(x, ~x); }

    vector<bool> run() {
        vector<bool> res(n);
        auto [scc, rep, gd] = condense(g);
        for (int i = 0; i < n; i++) {
            if (rep[i] == rep[i + n]) return {};
            res[i] = rep[i] > rep[i + n];
        }
        return res;
    }

    int ev(int x) { return x < 0 ? ~x + n : x; }
};
