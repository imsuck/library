#pragma once

struct RollingHash {
    using u64 = uint64_t;
    static u64 gen_base() noexcept {
        mt19937_64 rng((u64)make_unique<char>().get());
        uniform_int_distribution<u64> dist(1024, mod - 1);
        return dist(rng);
    }

    RollingHash(const string &s, u64 _base) noexcept :
        RollingHash(vector<char>(begin(s), end(s)), _base) {}
    template<class T>
    RollingHash(const vector<T> &v, u64 _base) noexcept :
        base(_base), hashes(v.size() + 1), power(v.size() + 1) {
        power[0] = 1;
        for (int i = 0; i < v.size(); i++) {
            power[i + 1] = mul(power[i], base);
            hashes[i + 1] = add(mul(hashes[i], base), v[i]);
        }
    }

    u64 query(int l, int r) const noexcept {
        return add(hashes[r], mod - mul(hashes[l], power[r - l]));
    }
    u64 concat(u64 l, u64 r, u64 lenr) const noexcept {
        return add(mul(l, power[lenr]), r);
    }
    void push_back(char c) noexcept {
        power.push_back(mul(power.back(), base));
        hashes.push_back(add(mul(hashes.back(), base), c));
    }

  private:
    const u64 base;
    vector<u64> hashes, power;

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
