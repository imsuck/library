#pragma once

template<class T, size_t N> struct CircularDeque {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    size_t fr = 0, bk = 0;
    array<T, N> data;

    template<class... Ts> T &emplace_front(Ts &&...xs) {
        fr = (fr + N - 1) % N;
        return data[fr] = T(forward<Ts>(xs)...);
    }
    template<class... Ts> T &emplace_back(Ts &&...xs) {
        size_t tmp = exchange(bk, (bk + 1) % N);
        return data[tmp] = T(forward<Ts>(xs)...);
    }
    T &push_front(T x) { return emplace_front(move(x)); }
    T &push_back(T x) { return emplace_back(move(x)); }
    void pop_front() { fr = (fr + 1) % N; }
    void pop_back() { bk = (bk + N - 1) % N; }
    T &front() { return data[fr]; }
    T &back() { return data[(bk + N - 1) % N]; }
    const T &front() const { return data[fr]; }
    const T &back() const { return data[(bk + N - 1) % N]; }
    T &operator[](size_t i) { return data[(fr + i) % N]; }
    const T &operator[](size_t i) const { return data[(fr + i) % N]; }
    size_t size() const { return (bk - fr + N) % N; }
    bool empty() const { return bk == fr; }
    void clear() { fr = bk = 0, data[0] = T(); }
};

template<class T> struct DynamicCircularDeque {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    size_t fr = 0, bk = 0, cap = 8;
    vector<T> data;

    DynamicCircularDeque() : data(cap) {}

    template<class... Ts> T &emplace_front(Ts &&...xs) {
        if (size() + 1 == cap) realloc(cap + 1);
        fr = (fr + cap - 1) & (cap - 1);
        return data[fr] = T(forward<Ts>(xs)...);
    }
    template<class... Ts> T &emplace_back(Ts &&...xs) {
        if (size() + 1 == cap) realloc(cap + 1);
        size_t tmp = exchange(bk, (bk + 1) & (cap - 1));
        return data[tmp] = T(forward<Ts>(xs)...);
    }
    T &push_front(T x) { return emplace_front(move(x)); }
    T &push_back(T x) { return emplace_back(move(x)); }
    void pop_front() { fr = (fr + 1) & (cap - 1); }
    void pop_back() { bk = (bk + cap - 1) & (cap - 1); }
    T &front() { return data[fr]; }
    T &back() { return data[(bk + cap - 1) & (cap - 1)]; }
    const T &front() const { return data[fr]; }
    const T &back() const { return data[(bk + cap - 1) & (cap - 1)]; }
    T &operator[](size_t i) { return data[(fr + i) & (cap - 1)]; }
    const T &operator[](size_t i) const { return data[(fr + i) & (cap - 1)]; }
    size_t size() const { return (bk - fr + cap) & (cap - 1); }
    bool empty() const { return bk == fr; }
    void clear() { fr = bk = 0, data[0] = T(); }
    void reserve(int n) { realloc(n); }

  private:
    void realloc(size_t n) {
        while (cap < n) cap *= 2;
        vector<T> d(cap);
        size_t sz = size();
        for (size_t i = 0; i < sz; i++) d[i] = move(data[(fr + i) & (cap - 1)]);
        fr = 0, bk = sz, data.swap(d);
    }
};
