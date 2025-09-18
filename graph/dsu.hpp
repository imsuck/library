#pragma once

struct DSU {
    vector<int> data;
    DSU() : DSU(0) {}
    DSU(int n) : data(n, -1) {}

    void reset(int n) {
        if (data.size() < n) data.resize(n);
        fill_n(begin(data), n, -1);
    }
    int size(int x) { return -data[find(x)]; }
    int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        return merge(x, y, [](auto...) {});
    }
    template<class F> bool merge(int x, int y, F &&f) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += exchange(data[y], x);
        f(x, y);
        return true;
    }
};
