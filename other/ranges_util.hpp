#pragma once

template<class T> struct rev_t {
    T &x;
    auto begin() const { return x.rbegin(); }
    auto end() const { return x.rend(); }
};
template<class T> struct crev_t {
    const T &x;
    auto begin() const { return x.crbegin(); }
    auto end() const { return x.crend(); }
};
template<class T> auto rev(T &x) { return rev_t<T>{x}; }
template<class T> auto rev(const T &x) { return crev_t<T>{x}; }
template<class T = int> struct range {
    range() {}
    range(T _stop) : stop(_stop) {}
    range(T _start, T _stop, T _step = 1) :
        start(_start), stop(_stop), step(_step) {
        assert(step != 0);
    }

    bool operator!=(range) { return step > 0 ? cur < stop : stop < cur; }
    void operator++() { cur += step; }
    T operator*() { return cur; }

    range begin() { return *this; }
    range end() { return {}; }

    T start = 0, stop, step = 1;
    T cur = start;
};
