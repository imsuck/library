#pragma once

// clang-format off
template<class T, int N> struct mdvec {
    const array<int, N> ds;
    vector<T> v;

    mdvec(array<int, N> _ds) : ds(_ds) {
        int size = 1;
        for (int d : ds) size *= d;
        v.resize(size);
    }
    int index(const array<int, N> &ids) const {
        int id = 0, w = 1;
        for (int i = 0; i < N; i++) id += ids[i] * w, w *= ds[i];
        return id;
    }
    T &operator[](const array<int, N> &ids) { return v[index(ids)]; }
    const T &operator[](const array<int, N> &ids) const { return v[index(ids)]; }
};

template<class R, int N, class F> struct Cache {
    mdvec<R, N> cache;
    mdvec<char, N> vis;
    F f;

    template<class T>
    Cache(array<int, N> ds, T &&_f) : cache(ds), vis(ds), f(forward<T>(_f)){};
    template<class... Ts> R operator()(Ts &&...xs) {
        if (vis[{xs...}]) return cache[{xs...}];
        return vis[{xs...}] = 1, cache[{xs...}] = f(*this, xs...);
    }
};
template<class R, int N, class F>
Cache<R, N, decay_t<F>> use_cache(array<int, N> ds, F &&f) { return {ds, forward<F>(f)}; }
// clang-format on
