#pragma once

template<class M> struct DequeAggregation {
    using T = typename M::T;

    T front() const { return f.size() ? getf() : b.front()[0]; }
    T back() const { return b.size() ? getb() : f.back()[0]; }
    void push_front(const T &x) { f.push_back({x, M::op(x, getf<1>())}); }
    void push_back(const T &x) { b.push_back({x, M::op(getb<1>(), x)}); }
    void pop_front() {
        assert(size());
        if (f.empty()) rebalance();
        f.pop_back();
    }
    void pop_back() {
        assert(size());
        if (b.empty()) rebalance();
        b.pop_back();
    }

    T query() const { return M::op(getf<1>(), getb<1>()); }

    int size() const { return int(f.size() + b.size()); }
    bool empty() const { return size() == 0; }

    vector<array<T, 2>> f, b;
  private:
    template<int d = 0> T getf() const {
        return f.size() ? f.back()[d] : M::id();
    }
    template<int d = 0> T getb() const {
        return b.size() ? b.back()[d] : M::id();
    }
    void rebalance() {
        int n = size(), i = 0;
        bool ef = f.empty();
        vector<T> xs(n);
        for (; f.size(); f.pop_back()) xs[i++] = getf();
        for (; b.size(); b.pop_back()) xs[i++] = getb();
        if (!ef) reverse(begin(xs), end(xs));
        for (i = n - 1; i >= 0; i--) push_front(xs[i]);
        for (i = n; i < n; i++) push_back(xs[i]);
    }
};
