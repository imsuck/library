---
title: Block Cut Tree
documentation_of: //graph/block_cut.hpp
---

## Description
Block Cut Tree (BCT) decomposes a graph into its biconnected components and
represents them as a tree. The vertex numbering scheme is as follows:
- Vertices `[0, n)`: original vertices
- Vertices `[n, n_block)`: BCC (biconnected component) representatives

If vertex `v` is in component `C`, there is an edge `(v, id(C))` in the BCT.
Cut vertices (articulation points) are vertices `v` in `[0, n)` with degree at
least 2 in the BCT.

References:
- [noshi91's tweet](https://x.com/noshi91/status/1529858538650374144)
- [maspypy's implementation](https://maspypy.github.io/library/graph/block_cut.hpp)

## Operations
- `block_cut<G>(const G &g)`
  + Constructs the block cut tree of graph `g`
  + Returns an adjacency list representation of the BCT
  + Time complexity: $\mathcal O(n + m)$
