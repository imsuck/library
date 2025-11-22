---
title: Static Range Query
documentation_of: //ds/srq.hpp
---

## Description
Static Range Query (SRQ) solves offline range queries using divide and
conquer. For each query `[l, r)`, it computes `op(v[l], v[l+1], ..., v[r-1])`
where `op` is an associative operation.

## Operations
- `RangeQuery<T, Q, Op>(const vector<T> &v, const vector<Q> &q, Op op, T e)`
  + Constructs SRQ instance with array `v`, queries `q`, operation `op`, and
    identity `e`
  + Each query `Q` must have fields `l` and `r` representing range `[l, r)`
  + Time complexity: $\mathcal O(n + q)$
- `void solve()`
  + Solves all queries and stores results in `ans` vector
  + Time complexity: $\mathcal O((n + q) \log n)$
- `make_rq(const vector<T> &v, const vector<Q> &q, Op op, T e)`
  + Helper function to create a `RangeQuery` instance
  + Time complexity: $\mathcal O(n + q)$
