---
title: Strongly Connected Components
documentation_of: //graph/scc.hpp
---

## Description
Finds strongly connected components (SCCs) in a directed graph using Tarjan's
algorithm. The algorithm runs in $\mathcal O(V + E)$ time.

## Functions
- `find_scc(const G &g)`
  + Returns a vector of vectors, where each inner vector contains the vertices
    in one SCC
  + SCCs are returned in topological order
  + Time complexity: $\mathcal O(V + E)$
- `condense(const G &g)`
  + Returns a tuple `(scc, rep, gd)` where:
    - `scc`: vector of SCCs (same as `find_scc`)
    - `rep`: mapping from vertex to its SCC index
    - `gd`: condensed DAG where each node represents an SCC
  + Time complexity: $\mathcal O(V + E)$ or $\mathcal O(V + E \log E)$ if you
    erase duplicated edges
