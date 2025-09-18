#pragma once

// clang-format off
template<class G> struct DsuOnTree {
    DsuOnTree(G &_g, int _root = 0) :
        g(_g), n((int)g.size()), root(_root), sz(n, 1), euler(n), in(n),
        out(n) {
        auto dfs = [&](auto &self, int v, int p) -> void {
            euler[time] = v, in[v] = time++;
            if (g[v].size() && g[v][0] == p) swap(g[v][0], g[v].back());
            for (int &c : g[v]) {
                if (c == p) continue;
                self(self, c, v), sz[v] += sz[c];
                if (sz[g[v][0]] < sz[c]) swap(g[v][0], c);
            }
            out[v] = time;
        };
        dfs(dfs, root, -1);
    }

    template<class F1, class F2, class F3>
    void run(F1 &&add, F2 &&del, F3 &&query) {
        auto dfs = [&](auto &self, int v, int p, bool keep) -> void {
            for (int c : g[v]) if (c != p && c != g[v][0]) self(self, c, v, false);
            if (g[v].size() && g[v][0] != p) self(self, g[v][0], v, true);
            for (int c : g[v]) {
                if (c == p || c == g[v][0]) continue;
                for (int i = in[c]; i < out[c]; i++) add(euler[i]);
            }
            add(v), query(v);
            if (!keep) for (int i = in[v]; i < out[v]; i++) del(euler[i]);
        };
        dfs(dfs, root, -1, false);
    }

  private:
    G &g;
    int n, root, time = 0;
    vector<int> sz, euler, in, out;
};
// clang-format on
