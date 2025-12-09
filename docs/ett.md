---
title: Euler Tour Tree
documentation_of: //tree/ett.hpp
---

## Description
Euler Tour Tree (ETT) maintains a dynamic tree and supports queries on
subtrees. It uses a treap to represent the Euler tour of the tree. Supports
link-cut operations and subtree queries in $\mathcal O(\log n)$ time per
operation.

## Operations
- `ETT<M>(int n)`
  + Constructs ETT for a tree with `n` vertices
  + Time complexity: $\mathcal O(n)$
- `T get(int v)`
  + Returns the value at vertex `v`
  + Time complexity: $\mathcal O(\log n)$
- `void set(int v, const T &x)`
  + Sets the value at vertex `v` to `x`
  + Time complexity: $\mathcal O(\log n)$
- `bool connected(int u, int v)`
  + Returns whether vertices `u` and `v` are in the same connected component
  + Time complexity: $\mathcal O(\log n)$
- `void link(int u, int v)`
  + Adds an edge between `u` and `v` (does nothing if already connected)
  + Time complexity: $\mathcal O(\log n)$
- `void cut(int u, int v)`
  + Removes the edge between `u` and `v` (does nothing if not connected)
  + Time complexity: $\mathcal O(\log n)$
- `int subtree_size(int v, int p = -1)`
  + Returns the size of the subtree of `v` with parent `p` (temporarily cuts
    edge if `p != -1`)
  + Time complexity: $\mathcal O(\log n)$
- `T subtree_prod(int v, int p = -1)`
  + Returns the product of values in the subtree of `v` with parent `p`
    (temporarily cuts edge if `p != -1`)
  + Time complexity: $\mathcal O(\log n)$
