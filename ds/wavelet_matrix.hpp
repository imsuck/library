#pragma once

using u32 = uint32_t;
using u64 = uint64_t;

// clang-format off
struct BitVec {
    BitVec() = default;
    explicit BitVec(int n, const vector<bool> &a) :
        BitVec(n, [&](int i) { return a[i]; }) {}
    template<class Gen> BitVec(int n, Gen gen) : v(n / wordsize + 1) {
        for (int i = 0; i < n; i++)
            v[i / wordsize].bit |= size_t(gen(i)) << i % wordsize;
        for (int i = 1; i < v.size(); i++)
            v[i].sum = v[i - 1].sum + popcnt64(v[i - 1].bit);
    }
    bool operator[](int i) const {
        return v[i / wordsize].bit >> i % wordsize & 1;
    }
    int rank(bool val, int i) const {
        int x = v[i / wordsize].sum +
                popcnt64(v[i / wordsize].bit & ~(~size_t(0) << i % wordsize));
        return val ? x : i - x;
    }
    int rank(bool val, int l, int r) const {
        return rank(val, r) - rank(val, l);
    }

  private:
    static constexpr int wordsize = numeric_limits<size_t>::digits;
    struct node { size_t bit = 0, sum = 0; };
    vector<node> v;
    static inline constexpr int popcnt64(size_t x) {
#ifdef __GNUC__
        return __builtin_popcountll(x);
#endif
        x -= x >> 1 & 0x5555555555555555;
        x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
        x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
        return x * 0x0101010101010101 >> 56;
    }
};

// suisen-cp's cp-library-cpp
template<class T, int bit_num = numeric_limits<T>::digits>
struct WaveletMatrix {
    WaveletMatrix() = default;
    explicit WaveletMatrix(const vector<T> &a) :
        WaveletMatrix(a.size(), [&](int i) { return a[i]; }) {}
    template<class Gen> WaveletMatrix(int _n, Gen gen) : n(_n) {
        vector<T> a(n), l(n), r(n);
        for (int i = 0; i < n; i++) a[i] = gen(i);
        for (int lg = bit_num - 1; lg >= 0; lg--) {
            bv[lg] = BitVec(n, [&](int i) { return a[i] >> lg & 1; });
            int li = 0, ri = 0;
            for (int i = 0; i < n; i++)
                (a[i] >> lg & 1 ? r[ri++] : l[li++]) = a[i];
            a.swap(l);
            copy(begin(r), begin(r) + ri, begin(a) + li);
            mid[lg] = li;
        }
    }
    T operator[](int i) const {
        T res = 0;
        for (int lg = bit_num - 1; lg >= 0; lg--) {
            bool b = bv[lg][i];
            res |= T(b) << lg;
            i = b * mid[lg] + bv[lg].rank(b, i);
        }
        return res;
    }
    T rank(T val, int i) const { return rank(val, 0, i); }
    T rank(T val, int l, int r) const {
        for (int lg = bit_num - 1; lg >= 0; lg--)
            succ(l, r, val >> lg & 1, lg);
        return r - l;
    }
    T kth_smallest(int l, int r, int k) const {
        T res = 0;
        for (int lg = bit_num - 1; lg >= 0; lg--) {
            int cnt = bv[lg].rank(0, l, r), bit = k >= cnt;
            succ(l, r, bit, lg);
            res |= T(bit) << lg;
            k -= bit * cnt;
        }
        return res;
    }
    int freq(int l, int r, T upper) const {
        int res = 0;
        for (int log = bit_num - 1; log >= 0; --log) {
            bool u = upper >> log & 1;
            if (u) res += bv[log].rank(0, l, r);
            succ(l, r, u, log);
        }
        return res;
    }
    int freq(int l, int r, T lower, T upper) const {
        return freq(l, r, upper) - freq(l, r, lower);
    }

  private:
    int n = 0;
    array<BitVec, bit_num> bv;
    array<int, bit_num> mid;
    void succ(int &l, int &r, bool b, int lg) const {
        l = b * mid[lg] + bv[lg].rank(b, l);
        r = b * mid[lg] + bv[lg].rank(b, r);
    }
};
// clang-format on
