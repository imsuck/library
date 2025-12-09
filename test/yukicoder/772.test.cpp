#define PROBLEM "https://yukicoder.me/problems/no/772"

#include <bits/stdc++.h>
using namespace std;

#include "other/types.hpp"
#include "tree/top_tree_ecnerwala.hpp"

struct node : top_tree_node_base<node> {
    i32 val, sub, max_sub;
    i64 path_len;
    array<i64, 2> ans;

    void flip() { swap(ans[0], ans[1]); }

    void pull() {
        sub = max_sub = path_len = 0;
        ans.fill(0);

        for (i32 z = 0; z <= 2; z++) {
            if (!c[z]) continue;
            sub += c[z]->sub;
            if (z == 2) continue;
            ans[0] += c[z]->ans[0];
            max_sub = max(max_sub, c[z]->max_sub);
        }

        if (is_vert) {
            sub += val;
            ans[1] = ans[0];
        } else if (is_path) {
            path_len = val;
            for (i32 z = 0; z < 2; z++) {
                path_len += c[z]->path_len;
                ans[z] = c[z]->ans[z] + c[!z]->ans[z] +
                         (c[z]->path_len + val) * c[!z]->sub;
            }
        } else {
            ans[0] += c[2]->ans[0] + 1LL * val * c[2]->sub;
            max_sub = max(max_sub, c[2]->sub);
            ans[1] = ans[0];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i32 n, q;
    cin >> n >> q;

    vector<node> vs(n);
    map<pair<i32, i32>, node> edge;
    auto es = [&](i32 u, i32 v) -> node & { return edge[minmax(u, v)]; };
    auto lnk = [&](i32 u, i32 v) { link(es(u, v), vs[u], vs[v]); };
    auto ct = [&](i32 u, i32 v) { cut(es(u, v)), edge.erase(minmax(u, v)); };

    for (i32 i = 0; i < n; i++) {
        vs[i].val = 1;
        vs[i].set_vert();
    }

    i64 sum = 0;
    auto rd_vert = [&]() -> i32 {
        i32 v;
        cin >> v;
        return (v - 1 + sum) % n;
    };

    for (i32 qi = 0; qi < q; qi++) {
        i32 op;
        cin >> op;
        if (op == 1) {
            i32 u = rd_vert(), v = rd_vert(), w;
            cin >> w;
            es(u, v).val = w;
            lnk(u, v);
        } else if (op == 2) {
            ct(rd_vert(), rd_vert());
        } else if (op == 3) {
            i32 v = rd_vert();

            vs[v].evert();
            vs[v].val ^= 1;
            vs[v].pull_all();

            i32 N = vs[v].sub;
            i64 right_sum = 0;
            auto centroid = search(&vs[v], [&](node *p) -> node * {
                if (p->is_path && !p->is_vert) {
                    assert(p->c[0] && p->c[1]);
                    if (2 * (p->c[1]->sub + right_sum) <= N) {
                        right_sum += p->c[1]->sub;
                        return p->c[0];
                    } else {
                        return p->c[1];
                    }
                } else {
                    right_sum = 0;
                    if (2 * p->max_sub <= N) return 0;
                    if (p->c[0] && 2 * p->c[0]->max_sub > N) return p->c[0];
                    if (p->c[1] && 2 * p->c[1]->max_sub > N) return p->c[1];
                    return p->c[2];
                }
            });

            cout << centroid->ans[0] << "\n";
            sum += centroid->ans[0];
            sum %= n;
        }
    }
}
