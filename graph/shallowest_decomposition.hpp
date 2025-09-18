#pragma once

// clang-format off
template<class G> pair<G, int> shallowest_decomp(const G &g) {
    auto clz = [](uint32_t x) { return x ? __builtin_clz(x) : 32; };
    auto ctz = [](uint32_t x) { return x ? __builtin_ctz(x) : 32; };
    auto bw = [&](uint32_t x) { return clz(0) - clz(x); };
    const int n = (int)g.size();
    G tree(n), st(bw(n));

    auto chain = [&](int labels, int v) {
        while (labels) {
            int label = __lg(labels);
            labels ^= 1 << label;
            int c = st[label].back(); st[label].pop_back();
            tree[v].push_back(c);
            v = c;
        }
    };
    vector<int> forbid(n, -1);
    auto dfs = [&](auto &self, int v, int p = -1) -> void {
        int once = 0, twice = 0;
        for (int c : g[v]) {
            if (c == p) continue;
            self(self, c, v);
            twice |= once & (forbid[c] + 1);
            once |= forbid[c] + 1;
        }
        forbid[v] = once | ((1 << bw(twice)) - 1);
        int label = ctz(forbid[v] + 1);
        st[label].push_back(v);
        for (int i = (int)g[v].size() - 1; i >= 0; i--) {
            int c = g[v][i];
            chain((forbid[c] + 1) & ((1 << label) - 1), v);
        }
    };
    dfs(dfs, 0);
    int mx = __lg(forbid[0] + 1);
    int root = st[mx].back(); st[mx].pop_back();
    chain((forbid[0] + 1) & ((1 << mx) - 1), root);
    return {move(tree), root};
}
// clang-format on
