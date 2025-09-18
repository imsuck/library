#pragma once

// clang-format off
template<class T = int> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    Compressor(int n = 0) { val.reserve(n); }

    template<class... Ts> void push(Ts &...x) { (_push(x), ...); }
    int build() {
        sort(begin(val), end(val));
        og.reserve(val.size());
        T id = -1;
        for (auto x : val) {
            if (og.empty() || og.back() != x) id++, og.push_back(x);
            x.get() = id;
        }
        og.shrink_to_fit();
        return size();
    }
    int size() const { return (int)og.size(); }
    T operator[](int i) const { return og[i]; }
    int operator()(T x) const { return int(lower_bound(begin(og), end(og), x) - begin(og)); }
    bool find(T x) const { return binary_search(begin(og), end(og), x); }

  private:
    void _push(T &x) { val.push_back(x); }
    void _push(pair<T, T> &p) { push(p.first, p.second); }
    template<class V> void _push(V &a) { for (auto &x : a) _push(x); }
};
// clang-format on
