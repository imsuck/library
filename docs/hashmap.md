---
title: Hash Map
documentation_of: //ds/hashmap.hpp
---

## Note
By default `hash_map` and `hash_set` does not support `std::pair`, `std::tuple`, etc.
Use [custom hash]({{ site.baseurl }}/other/chash.hpp) if you want to store them.

## `hash_map`
### Operations
- `hash_map<K, V, Hash = std::hash<K>>()`
  + Constructs hash map
  + Time complexity: $\mathcal O(1)$
- `set_default(V v)`
  + Sets default value of values
- `V &operator[](K k)`
  + Access value with key `k`, constructs default value if `k` is not found
  + Time complexity: $\mathcal O(1)$
- `V *emplace(K k, V v)`
  + Constructs key-value pair `(k, v)` if `k` did not exist already
  + Time complexity: $\mathcal O(1)$
- `void erase(K k)`
  + Erases key-value pair `(k, v)`, does nothing if `k` is not found
  + Time complexity: $\mathcal O(1)$
- `V *find(K k)`
  + Finds key-value pair `(k, v)`, returns pointer to `v` if found, `nullptr` if not
  + Time complexity: $\mathcal O(1)$

## `hash_set`
### Operations
- `hash_set<K, Hash = std::hash<K>>()`
  + Constructs hash set
  + Time complexity: $\mathcal O(1)$
- `void insert(K k)`
  + Inserts `k` into the set
  + Time complexity: $\mathcal O(1)$
- `void erase(K k)`
  + Erases `k`, does nothing if `k` is not found
  + Time complexity: $\mathcal O(1)$
- `null_type *find(K k)`
  + Finds `k`, returns `nullptr` if not found
  + Time complexity: $\mathcal O(1)$
