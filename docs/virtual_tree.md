---
title: Virtual Tree
documentation_of: //tree/virtual_tree.hpp
---

## Description
Virtual Tree constructs a tree containing only specified vertices and their
LCAs, preserving ancestor relationships. Useful for processing queries on a
subset of vertices efficiently. Requires HLD for LCA computation.

## Operations
- `VirtualTree(HLD &hld)`
  + Constructs virtual tree using HLD instance
  + Time complexity: $\mathcal O(1)$
- `template<class V> int build(V vs)`
  + Builds virtual tree from vertices `vs`
  + Returns the root of the virtual tree
  + Time complexity: $\mathcal O(k \log k)$ where $k$ is the number of
    vertices
- `auto &operator[](int v)`
  + Returns the adjacency list of vertex `v` in the virtual tree
  + Time complexity: $\mathcal O(1)$
