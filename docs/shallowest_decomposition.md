---
title: Shallowest Decomposition
documentation_of: //graph/shallowest_decomposition.hpp
---

## Description
Shallowest Decomposition constructs a tree decomposition that minimizes the
maximum depth. It uses a greedy algorithm to assign labels and build chains,
resulting in a tree with optimal depth properties.

## Operations
- `shallowest_decomp<G>(const G &g)`
  + Constructs the shallowest decomposition of tree `g`
  + Returns a pair `(tree, root)` where:
    - `tree` is the decomposed tree structure
    - `root` is the root of the decomposition
  + Time complexity: $\mathcal O(n)$
