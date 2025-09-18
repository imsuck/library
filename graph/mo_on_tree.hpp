#pragma once

#include "../other/mo.hpp"

template<int LG> struct MoOnTree {
    int n, qi = 0;
    vector<int> in, out, tour, w;
    vector<pair<int, int>> qs;
    array<vector<int>, LG> up;

    MoOnTree() {}
    template<class G>
    MoOnTree(G &g, int q, int root = 0) :
        n((int)g.size()), in(n), out(n), tour(2 * n), w(q), qs(q) {
        up.fill(vector<int>(n, -1));
        int t = 0;
        auto dfs = [&](auto &self, int v, int p = -1) -> void {
            up[0][v] = p;
            for (int l = 0; l + 1 < LG && up[l][v] != -1; l++)
                up[l + 1][v] = up[l][up[l][v]];
            tour[t] = v, in[v] = t++;
            for (int c : g[v]) {
                if (c == p) continue;
                self(self, c, v);
            }
            tour[t] = v, out[v] = t++;
        };
        dfs(dfs, root);
    }

    void add_query(int u, int v) {
        if (in[u] > in[v]) swap(u, v);
        w[qi] = lca(u, v);
        qs[qi] = {w[qi] == u ? in[u] : out[u], in[v] + 1};
        qi++;
    }

    template<class Eval, class Add, class Del>
    void run(Eval eval, Add add, Del del) {
        Mo mo(2 * n, qs);
        vector<bool> vis(n);
        auto mod = [&](int v) {
            v = tour[v], (vis[v] = !vis[v]) ? add(v) : del(v);
        };
        mo.run(
            [&](int i) {
                auto [u, v] = qs[i];
                u = tour[u], v = tour[v - 1];
                if (w[i] != u && w[i] != v) add(w[i]);
                eval(i);
                if (w[i] != u && w[i] != v) del(w[i]);
            },
            mod,
            mod
        );
    }

    bool anc(int p, int v) const {
        return p == -1 || (in[p] <= in[v] && out[v] <= out[p]);
    }
    int lca(int u, int v) {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;
        for (int l = LG - 1; l >= 0; l--)
            if (!anc(up[l][u], v)) u = up[l][u];
        return up[0][u];
    };
};
