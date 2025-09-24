---
title: Disjoint Sparse Table
documentation_of: //ds/disjoint_sparse_table.hpp
---

## Description
Handle static range queries under a semi-group (identity element for
placeholding).

## Operations
- `DisjointSparseTable<M>(const vector<T> &v)`
  + Construct disjoint sparse table
  + Time complexity: $\mathcal O(n \log n)$
- `T prod(int l, int r)`
  + Returns the product of the range `[l, r)`
  + Time complexity: $\mathcal O(1)$

## Example
```cpp
struct M {
  using T = int;
  static T id() { return 1.1e9; }
  static T op(T l, T r) { return min(l, r); }
};
DisjointSparseTable<M> st(vector{1, 7, 2, 3});
assert(st.prod(1, 4) == 2);
```
