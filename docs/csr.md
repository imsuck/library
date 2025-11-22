---
title: Compressed Sparse Row
documentation_of: //graph/csr.hpp
---

## Description
Compressed Sparse Row (CSR) is a space-efficient graph representation that
stores edges in a contiguous array with prefix sums for fast vertex access.
Provides iterator support for efficient edge traversal. Uses $\mathcal O(n +
m)$ space where $n$ is the number of vertices and $m$ is the number of edges.

## Operations
- `CSR<E>()`
  + Constructs empty CSR
  + Time complexity: $\mathcal O(1)$
- `CSR<E>(int n, const vector<pair<int, E>> &edges)`
  + Constructs CSR with `n` vertices and edges from the edge list
  + Each edge is a pair `(from, edge_data)`
  + Time complexity: $\mathcal O(n + m)$ where $m$ is the number of edges
- `int size()`
  + Returns the number of vertices
  + Time complexity: $\mathcal O(1)$
- `range operator[](size_t i)` or `const_range operator[](size_t i)`
  + Returns a range of edges from vertex `i` that can be iterated
  + Supports indexing: `g[v][i]` returns the `i`-th edge from vertex `v`
  + Time complexity: $\mathcal O(1)$
- Iterator support
  + Supports range-based for loops: `for (auto &e : g[v])`
  + Time complexity: $\mathcal O(\deg(v))$ to iterate all edges
