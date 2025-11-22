---
title: Rerooting
documentation_of: //tree/rerooting.hpp
---

## Description
Rerooting computes a value for each vertex in a tree when the tree is rooted
at that vertex in linear time. The value is computed using a monoid that aggregates
information from subtrees.

## Operations
- `Rerooting<M>(int n)`
  + Constructs rerooting instance for a tree with `n` vertices
  + Time complexity: $\mathcal O(1)$
- `void add_edge(int u, int v, const Cost &c)`
  + Adds an undirected edge between `u` and `v` with cost `c`
  + Time complexity: $\mathcal O(1)$
- `vector<T> run(F1 &&f1, F2 &&f2)`
  + Computes the value for each vertex when rooted at that vertex
  + `f1(dp, u, v, cost)` is called to combine edge information: takes
    subtree DP value `dp` from child `v` to parent `u` with edge cost `cost`
  + `f2(dp, v)` is called to apply vertex information: takes aggregated DP
    value `dp` for vertex `v`
  + Returns a vector where `result[v]` is the value when tree is rooted at
    `v`
  + Time complexity: $\mathcal O(n)$
