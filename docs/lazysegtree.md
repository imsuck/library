---
title: Lazy Segment Tree
documentation_of: //ds/lazysegtree.hpp
---

## Description
Handle range queries with range updates under a monoid. Example monoid:
```cpp
struct RangeAffineRangeSum {
  using T = array<int, 2>;
  using F = array<int, 2>;
  static T id() { return {0, 0}; }
  static F fid() { return 0; }
  static T op(T l, T r) { return {l[0] + r[0], l[1] + r[1]}; }
  static F comp(F l, F r) { return {r[0] * l[0], r[0] * l[1] + r[1]}; }
  // return false to force update children (segment tree beats)
  static bool map(F f, T &x) {
    x[0] = x[0] * f[0] + x[1] * f[1];
    return true;
  }
};
```

## Operations
- `LazySegTree<M>(int n)`
  + Constructs segment tree with identity elements
  + Time complexity: $\mathcal O(n)$
- `LazySegTree<M>(const vector<T> &v)`
  + Constructs segment tree using `v`
  + Time complexity: $\mathcal O(n)$
- `LazySegTree<M>(int n, Gen gen)`
  + Constructs segment tree using `gen(i)`
  + Time complexity: $\mathcal O(n)$
- `void set(int p, T x)`
  + Sets the value at `p` to be `x`, consider using `operator[]`
  + Time complexity: $\mathcal O(\log n)$
- `void mul(int p, T x)`
  + Sets the value at `p` (denoted as `a[p]`) to be `M::op(a[p], x)`
  + Time complexity: $\mathcal O(\log n)$
- `T operator()(int l, int r)` or `T prod(int l, int r)`
  + Returns the product of the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `void apply(int l, int r, F f)`
  + Applies update `f` to the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `int max_right(int l, G g)`
  + Finds the maximum `r` such that `g(prod(l, r)) == true`. For requirements of `g`, please visit
    [ac-library's `segtree` docs](https://atcoder.github.io/ac-library/production/document_en/segtree.html)
  + Time complexity: $\mathcal O(\log n)$
- `int min_left(int r, G g)`
  + Finds the maximum `l` such that `g(prod(l, r)) == true`. For requirements of `g`, please visit
    [ac-library's `segtree` docs](https://atcoder.github.io/ac-library/production/document_en/segtree.html)
  + Time complexity: $\mathcal O(\log n)$
- `vector<T> to_vec()`
  + Returns a vector of leaf nodes
  + Time complexity: $\mathcal O(n)$
