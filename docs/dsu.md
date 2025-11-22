---
title: Disjoint Set Union
documentation_of: //graph/dsu.hpp
---

## Description
Disjoint Set Union (DSU) with union by size and path compression. Supports
efficient union and find operations in nearly constant time per operation.

## Operations
- `DSU(int n)`
  + Constructs DSU with `n` elements
  + Time complexity: $\mathcal O(n)$
- `void reset(int n)`
  + Resets the DSU to have `n` elements (all in separate sets)
  + Time complexity: $\mathcal O(n)$
- `int find(int x)`
  + Returns the representative of the set containing `x`
  + Time complexity: $\mathcal O(\alpha(n))$ amortized
- `bool same(int x, int y)`
  + Returns whether `x` and `y` are in the same set
  + Time complexity: $\mathcal O(\alpha(n))$ amortized
- `int size(int x)`
  + Returns the size of the set containing `x`
  + Time complexity: $\mathcal O(\alpha(n))$ amortized
- `bool merge(int x, int y)`
  + Merges the sets containing `x` and `y`. Returns `true` if they were in
    different sets
  + Time complexity: $\mathcal O(\alpha(n))$ amortized
- `bool merge(int x, int y, F &&f)`
  + Merges the sets containing `x` and `y` and calls `f(rep(x), rep(y))` where
    `rep(x)` is the new root
  + Returns `true` if they were in different sets
  + Time complexity: $\mathcal O(\alpha(n))$ amortized
