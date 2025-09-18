#pragma once

template<class T, class D = void> struct _chash;
template<class T> inline void hash_combine(uint64_t &seed, const T &v) {
    seed ^= _chash<T>{}(v) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4);
}
template<class T> struct _chash<T, enable_if_t<is_integral_v<T>>> {
    uint64_t operator()(T x) const {
        // uncomment to use with STL
        static const uint64_t RAND =
            mt19937_64((uint64_t)make_unique<char>().get())();
        x ^= RAND;
        (x ^= x >> 30) *= 0xbf58476d1ce4e5b9;
        (x ^= x >> 27) *= 0x94d049bb133111eb;
        x ^= x >> 31;
        return x;
    }
};
template<class T> struct _chash<T, void_t<decltype(begin(declval<T>()))>> {
    uint64_t operator()(const T &a) const {
        uint64_t h = 0;
        for (auto &x : a) hash_combine(h, x);
        return h;
    }
};
template<class... Ts> struct _chash<tuple<Ts...>> {
    uint64_t operator()(const tuple<Ts...> &a) const {
        uint64_t h = 0;
        apply([&h](auto &&...x) { (hash_combine(h, x), ...); }, a);
        return h;
    }
};
template<class T, class U> struct _chash<pair<T, U>> {
    uint64_t operator()(const pair<T, U> &a) const {
        return _chash<tuple<T, U>>{}(a);
    }
};
struct chash {
    template<class T> uint64_t operator()(const T &x) const {
        return _chash<T>{}(x);
    }
};
