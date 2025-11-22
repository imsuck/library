---
title: Compressor
documentation_of: //other/compressor.hpp
---

## Description
Compressor maps values to consecutive integers starting from 0. Useful for
coordinate compression when working with large value ranges. Supports
compressing individual values, pairs, and containers.

## Operations
- `Compressor<T>(int n = 0)`
  + Constructs compressor with reserved capacity `n`
  + Time complexity: $\mathcal O(1)$
- `void push(Ts &...x)`
  + Adds values to be compressed (can take multiple arguments, pairs, or
    containers)
  + Time complexity: $\mathcal O(1)$ per value
- `int build()`
  + Builds the compression mapping and assigns compressed values
  + Must be called after all `push` operations and before using `operator[]`
    or `operator()`
  + Returns the number of distinct values
  + Time complexity: $\mathcal O(n \log n)$ where $n$ is the number of
    values
- `int size()`
  + Returns the number of distinct values
  + Time complexity: $\mathcal O(1)$
- `T operator[](int i)`
  + Returns the original value corresponding to compressed index `i`
  + Time complexity: $\mathcal O(1)$
- `int operator()(T x)`
  + Returns the compressed index of value `x`, or the insertion point if not
    found
  + Time complexity: $\mathcal O(\log n)$
- `bool find(T x)`
  + Returns whether value `x` was compressed
  + Time complexity: $\mathcal O(\log n)$
