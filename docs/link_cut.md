---
title: Link Cut Tree
documentation_of: //tree/link_cut.hpp
---

## Description
Link Cut Tree (LCT) is a data structure for maintaining a forest of trees
and supporting link, cut, and path operations. It uses splay trees internally
to achieve $\mathcal O(\log n)$ amortized time per operation. Users must
define a node type that inherits from `lct_node`.

Example node to handle subtree sum:
```cpp
struct node : lct_node<node> {
    // use the default constructor
    using lct_node::lct_node;

    i64 val = 0, sum = 0, light = 0;

    void set(i32 x) { val = x; }
    void add(i32 x) { val += x; }

    void pull() { sum = $(l)->sum + $(r)->sum + val + light; }
    void add_light(ptr c) { light += c->sum; }
    void sub_light(ptr c) { light -= c->sum; }
};
```

## Operations
- `LCT<node>(int n = 0)`
  + Constructs LCT with `n` nodes
  + Time complexity: $\mathcal O(n)$
- `auto operator[](int i)`
  + Returns pointer to node `i`
  + Time complexity: $\mathcal O(1)$
- `int id(ptr t)`
  + Returns the ID of node `t`
  + Time complexity: $\mathcal O(1)$

Note: All operations from `splay` onwards have static pointer variants that
take `ptr` (pointer) arguments instead of `int` (vertex ID) arguments.

- `void splay(int v)`
  + Splays node `v` to root of its splay tree
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void expose(int v)`
  + Exposes path from `v` to root, making `v` the root of its splay tree
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void expose_path(int u, int v)`
  + Exposes path from `u` to `v`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void evert(int v)`
  + Makes `v` the root of its tree
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void link(int v, int p)`
  + Links node `v` as a child of `p` (must be root of its tree)
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void cut(int v, int p)`
  + Cuts edge between `v` and `p`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `int lca(int u, int v)`
  + Returns LCA of `u` and `v`, or `-1` if not connected
  + Time complexity: $\mathcal O(\log n)$ amortized
- `template<class... T> void set(int v, T &&...x)`
  + Exposes `v` and calls `set` on the node
  + Time complexity: $\mathcal O(\log n)$ amortized
- `template<class... T> void add(int v, T &&...x)`
  + Exposes `v` and calls `add` on the node
  + Time complexity: $\mathcal O(\log n)$ amortized
