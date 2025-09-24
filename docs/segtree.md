---
title: Segment Tree
documentation_of: //ds/segtree.hpp
---

## Description
Handle range queries with point updates under a monoid.
Example monoid:
```cpp
struct Sum {
  using T = int;
  static T id() { return 0; }
  static T op(T l, T r) { return l + r; }
};
```

## Operations
- `SegTree<M>(int n)`
  + Constructs segment tree with identity elements
  + Time complexity: $\mathcal O(n)$
- `SegTree<M>(const vector<T> &v)`
  + Constructs segment tree using `v`
  + Time complexity: $\mathcal O(n)$
- `SegTree<M>(int n, Gen gen)`
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
- `int max_right(int l, G g)`
  + Finds the maximum `r` such that `g(prod(l, r)) == true`. For requirements of `g`, please
    visit [ac-library's segtree docs](https://atcoder.github.io/ac-library/production/document_en/segtree.html)
  + Time complexity: $\mathcal O(\log n)$
- `int min_left(int r, G g)`
  + Finds the maximum `l` such that `g(prod(l, r)) == true`. For requirements of `g`, please
    visit [ac-library's segtree docs](https://atcoder.github.io/ac-library/production/document_en/segtree.html)
  + Time complexity: $\mathcal O(\log n)$
- `vector<T> to_vec()`
  + Returns a vector of leaf nodes
  + Time complexity: $\mathcal O(n)$
