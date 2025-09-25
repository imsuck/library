#pragma once

#include "hld.hpp"

struct VirtualTree {
    int n;
    HLD &hld;
    vector<basic_string<int>> g;

    VirtualTree(HLD &_hld) : n(_hld.n), hld(_hld), g(n) {}

    template<class V> int build(V vs) {
        auto anc = [&](int p, int v) {
            return hld.in[p] <= hld.in[v] && hld.out[v] <= hld.out[p];
        };
        auto cmp = [&](int u, int v) { return hld.in[u] < hld.in[v]; };
        int k = (int)vs.size();
        sort(begin(vs), end(vs), cmp);
        for (int i = 1; i < k; i++) vs.push_back(hld.lca(vs[i - 1], vs[i]));
        sort(begin(vs), end(vs), cmp);
        k = unique(begin(vs), end(vs)) - begin(vs);
        for (int i = 0; i < k; i++) g[vs[i]].clear();
        stack<int> st;
        st.push(vs[0]);
        for (int i = 1; i < k; i++) {
            while (!anc(st.top(), vs[i])) st.pop();
            g[st.top()] += vs[i];
            st.push(vs[i]);
        }
        return vs[0];
    }
    auto &operator[](int v) { return g[v]; }
};
