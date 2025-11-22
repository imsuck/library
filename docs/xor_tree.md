---
title: XOR Tree
documentation_of: //tree/xor_tree.hpp
---

## Description
XOR Tree is a space-efficient tree representation using XOR linked lists. It
allows traversing a tree from leaves to root without storing parent pointers
explicitly.

## Operations
- `XorTree(int n)`
  + Constructs XOR tree with `n` vertices
  + Time complexity: $\mathcal O(n)$
- `void add_edge(int u, int v)`
  + Adds an edge between `u` and `v`
  + Time complexity: $\mathcal O(1)$
- `void set_root(int v)`
  + Sets `v` as the root of the tree
  + Time complexity: $\mathcal O(1)$
- `template<class F1, class F2> void run(F1 &&apply_edge, F2 &&apply_vertex)`
  + Traverses the tree from leaves to root
  + `apply_edge(p, v)` is called for each edge `(p, v)` where `v` is a leaf
  + `apply_vertex(v)` is called for each vertex `v` in order from leaves to
    root
  + Time complexity: $\mathcal O(n)$
- `auto dfs_ord()`
  + Returns DFS order and subtree sizes, destroys tree structure
  + Returns a pair `(ord, sz)` where:
    - `ord` is the DFS order array
    - `sz[v]` is the subtree size of vertex `v`
  + Time complexity: $\mathcal O(n)$
