---
title: Dynamic Modint
documentation_of: //math/dynmodint.hpp
---

## Description
Dynamic modular integer arithmetic with runtime modulus. The modulus can be set
at runtime and must be in the range $[1, 2^{31})$.

## Operations
- `static void set_mod(uint32_t m)`
  + Sets the modulus to `m` for all instances of this type
  + Must be called before using any operations
  + Time complexity: $\mathcal O(1)$

## Note
The template parameter `id` allows multiple independent moduli to be used
simultaneously.
