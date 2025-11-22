---
title: DSU on Tree
documentation_of: //tree/dsu_on_tree.hpp
---

## Description
DSU on Tree (also known as Sack) is a technique for efficiently answering
queries on subtrees. It uses small-to-large merging to achieve $\mathcal O(n
\log n)$ time for processing all subtree queries.

## Operations
- `DsuOnTree<G>(G &g, int root = 0)`
  + Constructs DSU on Tree instance for tree `g` with root `root`
  + Time complexity: $\mathcal O(n)$
- `void run(F1 &&add, F2 &&del, F3
  &&query)`
  + Processes all subtree queries
  + `add(v)` is called when adding vertex `v` to the current set
  + `del(v)` is called when removing vertex `v` from the current set
  + `query(v)` is called when the set contains exactly the vertices in the
    subtree of `v`
  + Time complexity: $\mathcal O(n \log n)$
