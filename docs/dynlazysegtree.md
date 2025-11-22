---
title: Dynamic Lazy Segment Tree
documentation_of: //ds/dynlazysegtree.hpp
---

## Description
Dynamic lazy segment tree is a space-efficient lazy segment tree that only
allocates nodes when needed. It can handle range queries with range updates
under a monoid in $\mathcal O(\log n)$ time per operation, using $\mathcal
O(q \log n)$ space where $q$ is the number of operations. This is useful when
the coordinate space is large but only a few indices are accessed.

Example monoid:
```cpp
struct RangeAffineRangeSum {
  using T = array<int, 2>;
  using F = array<int, 2>;
  static T id() { return {0, 0}; }
  static F fid() { return {1, 0}; }
  static T op(T l, T r) { return {l[0] + r[0], l[1] + r[1]}; }
  static F comp(F l, F r) { return {r[0] * l[0], r[0] * l[1] + r[1]}; }
  static T map(F f, T x, I tl, I tr) {
    return {x[0] * f[0] + x[1] * f[1], x[1]};
  }
};
```

## Operations
- `DynLazySegTree<M, I>(I n)`
  + Construct dynamic lazy segment tree with coordinate space `[0, n)`
  + Time complexity: $\mathcal O(1)$
- `T operator()(I l, I r)` or `T prod(I l, I r)`
  + Returns the product of the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `void apply(I l, I r, F f)`
  + Applies update `f` to the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `I max_right(I l, G g)`
  + Finds the maximum `r` such that `g(prod(l, r)) == true`. For
    requirements of `g`, please visit [ac-library's `segtree`
    docs](https://atcoder.github.io/ac-library/production/document_en/segtree.html)
  + Time complexity: $\mathcal O(\log n)$
