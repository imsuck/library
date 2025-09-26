---
title: Ordered Set
documentation_of: //ds/ordered_set.hpp
---

## Description
A set which can perform order statistic queries.

## Operations
- `ordered_set<T>(int n)`
  + Construct an ordered set
  + Time complexity: $\mathcal O(1)$
- `void insert(T k)`
  + Inserts `k` into the set
  + Time complexity: $\mathcal O(\log n)$
- `void erase(T k)`
  + Erases `k` from the set
  + Time complexity: $\mathcal O(\log n)$
- `optional<T> kth_order(int k)`
  + Returns the element which has `k` elements before it
  + Time complexity: $\mathcal O(\log n)$
- `int order_of(T k, bool include = true)`
  + Count the number of elements less than (or equal if `include == true`) to `k`
  + Time complexity: $\mathcal O(\log n)$
- `optional<T> pre_upper_bound(T k)`
  + Finds the maximum element less than or equal to `k`
  + Time complexity: $\mathcal O(\log n)$
- `optional<T> lower_bound(T k)`
  + Finds the minimum element greater than or equal to `k`
  + Time complexity: $\mathcal O(\log n)$
