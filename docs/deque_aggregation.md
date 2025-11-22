---
title: Deque Aggregation
documentation_of: //ds/deque_aggregation.hpp
---

## Description
Deque Aggregation maintains a double-ended queue with range query support
under a monoid. Supports push/pop at both ends and querying the product of all
elements in $\mathcal O(1)$ amortized time per operation. Example monoid:
```cpp
struct Sum {
  using T = int;
  static T id() { return 0; }
  static T op(T l, T r) { return l + r; }
};
```

## Operations
- `DequeAggregation<M>()`
  + Constructs empty deque aggregation
  + Time complexity: $\mathcal O(1)$
- `T front()` or `T back()`
  + Returns the front/back element
  + Time complexity: $\mathcal O(1)$
- `void push_front(const T &x)` or `void push_back(const T &x)`
  + Inserts element at front/back
  + Time complexity: $\mathcal O(1)$ amortized
- `void pop_front()` or `void pop_back()`
  + Removes element from front/back
  + Time complexity: $\mathcal O(1)$ amortized
- `T query()`
  + Returns the product of all elements in the deque
  + Time complexity: $\mathcal O(1)$
- `int size()` or `bool empty()`
  + Returns size or whether deque is empty
  + Time complexity: $\mathcal O(1)$
