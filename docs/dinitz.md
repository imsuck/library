---
title: Dinitz's Algorithm
documentation_of: //graph/dinitz.hpp
---

## Description
Dinitz's algorithm computes the maximum flow in a flow network using blocking
flows. This implementation uses bit-scaling optimization with $K$ levels
(default 31) for better performance. Time complexity is $\mathcal O(V^2 E)$ in
the worst case, but often performs better in practice.

## Operations
- `Dinitz<T, K>(int n)`
  + Construct flow network with `n` vertices
  + Time complexity: $\mathcal O(1)$
- `void add_edge(int u, int v, T cap, T rcap = 0)`
  + Adds a directed edge from `u` to `v` with capacity `cap` and reverse
    capacity `rcap`
  + Time complexity: $\mathcal O(1)$
- `auto &operator[](int i)`
  + Returns the adjacency list of vertex `i`
  + Time complexity: $\mathcal O(1)$
- `T max_flow(int s, int t)`
  + Computes the maximum flow from source `s` to sink `t`
  + Time complexity: $\mathcal O(V^2 E)$
- `set<int> min_cut(int s)`
  + Returns the set of vertices reachable from `s` in the residual graph
    after computing max flow
  + This represents one side of the minimum cut
  + Time complexity: $\mathcal O(V + E)$
