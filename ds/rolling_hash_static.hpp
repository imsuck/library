#pragma once

template<int id = 0> struct RollingHashStatic {
    using u64 = uint64_t;
    static u64 gen_base() noexcept {
        mt19937_64 rng((u64)make_unique<char>().get());
        uniform_int_distribution<u64> dist(1024, mod - 1);
        return dist(rng);
    }

    static inline u64 base = gen_base();

    static u64 concat(u64 l, u64 r, int lenr) noexcept {
        return add(mul(l, pow(lenr)), r);
    }

  private:
    static inline vector<u64> power{1};
    static u64 pow(int i) {
        while (power.size() <= i) power.push_back(mul(power.back(), base));
        return power[i];
    }

    static constexpr u64 mod = (1ull << 61) - 1;
    static constexpr u64 mask30 = (1u << 30) - 1;
    static constexpr u64 mask31 = (1u << 31) - 1;
    static constexpr u64 fast_mod(u64 x) noexcept {
        return add(x >> 61, x & mod);
    }
    static constexpr u64 add(u64 a, u64 b) noexcept {
        return (a += b) < mod ? a : a - mod;
    }
    static constexpr u64 mul(u64 a, u64 b) noexcept {
        u64 ha = a >> 31, la = a & mask31;
        u64 hb = b >> 31, lb = b & mask31;
        u64 m = ha * lb + la * hb;
        u64 hm = m >> 30, lm = m & mask30;
        return fast_mod(ha * hb * 2 + hm + (lm << 31) + la * lb);
    }
};
