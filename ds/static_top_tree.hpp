#pragma once

#include "other/y_combinator.hpp"

enum Type : char { Vertex, AddVertex, AddEdge, Compress, Rake };
template<class G> struct STT {
    struct node {
        Type t;
        int p = -1, l, r;

        node() {}
        node(Type tp, int _l, int _r) : t(tp), l(_l), r(_r) {}
    };

    int rt;
    G &g;
    vector<node> vs;

    STT(G &_g, int root = 0) : g(_g) {
        int n = (int)g.size();
        vs.assign(n, {Vertex, -1, -1});
        vs.reserve(4 * n);
        y_comb([&](auto &hld, int v) -> int {
            int s = 1, mx = 0;
            for (auto &c : g[v]) {
                int sc = hld(c);
                s += sc;
                if (sc > mx) mx = sc, swap(g[v][0], c);
            }
            return s;
        })(root);
        rt = compress(root)[0];
        vs.shrink_to_fit();
    }

    int size() const { return (int)vs.size(); }
    auto &operator[](int i) const { return vs[i]; }

    using P = array<int, 2>;
    int add(int k, int l, int r, Type t) {
        if (k == -1) {
            k = (int)vs.size();
            vs.emplace_back(t, l, r);
        } else {
            vs[k] = {t, l, r};
        }
        if (l != -1) vs[l].p = k;
        if (r != -1) vs[r].p = k;
        return k;
    }

    P merge(const vector<P> &a, Type t) {
        if (a.size() == 1) return a[0];
        int s = 0;
        for (auto [v, sz] : a) s += sz;
        vector<P> b, c;
        for (auto x : a) (s > x[1] ? b : c).push_back(x), s -= 2 * x[1];
        auto [l, szl] = merge(b, t);
        auto [r, szr] = merge(c, t);
        return {add(-1, l, r, t), szl + szr};
    }
    P compress(int v) {
        vector<P> ch{add_vertex(v)};
        while (g[v].size()) ch.push_back(add_vertex(v = g[v][0]));
        return merge(ch, Compress);
    }
    P rake(int v) {
        vector<P> ch;
        for (int i = 1; i < g[v].size(); i++) ch.push_back(add_edge(g[v][i]));
        return ch.size() ? merge(ch, Rake) : P{-1, 0};
    }
    P add_edge(int v) {
        auto [u, sz] = compress(v);
        return {add(-1, u, -1, AddEdge), sz};
    }
    P add_vertex(int v) {
        auto [u, sz] = rake(v);
        return {add(v, u, -1, u == -1 ? Vertex : AddVertex), sz + 1};
    }
};
