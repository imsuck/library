#pragma once

// clang-format off
struct XorTree {
    XorTree() {}
    XorTree(int _n) : n(_n), par(n), deg(n) {}

    void add_edge(int u, int v) {
        par[u] ^= v, par[v] ^= u, deg[u]++, deg[v]++;
    }
    void set_root(int v) { root = v, deg[v] = -1; }

    template<class F1, class F2> void run(F1 &&apply_edge, F2 &&apply_vertex) {
        assert(root != -1 && "no root set");
        for (int i = 0; i < n; i++) {
            int v = i;
            for (int p; deg[v] == 1; v = p) {
                p = par[v];
                deg[v]--, deg[p]--, par[p] ^= v;
                apply_vertex(v), apply_edge(p, v);
            }
        }
        apply_vertex(root), par[root] = -1;
    }
    auto dfs_ord() {
        int id = n;
        vector<int> sz(n, 1), ord(n);
        run(
            [&](int v, int c) { sz[v] += sz[c]; },
            [&](int v) { ord[--id] = v; }
        );
        for (int i = 1; i < n; i++) {
            int v = ord[i], p = par[v];
            tie(sz[v], sz[p]) = make_pair(sz[p], sz[p] - sz[v]);
        }
        for (int i = 0; i < n; i++) ord[--sz[i]] = i;
        return make_pair(ord, sz);
    }

  private: int n, root = -1;
  public:  vector<int> par;
  private: vector<int> deg;
};
// clang-format on
