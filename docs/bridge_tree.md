---
title: Bridge Tree
documentation_of: //graph/bridge_tree.hpp
---

## Description
Bridge Tree decomposes a graph into its 2-edge-connected components and
constructs a tree where each node represents a component. The function
`two_cc` returns the component ID for each vertex, and `bridge_tree` returns
the component tree along with the component assignments.

## Operations
- `two_cc<G>(const G &g)`
  + Computes 2-edge-connected components of graph `g`
  + Returns a vector where each element is the component ID of the
    corresponding vertex
  + Time complexity: $\mathcal O(n + m)$
- `bridge_tree<G>(const G &g)`
  + Constructs the bridge tree of graph `g`
  + Returns a tuple `(ccs, id, tr)` where:
    - `ccs[i]` is the list of vertices in component `i`
    - `id[v]` is the component ID of vertex `v`
    - `tr` is the adjacency list of the bridge tree
  + Time complexity: $\mathcal O(n + m)$ or $\mathcal O(n + m \log m)$ if you
    erase duplicated edges
