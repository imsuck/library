---
title: Top Tree
documentation_of: //tree/top_tree.hpp
---

## Description
Top Tree is a data structure for maintaining dynamic trees and supporting
path and subtree queries. It uses a tree decomposition approach similar to
Link Cut Tree but with different internal structure. Requires a `TreeDP`
structure defining the tree operations.

Reference: [ei1333's
implementation](https://ei1333.github.io/library/structure/dynamic-tree/top-tree.hpp)

## Operations
- `TopTree<TreeDP>(int n = 0)`
  + Constructs top tree with `n` nodes
  + Time complexity: $\mathcal O(n)$
- `TopTree<TreeDP>(const vector<Info> &v)`
  + Constructs top tree with initial node information
  + Time complexity: $\mathcal O(n)$
- `auto operator[](int i)`
  + Returns pointer to node `i`
  + Time complexity: $\mathcal O(1)$
- `int id(ptr t)`
  + Returns the ID of node `t`
  + Time complexity: $\mathcal O(1)$

Note: Operations `expose`, `evert`, `link`, `cut`, and `lca` have static
pointer variants that take `ptr` (pointer) arguments instead of `int`
(vertex ID) arguments.

- `void splay(int v)`
  + Splays node `v` to root
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void expose(int v)`
  + Exposes path from `v` to root
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void evert(int v)`
  + Makes `v` the root of its tree
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void link(int v, int p)`
  + Links node `v` as a child of `p`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void cut(int v)` or `void cut(int v, int r)`
  + Cuts edge from `v` to its parent, or cuts edge between `v` and `r`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void set(int v, const Info &x)`
  + Sets information at node `v` to `x`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `template<class F> void apply(int v, F &&f)`
  + Applies function `f` to information at node `v`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `int lca(int u, int v)`
  + Returns LCA of `u` and `v`, or `-1` if not connected
  + Time complexity: $\mathcal O(\log n)$ amortized
- `Path fold(int v)`
  + Returns folded value of entire tree with `v` as root
  + Time complexity: $\mathcal O(\log n)$ amortized
- `Path fold_path(int v)` or `Path fold_path(int u, int v)`
  + Returns folded value of path from root to `v`, or from `u` to `v`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `Path fold_subtree(int v)`
  + Returns folded value of subtree rooted at `v`
  + Time complexity: $\mathcal O(\log n)$ amortized

