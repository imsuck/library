---
title: Dynamic Tree DP
documentation_of: //tree/dynamic_tree_dp.hpp
---

## Description
If we define the process of computing tree DP as follow:
```rust
struct TreeDP {
  struct Info;
  struct Point;
  struct Path;
  fn vertex(Info v) -> Path;
  fn add_vertex(Point t, Info v) -> Path;
  fn add_edge(Path t) -> Point;
  fn compress(Path p, Path c) -> Path;
  fn rake(Point l, Point r) -> Point;
};
```
- `Point`: Result of combining all light children of a vertex (Point cluster)
- `Path`: Result of combining vertices connected by a heavy edge (Path cluster)
- `vertex(v)`: Creates a path cluster consisting of only vertex `v`
- `add_vertex(t, v)`: Sets `v` to be the root of point cluster `t`
- `add_edge(t)`: Add a virtual root to point cluster `t` to make it a path cluster
- `compress(p, c)`: Merge two path cluster `p` and `c` (`p` is closer to the root),
  it is usually sufficient to only consider the boundary vertices when merging
- `rake(l, r)`: Merge point clusters `l` and `r`

```rust
fn calc_light(int v) -> Point {
  vector<Point> points;
  // skip g[v][0] which is a heavy child
  for (int i = 1; i < g[v].size(); i++) {
    Path res = calc_heavy(g[v][i]);
    points.push_back(add_edge(res));
  }
  for (int i = 1; i < points.size(); i++) {
    points[0] = rake(points[0], points[i]);
  }
  return points[0];
}
fn calc_heavy(int v) -> Path {
  vector<Path> paths;
  while(!g[r].empty()) {
    if(g[r].size() == 1) {
      // no light children
      paths.push_back(vertex(info[r]));
    } else {
      // compute light edges
      Point res = calc_light(r);
      paths.push_back(add_vertex(res, info[r]));
    }
    r = g[r][0]; // traverse down to heavy child
  }
  for(int i = 1; i < (int) paths.size(); i++) {
    paths[0] = compress(paths[0], paths[i]);
  }
  return paths[0];
}
```

All that's left is trying to balance a tree $T$ by binarizing it. This is done
via [Static Top Tree]({{ site.baseurl }}/tree/static_top_tree.hpp).

## Operations
- `DDP(int n, STT &stt, TreeDP dp)`
  + Initialize the data structure
  + Time complexity: $\mathcal O(n)$
- `void build()`
  + Computes DP using `DPP::info` (you set this manually)
  + Time complexity: $\mathcal O(n)$
- `void pull_from(int v)`
  + Recomputes DP from vertex `v`
  + Time complexity: $\mathcal O(\log n)$
- `void set(int v, const Info &x)`
  + Sets `info[v] = x` and recomputes DP from vertex `v`
  + Time complexity: $\mathcal O(\log n)$
- `Path query()`
  + Returns DP result
  + Time complexity: $\mathcal O(1)$
