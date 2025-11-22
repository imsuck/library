---
title: Adjacency Edge List
documentation_of: //graph/ael.hpp
---

## Description
Adjacency Edge List (AEL) is a space-efficient graph representation using
a linked list structure. Unlike standard adjacency lists, it doesn't support
`g[v][i]` indexing but provides iterators for efficient edge traversal. Uses
$\mathcal O(n + m)$ space where $n$ is the number of vertices and $m$ is the
number of edges.

## Operations
- `AEL<E>()`
  + Constructs empty AEL
  + Time complexity: $\mathcal O(1)$
- `AEL<E>(int n)`
  + Constructs AEL with `n` vertices
  + Time complexity: $\mathcal O(n)$
- `AEL<E>(int n, int m)`
  + Constructs AEL with `n` vertices and reserves space for `m` edges
  + Time complexity: $\mathcal O(n)$
- `int size()`
  + Returns the number of vertices
  + Time complexity: $\mathcal O(1)$
- `void add_edge(int u, const E &e)`
  + Adds an edge from vertex `u` with edge data `e`
  + Time complexity: $\mathcal O(1)$
- `range operator[](size_t i)` or `const_range operator[](size_t i)`
  + Returns a range of edges from vertex `i` that can be iterated
  + Time complexity: $\mathcal O(1)$
- Iterator support
  + Supports range-based for loops: `for (auto &e : g[v])`
  + Time complexity: $\mathcal O(\deg(v))$ to iterate all edges
