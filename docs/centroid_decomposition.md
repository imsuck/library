---
title: Centroid Decomposition
documentation_of: //graph/centroid_decomposition.hpp
---

## Description
Centroid Decomposition decomposes a tree by repeatedly finding centroids and
recursively decomposing subtrees. Returns the level, component size, and parent
for each vertex in the centroid tree.

## Operations
- `centroid_decomp<G>(const G &g)`
  + Constructs the centroid decomposition of tree `g`
  + Returns a tuple `(lvl, sz_comp, par)` where:
    - `lvl[v]` is the level of vertex `v` in the centroid tree
    - `sz_comp[v]` is the size of the component when `v` was chosen as
      centroid
    - `par[v]` is the parent of `v` in the centroid tree
  + Time complexity: $\mathcal O(n \log n)$
