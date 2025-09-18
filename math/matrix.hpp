#pragma once

using i32 = int32_t;
using i64 = int64_t;

namespace without_mod {
// clang-format off
template<class T, int N> struct Matrix {
  private:
    template<class _> using vec = vector<_>;

  public:
    array<array<T, N>, N> mat;
    array<T, N> &operator[](int i) { return mat[i]; }
    const array<T, N> &operator[](int i) const { return mat[i]; }
    constexpr Matrix() : mat{} {}
    constexpr Matrix(const vec<vec<T>> &v) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                mat[i][j] = v[i][j];
    }
    static constexpr Matrix id() {
        Matrix res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }

    constexpr friend Matrix operator*(const Matrix &l, const Matrix &r) {
        Matrix res;
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                for (int j = 0; j < N; j++)
                    res[i][j] += l[i][k] * r[k][j];
        return res;
    }
    Matrix operator^(int64_t n) const {
        Matrix res = id(), base = *this;
        while (n) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
    vec<T> operator*(const vec<T> &x) const {
        assert(x.size() == N);
        vec<T> res(x.size());
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                res[i] += mat[i][k] * x[k];
        return res;
    }
};
// clang-format on
} // namespace without_mod

// TODO: Make this work for n*m matrices
namespace with_mod {
// clang-format off
template<class T, int N, int mod = 0> struct Matrix {
  private:
    template<class _> using vec = vector<_>;
    static constexpr T mul(T a, T b) {
        if constexpr (mod == 0) return a * b;
        else a * b % mod;
    }

  public:
    array<array<T, N>, N> mat;
    array<T, N> &operator[](int i) { return mat[i]; }
    const array<T, N> &operator[](int i) const { return mat[i]; }
    constexpr Matrix() : mat{} {}
    constexpr Matrix(const vec<vec<T>> &v) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                mat[i][j] = v[i][j];
    }
    static constexpr Matrix id() {
        Matrix res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }

    constexpr friend Matrix operator*(const Matrix &l, const Matrix &r) {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    res[i][j] += mul(l[i][k], r[k][j]);
                    if (res[i][j] >= mod) res[i][j] -= mod;
                }
            }
        }
        return res;
    }
    Matrix operator^(int64_t n) const {
        Matrix res = id(), base = *this;
        while (n) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
    vec<T> operator*(const vec<T> &x) const {
        assert(x.size() == N);
        vec<T> res(x.size());
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                res[i] += mul(mat[i][k], x[k]);
                if (res[i] >= mod) res[i] -= mod;
            }
        }
        return res;
    }
};
// clang-format on
} // namespace with_mod
