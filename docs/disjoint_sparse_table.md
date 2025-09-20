---
title: Disjoint Sparse Table
documentation_of: //ds/disjoint_sparse_table.hpp
---

## Overview
Handle range queries under semi-group, $\mathcal O(n\log n)$ build,
$\mathcal O(1)$ query.

## Usage
- Pass a semi-group with the following content:
  + Type `T`
  + `static T id()`
  + `static T op(T l, T r)`
- Querying: `prod(l, r)` returns the product in the range $[l, r)$

## Time complexity
- Constructor: $\mathcal O(n\log n)$
- `prod(l, r)`: $\mathcal O(1)$
