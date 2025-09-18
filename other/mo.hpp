#pragma once

struct Mo {
    int q;
    const int B;
    vector<int> qi;
    vector<pair<int, int>> qs;

    int l = 0, r = 0;

    Mo(int n, const vector<pair<int, int>> &_qs) :
        q((int)_qs.size()), B(blk_sz(n, q)), qi(q), qs(_qs) {
        iota(begin(qi), end(qi), 0);
        sort(begin(qi), end(qi), [&](int i, int j) {
            auto [li, ri] = qs[i];
            auto [lj, rj] = qs[j];
            int bi = li / B, bj = lj / B;
            if (bi != bj) return bi < bj;
            if (ri != rj) return (bi & 1) != (ri < rj);
            return li < lj;
        });
    }

    template<class Eval, class AL, class DL, class AR, class DR>
    void run(Eval eval, AL add_l, DL del_l, AR add_r, DR del_r) {
        for (int i : qi) {
            auto [ql, qr] = qs[i];
            while (ql < l) add_l(--l);
            while (r < qr) add_r(r++);
            while (l < ql) del_l(l++);
            while (qr < r) del_r(--r);
            eval(i);
        }
    }
    template<class Eval, class Add, class Del>
    void run(Eval eval, Add add, Del del) {
        run(eval, add, del, add, del);
    }

  private:
    static int blk_sz(int n, int q) {
        return max(1, int(n / max<double>(1, sqrt(q * 2.0 / 3.0))));
    }
};
