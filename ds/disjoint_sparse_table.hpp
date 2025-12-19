#pragma once

template<class M> struct DisjointSparseTable {
    using T = typename M::T;
    DisjointSparseTable(const vector<T> &v) :
        DisjointSparseTable((int)v.size(), [&](int i) -> T { return v[i]; }) {}
    template<class G> DisjointSparseTable(int _n, G &&gen) : n(_n) {
        t.emplace_back(n);
        for (int i = 0; i < n; i++) t[0][i] = gen(i);
        for (int p = 1; 1 << p < n; p++) {
            t.emplace_back(n);
            for (int mid = 1 << p; mid < n; mid += 1 << (p + 1)) {
                t[p][mid - 1] = gen(mid - 1);
                for (int j = mid - 2; j >= mid - (1 << p); j--)
                    t[p][j] = M::op(gen(j), t[p][j + 1]);
                t[p][mid] = gen(mid);
                for (int j = mid + 1; j < min(mid + (1 << p), n); j++)
                    t[p][j] = M::op(t[p][j - 1], gen(j));
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
