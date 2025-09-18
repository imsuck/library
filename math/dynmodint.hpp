#pragma once

// clang-format off
template<int id = 0> struct dynmodint {
    using mint = dynmodint;
    static constexpr bool is_simple = true;

    static void set_mod(uint32_t m) {
        assert(m >= 1 && "Modulus must be in the range [1;2^31)");
        mint::m = m;
        for (k = 0; 1 << k / 2 < m; k += 2);
        r = (1ULL << k) / m;
    }
    static constexpr uint32_t mod() noexcept { return m; }
    constexpr dynmodint() noexcept = default;
    constexpr dynmodint(int64_t v) noexcept : _v(uint32_t((v %= m) < 0 ? v + m : v)) {}
    constexpr static mint raw(uint32_t v) noexcept { mint x; return x._v = v, x; }
    template<class T> constexpr explicit operator T() const noexcept { return _v; }

    constexpr mint &operator++() noexcept { return _v = ++_v == mod() ? 0 : _v, *this; }
    constexpr mint &operator--() noexcept { --(_v ? _v : _v = mod()); return *this; }
    constexpr mint operator++(int) noexcept { return exchange(*this, ++mint(*this)); }
    constexpr mint operator--(int) noexcept { return exchange(*this, --mint(*this)); }

    constexpr mint &operator+=(mint rhs) noexcept {
        return _v = int(_v += rhs._v - mod()) < 0 ? _v + mod() : _v, *this;
    }
    constexpr mint &operator-=(mint rhs) noexcept {
        return _v = int(_v -= rhs._v) < 0 ? _v + mod() : _v, *this;
    }
    constexpr mint &operator*=(mint rhs) noexcept {
        return _v = reduce(1ULL * _v * rhs._v), *this;
    }
    constexpr mint &operator/=(mint rhs) noexcept {
        return *this = *this * rhs.inv();
    }

    constexpr friend mint operator+(mint l, mint r) noexcept { return l += r; }
    constexpr friend mint operator-(mint l, mint r) noexcept { return l -= r; }
    constexpr friend mint operator*(mint l, mint r) noexcept { return l *= r; }
    constexpr friend mint operator/(mint l, mint r) noexcept { return l /= r; }

    constexpr mint operator+() const noexcept { return *this; }
    constexpr mint operator-() const noexcept { return raw(_v ? mod() - _v : 0); }

    constexpr friend bool operator==(const mint &l, const mint &r) noexcept { return l._v == r._v; }
    constexpr friend bool operator!=(const mint &l, const mint &r) noexcept { return l._v != r._v; }
    constexpr friend bool operator<(const mint &l, const mint &r) noexcept { return l._v < r._v; }

    constexpr mint pow(uint64_t n) const noexcept {
        mint b = *this, res = 1;
        while (n) n & 1 ? res *= b : 0, b *= b, n >>= 1;
        return res;
    }

    constexpr mint inv() const noexcept {
        int a = _v, b = mod(), x = 1, y = 0;
        while (b) {
            int d = a / b;
            x = exchange(y, x - d * y);
            a = exchange(b, a - d * b);
        }
        assert(a == 1);
        return x;
    }

    friend istream &operator>>(istream &is, mint &x) {
        int64_t v{};
        return is >> v, x = v, is;
    }
    friend ostream &operator<<(ostream &os, const mint &x) { return os << x._v; }

  private:
    static inline uint32_t m, k;
    static inline uint64_t r;
    static uint32_t reduce(uint64_t x) {
        x -= (__uint128_t)x * r / (1ULL << k) * m;
        return uint32_t(x < m ? x : x - m);
    }
    uint32_t _v = 0;
};
// clang-format on
