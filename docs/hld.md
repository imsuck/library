---
title: Heavy-light Decomposition
documentation_of: //tree/hld.hpp
---

## Description
Decomposition of a tree into heavy/light paths which allows for efficient path
queries.

## Operations
- `HLD(G &g, int root = 0)`
  + Decompose tree into heavy/light paths
  + Time complexity: $\mathcal O(n)$
- `int lca(int u, int v)`
  + Returns the lowest common ancestor of `u` and `v`
  + Time complexity: $\mathcal O(\log n)$
- `int dist(int u, int v)`
  + Returns the length of the path from `u` to `v`
  + Time complexity: $\mathcal O(\log n)$
- `vector<pair<int, int>> path(int v, int p, bool es = false)`
  + Returns the intervals representing the path from `v` to `p`, `es == true`
    excludes `p` from the interval
  + Time complexity: $\mathcal O(\log n)$
- `pair<int, int> subtree(int v)`
  + Returns the interval representing the subtree of `v`
  + Time complexity: $\mathcal O(1)$

## Reference
- [CP Algorithms](https://cp-algorithms.com/graph/hld.html)
- [tko919](https://tko919.github.io/library/Graph/hld.hpp)
- [Easiest HLD with subtree queries](https://codeforces.com/blog/entry/53170)
