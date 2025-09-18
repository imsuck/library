#pragma once

template<class M> struct DisjointSparseTable {
    using T = typename M::T;
    DisjointSparseTable(const vector<T> &v) : n((int)v.size()) {
        t.push_back(v);
        for (int p = 1; 1 << p < n; p++) {
            t.emplace_back(n);
            for (int mid = 1 << p; mid < n; mid += 1 << (p + 1)) {
                t[p][mid - 1] = v[mid - 1];
                for (int j = mid - 2; j >= mid - (1 << p); j--)
                    t[p][j] = M::op(v[j], t[p][j + 1]);
                t[p][mid] = v[mid];
                for (int j = mid + 1; j < min(mid + (1 << p), n); j++)
                    t[p][j] = M::op(t[p][j - 1], v[j]);
            }
        }
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::id();
        r--;
        if (l == r) return t[0][l];
        int p = __builtin_clz(1) - __builtin_clz(l ^ r);
        return M::op(t[p][l], t[p][r]);
    }

  private:
    int n;
    vector<vector<T>> t;
};
