#pragma once

template<class G> auto two_cc(const G &g) {
    const int n = (int)g.size();
    int time = 0;
    vector<int> in(n, n), low(n);

    auto dfs = [&](auto &dfs, int v, int p) -> void {
        in[v] = low[v] = time++;
        bool skip = true;
        for (int c : g[v]) {
            if (c == p && exchange(skip, 0)) continue;
            if (in[c] < n) {
                low[v] = min(low[v], in[c]);
                continue;
            }
            dfs(dfs, c, v);
            low[v] = min(low[v], low[c]);
        }
    };
    for (int i = 0; i < n; i++)
        if (in[i] == n) dfs(dfs, i, -1);

    auto is_bridge = [&](int u, int v) {
        if (in[u] > in[v]) swap(u, v);
        return low[v] > in[u];
    };

    int k = 0;
    vector<int> id(n, n);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (id[i] != n) continue;
        assert(q.empty());
        id[i] = k, q.push(i);
        while (q.size()) {
            int v = q.front();
            q.pop();
            for (int u : g[v]) {
                if (id[u] != n || is_bridge(u, v)) continue;
                id[u] = k;
                q.push(u);
            }
        }
        k++;
    }

    return id;
}
template<class G> auto bridge_tree(const G &g) {
    auto id = two_cc(g);
    const int n = (int)g.size(), k = *max_element(begin(id), end(id)) + 1;
    vector<basic_string<int>> ccs(k), tr(k);
    for (int v = 0; v < n; v++) {
        ccs[id[v]] += (v);
        for (int u : g[v])
            if (id[v] != id[u]) tr[id[v]] += u, tr[id[u]] += v;
    }
    for (auto &a : tr) {
        sort(begin(a), end(a));
        a.resize(unique(begin(a), end(a)) - begin(a));
    }
    return tuple(ccs, id, tr);
}
