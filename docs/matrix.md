---
title: Matrix
documentation_of: //math/matrix.hpp
---

## Description
Matrix provides fixed-size matrix operations including multiplication,
exponentiation, and vector multiplication. Supports both modular and
non-modular arithmetic. Available in `without_mod` and `with_mod`
namespaces.

## Operations
- `Matrix<T, N>()`
  + Constructs zero matrix
  + Time complexity: $\mathcal O(1)$
- `Matrix<T, N>(const vector<vector<T>> &v)`
  + Constructs matrix from 2D vector
  + Time complexity: $\mathcal O(N^2)$
- `static Matrix id()`
  + Returns identity matrix
  + Time complexity: $\mathcal O(N^2)$
- `array<T, N> &operator[](int i)`
  + Returns reference to row `i`
  + Time complexity: $\mathcal O(1)$
- `friend Matrix operator*(const Matrix &l, const Matrix &r)`
  + Matrix multiplication
  + Time complexity: $\mathcal O(N^3)$
- `Matrix operator^(int64_t n)`
  + Matrix exponentiation
  + Time complexity: $\mathcal O(N^3 \log n)$
- `vector<T> operator*(const vector<T> &x)`
  + Matrix-vector multiplication
  + Time complexity: $\mathcal O(N^2)$
