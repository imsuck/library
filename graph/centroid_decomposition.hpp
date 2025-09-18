#pragma once

template<class G>
tuple<vector<int>, vector<int>, vector<int>> centroid_decomp(const G &g) {
    const int N = (int)g.size();
    vector<int> sz(N), lvl(N, -1), sz_comp(N), par(N);

    auto dfs_sz = [&](auto &dfs, int v, int p) -> int {
        sz[v] = 1;
        for (int c : g[v])
            if (c != p && lvl[c] == -1) sz[v] += dfs(dfs, c, v);
        return sz[v];
    };
    auto dfs_cent = [&](auto &dfs, int v, int p, int n) -> int {
        for (int c : g[v])
            if (c != p && lvl[c] == -1 && sz[c] > n / 2)
                return dfs(dfs, c, v, n);
        return v;
    };
    auto decomp = [&](auto &dfs, int v, int l, int p) -> void {
        int n = dfs_sz(dfs_sz, v, -1);
        int s = dfs_cent(dfs_cent, v, -1, n);
        lvl[s] = l, sz_comp[s] = n, par[s] = p;
        for (int c : g[s])
            if (lvl[c] == -1) dfs(dfs, c, l + 1, s);
    };

    decomp(decomp, 0, 0, -1);
    return {move(lvl), move(sz_comp), move(par)};
}
