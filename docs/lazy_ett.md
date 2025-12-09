---
title: Lazy Euler Tour Tree
documentation_of: //tree/lazy_ett.hpp
---

## Description
Lazy Euler Tour Tree (Lazy ETT) extends ETT with lazy propagation, allowing
range updates on subtrees. It maintains a dynamic tree and supports queries
and updates on subtrees in $\mathcal O(\log n)$ time per operation.

## Operations
- `LazyETT<M>(int n)`
  + Constructs lazy ETT for a tree with `n` vertices
  + Time complexity: $\mathcal O(n)$
- `LazyETT<M>(const vector<T> &val)`
  + Constructs lazy ETT with initial values `val`
  + Time complexity: $\mathcal O(n)$
- `bool same(int u, int v)`
  + Returns whether vertices `u` and `v` are in the same connected component
  + Time complexity: $\mathcal O(\log n)$
- `void link(int u, int v)`
  + Adds an edge between `u` and `v` (panics if they are connected)
  + Time complexity: $\mathcal O(\log n)$
- `void cut(int u, int v)`
  + Removes the edge between `u` and `v` (panics if they are not connected)
  + Time complexity: $\mathcal O(\log n)$
- `void set(int v, const T &x)`
  + Sets the value at vertex `v` to `x`
  + Time complexity: $\mathcal O(\log n)$
- `T subtree_prod(int v, int p)`
  + Returns the product of values in the subtree of `v` with parent `p`
  + Time complexity: $\mathcal O(\log n)$
- `void apply(int v, int p, const F &f)`
  + Applies update `f` to the subtree of `v` with parent `p`
  + Time complexity: $\mathcal O(\log n)$
