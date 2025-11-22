---
title: Circular Deque
documentation_of: //ds/circular_deque.hpp
---

## Description
Circular Deque is a fixed-size or dynamically-sized double-ended queue
implemented using a circular buffer. Provides efficient push/pop operations
at both ends in $\mathcal O(1)$ time.

## Operations
- `CircularDeque<T, N>()`
  + Constructs fixed-size circular deque with capacity `N`
  + Time complexity: $\mathcal O(1)$
- `DynamicCircularDeque<T>()`
  + Constructs dynamically-sized circular deque with initial capacity 8
  + Time complexity: $\mathcal O(1)$
- `template<class... Ts> T &emplace_front(Ts &&...xs)`
  + Constructs element at front using arguments
  + Time complexity: $\mathcal O(1)$
- `template<class... Ts> T &emplace_back(Ts &&...xs)`
  + Constructs element at back using arguments
  + Time complexity: $\mathcal O(1)$
- `T &push_front(T x)` or `T &push_back(T x)`
  + Inserts element at front/back
  + Time complexity: $\mathcal O(1)$
- `void pop_front()` or `void pop_back()`
  + Removes element from front/back
  + Time complexity: $\mathcal O(1)$
- `T &front()` or `T &back()`
  + Returns reference to front/back element
  + Time complexity: $\mathcal O(1)$
- `T &operator[](size_t i)`
  + Returns reference to element at index `i`
  + Time complexity: $\mathcal O(1)$
- `size_t size()` or `bool empty()`
  + Returns size or whether deque is empty
  + Time complexity: $\mathcal O(1)$
- `void clear()`
  + Clears the deque
  + Time complexity: $\mathcal O(1)$
- `void reserve(int n)` (DynamicCircularDeque only)
  + Reserves capacity for at least `n` elements
  + Time complexity: $\mathcal O(n)$
