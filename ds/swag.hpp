#pragma once

template<class M> struct SWAG {
    using T = typename M::T;

    T front() const { return f.size() ? getf() : b.front()[0]; }
    T back() const { return b.size() ? getb() : f.back()[0]; }
    void push(const T &x) { b.push_back({x, M::op(getb<1>(), x)}); }
    void pop() {
        assert(size());
        if (f.empty()) {
            int n = size(), i = 0;
            vector<T> xs(n);
            for (; b.size(); b.pop_back()) xs[i++] = b.back()[0];
            for (i = 0; i < n; i++)
                f.push_back({xs[i], M::op(xs[i], getf<1>())});
        }
        f.pop_back();
    }

    T query() const { return M::op(getf<1>(), getb<1>()); }

    int size() const { return int(f.size() + b.size()); }
    bool empty() const { return size() == 0; }

    vector<array<T, 2>> f, b;
    template<int d = 0> T getf() const {
        return f.size() ? f.back()[d] : M::id();
    }
    template<int d = 0> T getb() const {
        return b.size() ? b.back()[d] : M::id();
    }
};
