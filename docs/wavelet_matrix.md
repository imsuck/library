---
title: Wavelet Matrix
documentation_of: //ds/wavelet_matrix.hpp
---

## Description
Wavelet matrix is a data structure that supports various queries on sequences
in $\mathcal O(\log U)$ time (bit-count of the universe set). It uses
$\mathcal O(n \log \sigma)$ space. The wavelet matrix is built by recursively
partitioning the array based on bit values.

## Operations
- `WaveletMatrix<T, bit_num>(const vector<T> &a)`
  + Construct wavelet matrix from array `a`
  + Time complexity: $\mathcal O(n \log \sigma)$
- `WaveletMatrix<T, bit_num>(int n, Gen gen)`
  + Construct wavelet matrix using `gen(i)` for each element
  + Time complexity: $\mathcal O(n \log \sigma)$
- `T operator[](int i)`
  + Returns the value at index `i`
  + Time complexity: $\mathcal O(\log \sigma)$
- `T rank(T val, int i)`
  + Returns the number of occurrences of `val` in `[0, i)`
  + Time complexity: $\mathcal O(\log \sigma)$
- `T rank(T val, int l, int r)`
  + Returns the number of occurrences of `val` in `[l, r)`
  + Time complexity: $\mathcal O(\log \sigma)$
- `T kth_smallest(int l, int r, int k)`
  + Returns the $k$-th smallest value in `[l, r)` (0-indexed)
  + Time complexity: $\mathcal O(\log \sigma)$
- `int freq(int l, int r, T upper)`
  + Returns the number of values less than `upper` in `[l, r)`
  + Time complexity: $\mathcal O(\log \sigma)$
- `int freq(int l, int r, T lower, T upper)`
  + Returns the number of values in `[lower, upper)` in `[l, r)`
  + Time complexity: $\mathcal O(\log \sigma)$
