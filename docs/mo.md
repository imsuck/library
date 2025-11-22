---
title: Mo's Algorithm
documentation_of: //other/mo.hpp
---

## Description
Mo's algorithm processes offline range queries efficiently by reordering
queries to minimize the number of element additions/removals.

## Operations
- `Mo(int n, const vector<pair<int, int>> &qs)`
  + Constructs Mo's algorithm instance with array size `n` and queries `qs`
  + Each query is a pair `(l, r)` representing range `[l, r)`
  + Time complexity: $\mathcal O(q \log q)$
- `void run(Eval eval, AL add_l, DL del_l, AR add_r, DR del_r)`
  + Processes queries with separate callbacks for adding/removing elements on
    left and right
  + `eval(i)` is called when query `i` should be evaluated
  + `add_l(i)` / `del_l(i)` are called when adding/removing element at index
    `i` from the left
  + `add_r(i)` / `del_r(i)` are called when adding/removing element at index
    `i` from the right
  + Time complexity: $\mathcal O(n \sqrt{q})$
- `void run(Eval eval, Add add, Del del)`
  + Processes queries with symmetric callbacks for adding/removing elements
  + `eval(i)` is called when query `i` should be evaluated
  + `add(i)` / `del(i)` are called when adding/removing element at index `i`
  + Time complexity: $\mathcal O(n \sqrt{q})$
