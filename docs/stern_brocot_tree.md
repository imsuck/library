---
title: Stern-Brocot Tree
documentation_of: //math/stern_brocot_tree.hpp
---

## Description
Stern-Brocot Tree represents rational numbers in a binary search tree
structure. Each node corresponds to a rational number, and navigation
operations allow moving to parent/child nodes. Useful for binary search on
rationals and finding continued fraction representations.

## Operations
- `sbt_node<Int>()`
  + Constructs node at root (represents 1/1)
  + Time complexity: $\mathcal O(1)$
- `sbt_node<Int>(Int a, Int b)` or `sbt_node<Int>(const rational &x)`
  + Constructs node representing rational `a/b`
  + Time complexity: $\mathcal O(\log \max(a, b))$
- `sbt_node<Int>(const sbt_path &path)`
  + Constructs node from path description
  + Time complexity: $\mathcal O(\text{path length})$
- `operator rational()` or `rational get()`
  + Returns the rational value represented by this node
  + Time complexity: $\mathcal O(1)$
- `pair<rational, rational> range()`
  + Returns the range of rationals in the subtree
  + Time complexity: $\mathcal O(1)$
- `Int depth()`
  + Returns the depth of the node
  + Time complexity: $\mathcal O(1)$
- `const sbt_path &path()`
  + Returns the path from root to this node
  + Time complexity: $\mathcal O(1)$
- `bool go_up(Int k)`
  + Moves up `k` levels toward root
  + Returns `false` if insufficient depth
  + Time complexity: $\mathcal O(k)$
- `void go_down(sbt_arc dir, Int k)`
  + Moves down `k` steps in direction `dir` (Left or Right)
  + Time complexity: $\mathcal O(1)$
- `friend sbt_node lca(const sbt_node &a, const sbt_node &b)`
  + Returns LCA of two nodes
  + Time complexity: $\mathcal O(\min(\text{depth}(a), \text{depth}(b)))$
- `friend Int dist(const sbt_node &a, const sbt_node &b)`
  + Returns distance between two nodes
  + Time complexity: $\mathcal O(\min(\text{depth}(a), \text{depth}(b)))$
