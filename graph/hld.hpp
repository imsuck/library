#pragma once

struct HLD {
    int n;
    vector<int> in, par, dep, out, hs;

    template<class G>
    HLD(G &g, int root = 0) :
        n((int)g.size()), in(n), par(n), dep(n), out(n), hs(n) {
        hs[root] = root;
        dfs_sz(g, root);
        dfs_hld(g, root);
        assert(time == n);
    }

    int lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        for (;; v = par[hs[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (hs[u] == hs[v]) return u;
        }
    }
    int dist(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    auto path(int v, int p, bool es = 0) const {
        assert(in[p] <= in[v] && out[v] <= out[p]);
        vector<pair<int, int>> res;
        for (; hs[v] != hs[p]; v = par[hs[v]])
            res.emplace_back(in[hs[v]], in[v] + 1);
        res.emplace_back(in[p] + es, in[v] + 1);
        return res;
    }
    pair<int, int> subtree(int v) const {
        assert(0 <= v && v < n);
        return {in[v], out[v]};
    }
    int operator[](int v) { return in[v]; }
    int operator()(int v) { return out[v]; }

  private:
    int time = 0;
    template<class G> int dfs_sz(G &g, int v, int p = -1) {
        par[v] = p;
        int sz = 1, mx = 0;
        for (int &c : g[v]) {
            if (c == p) continue;
            dep[c] = dep[v] + 1;
            int s = dfs_sz(g, c, v);
            sz += s;
            if (g[v][0] == p || mx < s) mx = s, swap(g[v][0], c);
        }
        return sz;
    }
    template<class G> void dfs_hld(G &g, int v, int p = -1) {
        in[v] = time++;
        for (int c : g[v]) {
            if (c == p) continue;
            hs[c] = (c == g[v][0] ? hs[v] : c);
            dfs_hld(g, c, v);
        }
        out[v] = time;
    }
};
