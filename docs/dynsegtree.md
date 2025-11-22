---
title: Dynamic Segment Tree
documentation_of: //ds/dynsegtree.hpp
---

## Description
Dynamic segment tree is a space-efficient segment tree that only allocates
nodes when needed. It can handle range queries with point updates under a
monoid in $\mathcal O(\log n)$ time per operation, using $\mathcal O(q \log
n)$ space where $q$ is the number of operations.

Example monoid:
```cpp
struct Sum {
  using T = int;
  static T id() { return 0; }
  static T op(T l, T r) { return l + r; }
};
```

## Operations
- `DynSegTree<M, I>(int n)`
  + Construct dynamic segment tree with coordinate space `[0, n)`
  + Time complexity: $\mathcal O(1)$
- `void set(I p, T x)`
  + Sets the value at `p` to be `x`
  + Time complexity: $\mathcal O(\log n)$
- `T operator[](I p)` or `T get(I p)`
  + Returns the value at `p`, returns identity if not set
  + Time complexity: $\mathcal O(\log n)$
- `T operator()(I l, I r)` or `T prod(I l, I r)`
  + Returns the product of the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `T all_prod()`
  + Returns the product of the entire coordinate space
  + Time complexity: $\mathcal O(\log n)$
