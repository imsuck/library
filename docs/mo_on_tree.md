---
title: Mo's Algorithm on Tree
documentation_of: //tree/mo_on_tree.hpp
---

## Description
Mo's Algorithm on Tree processes offline path queries on trees efficiently
by reordering queries to minimize the number of vertex additions/removals.
Uses Euler Tour to convert tree paths to ranges.

## Operations
- `MoOnTree<LG>()`
  + Constructs empty Mo on Tree instance
  + Time complexity: $\mathcal O(1)$
- `template<class G> MoOnTree<LG>(G &g, int q, int root = 0)`
  + Constructs Mo on Tree instance for tree `g` with `q` queries and root
    `root`
  + `LG` is the logarithm of the maximum tree depth
  + Time complexity: $\mathcal O(n \log n)$
- `void add_query(int u, int v)`
  + Adds a path query from `u` to `v`
  + Time complexity: $\mathcal O(1)$
- `template<class Eval, class Add, class Del> void run(Eval eval, Add add,
  Del del)`
  + Processes all queries
  + `eval(i)` is called when query `i` should be evaluated
  + `add(v)` / `del(v)` are called when adding/removing vertex `v`
  + Time complexity: $\mathcal O(n \sqrt{q})$ where $q$ is the number of
    queries
