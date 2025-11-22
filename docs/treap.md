---
title: Treap
documentation_of: //ds/treap.hpp
---

## Description
Treap is a randomized binary search tree that supports sequence operations
under a monoid. It can split, merge, reverse ranges, and perform range queries
in $\mathcal O(\log n)$ time per operation. Example monoid:
```cpp
struct Sum {
  using T = int;
  static T id() { return 0; }
  static T op(T l, T r) { return l + r; }
};
```

## Operations
- `Treap<M>()`
  + Constructs empty treap
  + Time complexity: $\mathcal O(1)$
- `static Treap merge(const Treap &l, const Treap &r)`
  + Merges two treaps
  + Time complexity: $\mathcal O(\log n)$
- `pair<Treap, Treap> split(int k)`
  + Splits treap at position `k`, returning `[0, k)` and `[k, n)`
  + Time complexity: $\mathcal O(\log n)$
- `int size()`
  + Returns the number of elements
  + Time complexity: $\mathcal O(1)$
- `bool empty()`
  + Returns whether the treap is empty
  + Time complexity: $\mathcal O(1)$
- `T operator[](int p)` or `T get(int p)`
  + Returns the value at position `p`
  + Time complexity: $\mathcal O(\log n)$
- `void reverse(int l, int r)`
  + Reverses the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `T operator()(int l, int r)` or `T prod(int l, int r)`
  + Returns the product of the range `[l, r)`
  + Time complexity: $\mathcal O(\log n)$
- `T all_prod()`
  + Returns the product of all elements
  + Time complexity: $\mathcal O(1)$
- `void push_front(const T &x)`
  + Inserts `x` at the beginning
  + Time complexity: $\mathcal O(\log n)$
- `void push_back(const T &x)`
  + Inserts `x` at the end
  + Time complexity: $\mathcal O(\log n)$
- `void pop_front()`
  + Removes the first element
  + Time complexity: $\mathcal O(\log n)$
- `void pop_back()`
  + Removes the last element
  + Time complexity: $\mathcal O(\log n)$
