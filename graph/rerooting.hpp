#pragma once

template<class M> struct Rerooting {
    using T = typename M::T;
    using Cost = typename M::Cost;

    Rerooting(int n) : g(n) {}

    void add_edge(int u, int v, const Cost &c) {
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }

    template<class F1, class F2> vector<T> run(F1 &&f1, F2 &&f2) {
        apply_edge = f1, apply_vertex = f2;
        dp_sub.assign(g.size(), M::id()), dp_all.resize(g.size());
        dfs_sub(0, -1);
        dfs_all(0, -1, M::id());
        return dp_all;
    }

  private:
    vector<vector<pair<int, Cost>>> g;
    function<T(T, int, int, Cost)> apply_edge;
    function<T(T, int)> apply_vertex;
    vector<T> dp_sub, dp_all;

    void dfs_sub(int v, int p) {
        for (auto &[c, cost] : g[v]) {
            if (c == p) continue;
            dfs_sub(c, v);
            dp_sub[v] = M::op(dp_sub[v], apply_edge(dp_sub[c], v, c, cost));
        }
        dp_sub[v] = apply_vertex(dp_sub[v], v);
    }
    void dfs_all(int v, int p, const T &val) {
        vector ds = {val};
        for (auto &[c, cost] : g[v]) {
            if (c == p) continue;
            ds.push_back(apply_edge(dp_sub[c], v, c, cost));
        }
        int n = (int)ds.size();
        vector head(n + 1, M::id()), tail(n + 1, M::id());
        for (int i = 0; i < n; i++) head[i + 1] = M::op(head[i], ds[i]);
        for (int i = n; i--;) tail[i] = M::op(ds[i], tail[i + 1]);
        dp_all[v] = apply_vertex(head[n], v);
        int k = 1;
        for (auto &[c, cost] : g[v]) {
            if (c == p) continue;
            dfs_all(c, v,
                    apply_edge(apply_vertex(M::op(head[k], tail[k + 1]), v), c,
                               v, cost));
            k++;
        }
    }
};
