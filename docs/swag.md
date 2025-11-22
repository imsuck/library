---
title: Sliding Window Aggregation (SWAG)
documentation_of: //ds/swag.hpp
---

## Description
Sliding Window Aggregation (SWAG) maintains a queue and supports querying the
aggregate of all elements in the queue under a monoid.

Example monoid:
```cpp
struct Sum {
  using T = int;
  static T id() { return 0; }
  static T op(T l, T r) { return l + r; }
};
```

## Operations
- `SWAG<M>()`
  + Constructs empty SWAG
  + Time complexity: $\mathcal O(1)$
- `void push(const T &x)`
  + Pushes `x` to the back of the queue
  + Time complexity: $\mathcal O(1)$ amortized
- `void pop()`
  + Pops from the front of the queue
  + Time complexity: $\mathcal O(1)$ amortized
- `T front()`
  + Returns the front element
  + Time complexity: $\mathcal O(1)$
- `T back()`
  + Returns the back element
  + Time complexity: $\mathcal O(1)$
- `T query()`
  + Returns the aggregate of all elements in the queue
  + Time complexity: $\mathcal O(1)$
- `int size()`
  + Returns the number of elements in the queue
  + Time complexity: $\mathcal O(1)$
- `bool empty()`
  + Returns whether the queue is empty
  + Time complexity: $\mathcal O(1)$
