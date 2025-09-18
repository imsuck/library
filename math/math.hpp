#pragma once

// clang-format off
namespace utils {
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    u64 lo(u64 x) { return u32(x); }
    u64 hi(u64 x) { return x >> 32; }
    // Gets the high bits of 64-bit int multiplication
    u64 mulhi(u64 a, u64 b) {
    #ifdef __SIZEOF_INT128__
        return ((__uint128_t)a * b) >> 64;
    #endif
        u64 h = hi(a) * hi(b);
        u64 m1 = lo(a) * hi(b), m2 = hi(a) * lo(b);
        u64 l = lo(a) * lo(b);

        u64 c = hi(lo(m1) + lo(m2) + hi(l));

        return h + hi(m1) + hi(m2) + c;
    }
    // m in [0; 2^63)
    u64 mulmod(u64 a, u64 b, u64 m) {
    #ifdef __SIZEOF_INT128__
        return u64((__uint128_t)a * b % m);
    #endif
        u64 res = mulhi(a, b) % m;
        if (m < 1 << 32) res = res*((1<<63)%m)%m, res<<=1, res-=(res>=m)*m;
        else for (u32 i = 0; i < 64; i++) res <<= 1, res -= (res >= m) * m;
        res += a * b % m;
        return res - (res >= m) * m;
    }
} // namespace utils
// clang-format on

using utils::mulhi;
using utils::mulmod;
