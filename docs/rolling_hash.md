---
title: Rolling Hash
documentation_of: //ds/rolling_hash.hpp
---

## Description
Rolling hash computes polynomial hashes of strings or arrays using a base and
modulus. This implementation uses modulus $2^{61} - 1$ for fast modular
arithmetic.

## Operations
- `RollingHash(const string &s, u64 base)`
  + Construct rolling hash from string `s` with given `base`
  + Time complexity: $\mathcal O(n)$
- `RollingHash(const vector<T> &v, u64 base)`
  + Construct rolling hash from vector `v` with given `base`
  + Time complexity: $\mathcal O(n)$
- `u64 query(int l, int r)`
  + Returns the hash of the substring `[l, r)`
  + Time complexity: $\mathcal O(1)$
- `u64 concat(u64 l, u64 r, u64 lenr)`
  + Returns the hash of concatenating hash `l` with hash `r` (where `r` has
    length `lenr`)
  + Time complexity: $\mathcal O(1)$
- `void push_back(char c)`
  + Appends character `c` to the end of the string
  + Time complexity: $\mathcal O(1)$
- `static u64 gen_base()`
  + Generates a random base suitable for hashing
  + Time complexity: $\mathcal O(1)$
