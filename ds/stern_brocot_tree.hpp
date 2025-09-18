#pragma once

// clang-format off
template<class Int> struct sbt_node {
    using node = sbt_node;
    using rational = pair<Int, Int>;
    using sbt_arc = bool;
    static constexpr sbt_arc Left = false, Right = true;
    using sbt_path = vector<pair<sbt_arc, Int>>;

    sbt_node() {}
    sbt_node(Int a, Int b) {
        assert(a > 0 && b > 0);
        sbt_arc dir = a < b ? Left : Right;
        if (dir == Left) swap(a, b);
        for (; b; dir = !dir) {
            const Int q = a / b, r = a % b;
            go_down(dir, q - (r == 0));
            a = exchange(b, r);
        }
    }
    sbt_node(const rational &x) : sbt_node(x.first, x.second) {}
    sbt_node(const sbt_path &path) {
        for (const auto &[dir, len] : path) go_down(dir, len);
    }

    operator rational() const { return {_l.first + _r.first, _l.second + _r.second}; }
    rational get() const { return *this; }
    pair<rational, rational> range() const { return {_l, _r}; }
    Int depth() const { return _dep; }
    const sbt_path &path() const { return _path; }

    friend bool operator==(const sbt_node &a, const sbt_node &b) { return a._l == b._l && a._r == b._r; }
    friend bool operator!=(const sbt_node &a, const sbt_node &b) { return !(a == b); }
    friend bool operator<(const sbt_node &a, const sbt_node &b) { return rational(a) < rational(b); }
    friend bool operator>(const sbt_node &a, const sbt_node &b) { return b > a; }
    friend bool operator<=(const sbt_node &a, const sbt_node &b) { return !(a > b); }
    friend bool operator>=(const sbt_node &a, const sbt_node &b) { return !(a < b); }

    static sbt_node lca(const sbt_node &a, const sbt_node &b) {
        const sbt_path &pa = a.path(), &pb = b.path();
        const int k = (int)min(pa.size(), pb.size());
        sbt_node c;
        for (int i = 0; i < k; i++) {
            if (pa[i] == pb[i]) {
                c.go_down(pa[i].first, pa[i].second);
            } else {
                if (pa[i].first == pb[i].first)
                    c.go_down(pa[i].first, min(pa[i].second, pb[i].second));
                break;
            }
        }
        return c;
    }
    static sbt_node dist(const sbt_node &a, const sbt_node &b) {
        return a.depth() + b.depth() - 2 * lca(a, b).depth();
    }
    sbt_node lca(const sbt_node &other) const { return lca(*this, other); }
    sbt_node dist(const sbt_node &other) const { return dist(*this, other); }

    bool go_up(Int k) {
        if (k < 0 || depth() < k) return false;
        while (k) {
            auto &[dir, len] = _path.back();
            const Int u = min(k, len);
            k -= u;
            _dep -= u;
            if (dir == Left) {
                _r.first -= _l.first * u, _r.second -= _l.second * u;
            } else {
                _l.first -= _r.first * u, _l.second -= _r.second * u;
            }
            len -= u;
            if (len == 0) _path.pop_back();
        }
        return true;
    }
    void go_down(sbt_arc dir, Int k) {
        assert(k >= 0);
        if (k == 0) return;
        if (_path.size() && dir == _path.back().first) _path.back().second += k;
        else _path.emplace_back(dir, k);
        _dep += k;
        if (dir == Left) _r.first += _l.first * k, _r.second += _l.second * k;
        else _l.first += _r.first * k, _l.second += _r.second * k;
    }

  private:
    rational _l = {0, 1}, _r = {1, 0};
    Int _dep = 0;
    sbt_path _path;

    static bool less(const rational &a, const rational &b) {
        using LInt = conditional_t<numeric_limits<Int>::digits <= 32, uint64_t,
                                   __uint128_t>;
        return LInt(a.first) * b.second < LInt(b.first) * a.second;
    }
};
// clang-format on
