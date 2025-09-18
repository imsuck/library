#pragma once

template<class G> auto find_scc(const G &g) {
    int n = (int)g.size();
    vector<int> val(n), z;
    vector<char> added(n);
    vector<basic_string<int>> scc;
    int time = 0;
    auto dfs = [&](auto &self, int v) -> int {
        int low = val[v] = time++;
        z.push_back(v);
        for (auto u : g[v])
            if (!added[u]) low = min(low, val[u] ?: self(self, u));
        if (low == val[v]) {
            scc.emplace_back();
            int x;
            do {
                x = z.back(), z.pop_back();
                added[x] = true;
                scc.back().push_back(x);
            } while (x != v);
        }
        return val[v] = low;
    };
    for (int i = 0; i < n; i++)
        if (!added[i]) dfs(dfs, i);
    reverse(begin(scc), end(scc));
    return scc;
}
template<class G> auto condense(const G &g) {
    auto scc = find_scc(g);
    int n = (int)scc.size();
    vector<int> rep(g.size());
    for (int i = 0; i < n; i++)
        for (auto v : scc[i]) rep[v] = i;
    vector<basic_string<int>> gd(n);
    for (int v = 0; v < g.size(); v++)
        for (auto u : g[v])
            if (rep[v] != rep[u]) gd[rep[v]].push_back(rep[u]);
    for (auto &v : gd) {
        sort(begin(v), end(v));
        v.erase(unique(begin(v), end(v)), end(v));
    }
    return make_tuple(move(scc), move(rep), move(gd));
}
