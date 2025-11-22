---
title: 2-SAT
documentation_of: //other/two_sat.hpp
---

## Description
2-SAT solver using strongly connected components. Variables are represented
as integers $0$ to $n-1$, with bitwise not representing negation (`~x` is $\neg
x$).

## Operations
- `TwoSAT(int n)`
  + Constructs 2-SAT instance with `n` variables
  + Time complexity: $\mathcal O(1)$
- `void add_if(int x, int y)`
  + Adds constraint: if $x$ then $y$ (equivalent to $\neg x \lor y$)
  + Time complexity: $\mathcal O(1)$
- `void add_or(int x, int y)`
  + Adds constraint: $x \lor y$
  + Time complexity: $\mathcal O(1)$
- `void add_nand(int x, int y)`
  + Adds constraint: $\neg(x \land y)$ (equivalent to $\neg x \lor \neg y$)
  + Time complexity: $\mathcal O(1)$
- `void set_true(int x)`
  + Forces variable $x$ to be true
  + Time complexity: $\mathcal O(1)$
- `void set_false(int x)`
  + Forces variable $x$ to be false
  + Time complexity: $\mathcal O(1)$
- `vector<bool> run()`
  + Solves the 2-SAT instance
  + Returns a satisfying assignment if one exists, empty vector otherwise
  + Time complexity: $\mathcal O(V + E)$ where $V = 2n$ and $E$ is the number
    of constraints
