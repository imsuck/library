#pragma once

// https://usaco.guide/plat/DC-SRQ
// Not really optimized I just wrote this on a whim
template<class T, class Q, class Op> struct RangeQuery {
    RangeQuery(const vector<T> &v, const vector<Q> &_q, Op _op, T e) :
        ans((int)_q.size()), n((int)v.size()), d(v), lef(n, e), rig(n, e),
        idx((int)_q.size()), q(_q), op(_op) {
        iota(begin(idx), end(idx), 0);
    }
    void solve() { _solve(0, n - 1, idx); }

    vector<T> ans;

  private:
    int n;
    vector<T> d, lef, rig;
    vector<int> idx;
    vector<Q> q;
    Op op;
    void _solve(int l, int r, vector<int> &qry) {
        if (qry.empty()) return;
        if (l == r) {
            for (int &i : qry) ans[i] = d[l];
            return;
        }
        int m = (l + r) / 2;
        lef[m] = d[m];
        for (int i = m - 1; i >= l; i--) lef[i] = op(d[i], lef[i + 1]);
        rig[m + 1] = d[m + 1];
        for (int i = m + 2; i < r + 1; i++) rig[i] = op(rig[i - 1], d[i]);
        vector<int> le, ri;
        for (int i : qry) {
            if (q[i].l <= m && m < q[i].r) {
                ans[i] = op(lef[q[i].l], rig[q[i].r]);
                continue;
            }
            (q[i].l <= m ? le : ri).push_back(i);
        }
        _solve(l, m, le);
        _solve(m + 1, r, ri);
    }
};
template<class T, class Q, class Op>
auto make_rq(const vector<T> &v, const vector<Q> &q, Op op, T e) {
    return RangeQuery<T, Q, Op>{v, q, op, e};
}
