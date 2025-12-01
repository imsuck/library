---
title: Top Tree (ecnerwala)
documentation_of: //tree/top_tree_ecnerwala.hpp
---

## Description
Top Tree (ecnerwala) is an implementation of top trees for maintaining dynamic
trees and supporting path and subtree queries. This implementation uses a
different structure than the other top tree implementation. Users must define
a node type that inherits from `top_tree_node_base`.

Reference:
[ecnerwala's
implementation](https://github.com/ecnerwala/cp-book/blob/master/src/top_tree.hpp)

## Node Structure

Nodes can be vertices or edges. Vertices are created with `set_vert()`, and
edges are linked between vertices. Nodes have three child pointers `c[0]`,
`c[1]`, `c[2]` and flags `is_vert` and `is_path`. Methods `push`, `pull`, `flip`
can be omitted from the struct declaration.

Example node:
```cpp
struct node : top_tree_node_base<node> {
    int val = 0, sum = 0;
    int path_lazy = 0;
    
    void push() {
        // Be careful not to push path update from vertices!
        if (!is_vert) {
            if (c[0]) c[0]->do_path_update(path_lazy);
            if (c[1]) c[1]->do_path_update(path_lazy);
        }
        path_lazy = 0;
    }
    
    void pull() {
        // update aggregate information from children
        sum = is_vert ? val : 0;
        for (int i = 0; i < 3; i++) {
            if (c[i]) sum += c[i]->sum;
        }
        // sometimes you need to handle different node aggregation types
        if (is_vert) { // add_vertex(self, rake(c[0], c[1]))
            // ...
        } else if (is_path) { // compress(c[0], self, c[1])
            // ...
        } else { // rake(c[0], add_edge(self, c[2]), c[1])
            // ...
        }
    }
    
    void flip() {
        // optional: handle path reversal
    }
};
```

## Usage Pattern

```cpp
// Create vertices
vector<node> vert(n);
for (int i = 0; i < n; i++) {
    vert[i].val = ...;
    vert[i].set_vert();
}

// Create edges
map<pair<int, int>, node> edges;
link(&edges[{u, v}], &vert[u], &vert[v]);

// Update edge info
edges[{u, v}].expose_edge();
edges[{u, v}].weight = ...;
edges[{u, v}].pull_all();

// Query path
vert[u].evert();
auto path = get_path(&vert[v]);
cout << path->aggregate;
path->do_lazy_update();
path->push_all();

// Query subtree
vert[p].evert();
auto subtree = get_subtree(&vert[v]);
cout << subtree->aggregate;
subtree->do_lazy_update();
subtree->push_all();
```

## Operations
- `void this->set_vert()`
  + Marks a node as a vertex
  + Must be called after setting vertex data
  + Time complexity: $\mathcal O(1)$
- `ptr this->expose()`
  + Exposes path from this vertex to root
  + Returns the root of the exposed path
  + Time complexity: $\mathcal O(\log n)$ amortized
- `ptr this->expose_edge()`
  + Exposes path containing this edge
  + Returns the root of the exposed path
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void this->evert()`
  + Makes this vertex the root of its tree
  + Time complexity: $\mathcal O(\log n)$ amortized
- `void this->push_all()`
  + Pushes lazy updates from root to this node
  + Time complexity: $\mathcal O(\text{depth})$
- `ptr this->pull_all()`
  + Pulls aggregate information from this node to root
  + Returns the root
  + Time complexity: $\mathcal O(\text{depth})$
- `friend void link(ptr e, ptr v, ptr p)`
  + Links vertex `v` as a child of `p` with edge `e`
  + Time complexity: $\mathcal O(\log n)$ amortized
- `friend bool link_root(ptr e, ptr v, ptr p)`
  + Links root of `v`'s tree as a child of `p` with edge `e`
  + Returns `false` if `v` and `p` are already in the same tree
  + Time complexity: $\mathcal O(\log n)$ amortized
- `friend pair<ptr, ptr> cut(ptr e)`
  + Cuts edge `e`, splitting the tree
  + Returns pair of roots of the two resulting trees
  + Time complexity: $\mathcal O(\log n)$ amortized
- `friend ptr get_path(ptr v)`
  + Returns the path node from root to `v`
  + `v` must be a vertex
  + Time complexity: $\mathcal O(\log n)$ amortized
- `friend ptr get_subtree(ptr v)`
  + Returns the subtree node rooted at `v`
  + `v` must be a vertex
  + Time complexity: $\mathcal O(\log n)$ amortized
- `friend ptr lca(ptr u, ptr v)`
  + Returns LCA of `u` and `v`, or `nullptr` if not connected
  + Time complexity: $\mathcal O(\log n)$ amortized
