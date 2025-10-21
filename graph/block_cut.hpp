#pragma once

#include "other/y_combinator.hpp"

// https://x.com/noshi91/status/1529858538650374144
// https://maspypy.github.io/library/graph/block_cut.hpp
// [0, n): original vertices, [n, n_block): BCC representative
// if v in C then there is an edge (v, id(C))
// cut points are vertices v in [0, n) with deg(v) >= 2
template<class G> auto block_cut(const G &g) {
    const int n = (int)g.size();

    vector<int> in(n), low(n), st;
    vector<bool> vis(n);
    vector<basic_string<int>> bct(2 * n);
    st.reserve(n);
    auto add_edge = [&](int u, int v) { bct[u] += v, bct[v] += u; };

    int comp = n, time = 0;
    auto dfs = y_comb([&](auto &self, int v, int p) -> void {
        st.push_back(v), vis[v] = true;
        in[v] = low[v] = time++;
        int cnt = 0;
        for (int c : g[v]) {
            if (c == p) continue;
            if (!vis[c]) {
                cnt++;
                int s = (int)st.size();
                self(c, v);
                low[v] = min(low[v], low[c]);
                if ((p == -1 && cnt > 1) || (p != -1 && low[c] >= in[v])) {
                    add_edge(comp, v);
                    for (; st.size() > s; st.pop_back())
                        add_edge(comp, st.back());
                    comp++;
                }
            } else {
                low[v] = min(low[v], in[c]);
            }
        }
    });

    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        dfs(i, -1);
        for (int v : st) add_edge(comp, v);
        comp++, st.clear();
    }
    bct.resize(comp), bct.shrink_to_fit();
    return bct;
}
