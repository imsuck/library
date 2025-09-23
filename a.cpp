#line 1 "test/yosupo/tree/dynamic_tree_vertex_set_path_composite_top_tree.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;

#line 2 "graph/top_tree.hpp"

// reference:
// https://ei1333.github.io/library/structure/dynamic-tree/top-tree.hpp
template<class TreeDP> struct TopTree {
    using Info = typename TreeDP::Info;
    using Point = typename TreeDP::Point;
    using Path = typename TreeDP::Path;

    struct node;
    using ptr = node *;
    vector<node> nodes;

    TopTree(int n = 0) : nodes(n) { for (int i = 0; i < n; i++); }
    TopTree(const vector<Info> &v) : nodes(v.size()) {
        for (int i = 0; i < v.size(); i++) {
            nodes[i].id = i;
            nodes[i].info = v[i];
            nodes[i].pull();
        }
    }
    ~TopTree() {
        for (auto &n : nodes) {
            auto del = [](auto f, auto t) {
                if (!t) return;
                f(f, t->l), f(f, t->r);
                delete t;
            };
            del(del, n.light);
            n.light = n.point = 0;
        }
    }

    auto operator[](int i) { return &nodes[i]; }

    void splay(int v) { splay(&nodes[v]); }
    void expose(int v) { expose(&nodes[v]); }
    void evert(int v) { evert(&nodes[v]); }
    void link(int v, int p) { link(&nodes[v], &nodes[p]); }
    void cut(int v) { cut(&nodes[v]); }
    void cut(int v, int r) { evert(r), cut(v); }
    void set(int v, const Info &x) {
        apply(v, [&x](auto &info) { info = x; });
    }
    template<class F> void apply(int v, F &&f) {
        expose(v), f(nodes[v].info), nodes[v].pull();
    }
    int lca(int u, int v) {
        ptr l = lca(&nodes[u], &nodes[v]);
        return l ? l->id : -1;
    }
    Path fold(int v) { return evert(v), nodes[v].sum; }
    Path fold_path(int v) { return expose(v), nodes[v].sum; }
    Path fold_path(int u, int v) { return evert(u), fold_path(v); }
    Path fold_subtree(int v) {
        expose(v);
        ptr l = nodes[v].l;
        nodes[v].l = 0, nodes[v].pull();
        Path ret = nodes[v].sum;
        nodes[v].l = l, nodes[v].pull();
        return ret;
    }
    Path fold_subtree(int v, int r) { return evert(r), fold_subtree(v); }

    struct rake_node {
        using rptr = rake_node *;
        rptr p = 0, l = 0, r = 0;
        Point val{}, sum{};

        rake_node(const Point &x) : val(x), sum(x) {}

        void pull() {
            sum = val;
            if (l) sum = TreeDP::rake(sum, l->sum);
            if (r) sum = TreeDP::rake(sum, r->sum);
        }

        rptr &ch(bool d) { return !d ? l : r; }
        static bool dir(rptr t) { return t == t->p->r; }
        static void rot(rptr t) {
            rptr p = t->p;
            int d = dir(t);
            t->p = p->p;
            if (p->p) p->p->ch(dir(p)) = t;
            if ((p->ch(d) = t->ch(!d))) p->ch(d)->p = p;
            t->ch(!d) = p, p->p = t;
            p->pull(), t->pull();
        }
        static void splay(rptr t) {
            for (; t->p; rot(t))
                if (t->p->p) dir(t) == dir(t->p) ? rot(t->p) : rot(t);
        }

        rptr rightmost() {
            rptr cur = this;
            while (cur->r) cur = cur->r;
            return cur;
        }
        friend rptr insert(rptr t, const Point &x) {
            rptr z = new rake_node(x);
            if (!t) return z;
            splay(t = t->rightmost());
            t->r = z, z->p = t;
            t->pull();
            return splay(z), z;
        }
        friend rptr erase(rptr t) {
            splay(t);
            rptr l = t->l, r = t->r;
            delete t;
            if (l) l->p = 0;
            if (r) r->p = 0;
            if (!l) {
                t = r;
            } else if (!r) {
                t = l;
            } else {
                splay(t = l->rightmost());
                t->r = r, r->p = t;
                t->pull();
            }
            return t;
        }
    };
    struct node {
        ptr p = 0, l = 0, r = 0;
        rake_node *light = 0, *point = 0;
        int id;
        bool rev = 0;
        Info info{};
        Path sum{}, mus{};

        void pull() {
            Path raked = light ? TreeDP::add_vertex(light->sum, info)
                                : TreeDP::vertex(info);
            sum = mus = raked;
            if (l) {
                sum = TreeDP::compress(l->sum, sum);
                mus = TreeDP::compress(mus, l->mus);
            }
            if (r) {
                sum = TreeDP::compress(sum, r->sum);
                mus = TreeDP::compress(r->mus, mus);
            }
        }
        void flip() { swap(l, r), swap(sum, mus), rev ^= 1; }
        void push() {
            if (exchange(rev, 0)) {
                if (l) l->flip();
                if (r) r->flip();
            }
        }

        ptr &ch(bool d) { return !d ? l : r; }
        static bool is_root(ptr t) {
            return !t->p || (t != t->p->l && t != t->p->r);
        }
        static bool dir(ptr t) { return t == t->p->r; }
        static void rot(ptr t) {
            ptr p = t->p;
            int d = dir(t);
            t->p = p->p;
            if (!is_root(p)) p->p->ch(dir(p)) = t;
            if ((p->ch(d) = t->ch(!d))) p->ch(d)->p = p;
            t->ch(!d) = p, p->p = t;
            p->pull(), t->pull();
        }
        static void splay(ptr t) {
            t->push();
            {
                ptr cur = t;
                while (!is_root(cur)) cur = cur->p;
                t->point = cur->point;
                if (t != cur) cur->point = 0;
            }
            for (; !is_root(t); rot(t)) {
                ptr p = t->p, g = p->p;
                if (g) g->push();
                p->push(), t->push();
                if (!is_root(p)) rot(dir(t) == dir(p) ? p : t);
            }
        }
    };

    static ptr expose(ptr t) {
        ptr prv = 0;
        for (ptr cur = t; cur; cur = cur->p) {
            node::splay(cur);
            if (cur->r) {
                cur->light = insert(cur->light, TreeDP::add_edge(cur->r->sum));
                cur->r->point = cur->light;
            }
            if (prv) {
                prv->push();
                cur->light = erase(prv->point);
            }
            cur->r = exchange(prv, cur), cur->pull();
        }
        node::splay(t);
        return prv;
    }
    static void evert(ptr t) { expose(t), t->flip(); }
    static void link(ptr v, ptr p) {
        evert(v), expose(p);
        assert(!p->r);
        p->r = v, v->p = p, p->pull();
    }
    static void cut(ptr v) {
        expose(v);
        assert(v->l);
        v->l = v->l->p = 0, v->pull();
    }
    static ptr lca(ptr u, ptr v) {
        if (u == v) return u;
        expose(u);
        ptr l = expose(v);
        return u->p ? l : 0;
    }
};
#line 2 "math/modint.hpp"

// clang-format off
template<uint32_t m> struct modint {
    static_assert(m >= 1, "Modulus must be in the range [1;2^31)");

    using mint = modint;
    static constexpr bool is_simple = true;

    static constexpr uint32_t mod() noexcept { return m; }
    constexpr modint() noexcept = default;
    constexpr modint(int64_t v) noexcept : _v(uint32_t((v %= m) < 0 ? v + m : v)) {}
    constexpr static mint raw(uint32_t v) noexcept { mint x; return x._v = v, x; }
    template<class T> constexpr explicit operator T() const noexcept { return _v; }

    constexpr mint &operator++() noexcept { return _v = ++_v == mod() ? 0 : _v, *this; }
    constexpr mint &operator--() noexcept { --(_v ? _v : _v = mod()); return *this; }
    constexpr mint operator++(int) noexcept { return exchange(*this, ++mint(*this)); }
    constexpr mint operator--(int) noexcept { return exchange(*this, --mint(*this)); }

    constexpr mint &operator+=(mint rhs) noexcept {
        return _v = int(_v += rhs._v - mod()) < 0 ? _v + mod() : _v, *this;
    }
    constexpr mint &operator-=(mint rhs) noexcept {
        return _v = int(_v -= rhs._v) < 0 ? _v + mod() : _v, *this;
    }
    constexpr mint &operator*=(mint rhs) noexcept {
        return _v = uint64_t(_v) * rhs._v % mod(), *this;
    }
    constexpr mint &operator/=(mint rhs) noexcept {
        return *this = *this * rhs.inv();
    }

    constexpr friend mint operator+(mint l, mint r) noexcept { return l += r; }
    constexpr friend mint operator-(mint l, mint r) noexcept { return l -= r; }
    constexpr friend mint operator*(mint l, mint r) noexcept { return l *= r; }
    constexpr friend mint operator/(mint l, mint r) noexcept { return l /= r; }

    constexpr mint operator+() const noexcept { return *this; }
    constexpr mint operator-() const noexcept { return raw(_v ? mod() - _v : 0); }

    constexpr friend bool operator==(mint l, mint r) noexcept { return l._v == r._v; }
    constexpr friend bool operator!=(mint l, mint r) noexcept { return l._v != r._v; }
    constexpr friend bool operator<(mint l, mint r) noexcept { return l._v < r._v; }

    constexpr mint pow(uint64_t n) const noexcept {
        mint b = *this, res = 1;
        while (n) n & 1 ? res *= b : 0, b *= b, n >>= 1;
        return res;
    }

    constexpr mint inv() const noexcept {
        int a = _v, b = mod(), x = 1, y = 0;
        while (b) {
            x = exchange(y, x - a / b * y);
            a = exchange(b, a % b);
        }
        assert(a == 1);
        return x;
    }

    friend istream &operator>>(istream &is, mint &x) {
        int64_t v{};
        return is >> v, x = v, is;
    }
    friend ostream &operator<<(ostream &os, const mint &x) { return os << x._v; }

  private:
    uint32_t _v = 0;
};
using modint107 = modint<1'000'000'007>;
using modint998 = modint<998'244'353>;
// clang-format on
#line 2 "other/types.hpp"

using i8 = int8_t;
using u8 = uint8_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f80 = long double;
using str = string;
template<class T> using vec = vector<T>;
template<class E = i32> using graph = vec<vec<E>>;
#line 9 "test/yosupo/tree/dynamic_tree_vertex_set_path_composite_top_tree.test.cpp"

using mint = modint998;

struct TreeDP {
    struct Info {
        mint a, b;
    };
    struct Point {};
    struct Path {
        mint a, b;
    };
    static Path vertex(Info x) { return {x.a, x.b}; }
    static Path add_vertex(Point, Info) { return {1, 0}; }
    static Point add_edge(Path t) { return {}; }
    static Path compress(Path p, Path c) {
        return {c.a * p.a, c.a * p.b + c.b};
    }
    static Point rake(Point, Point) { return {}; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, q;
    cin >> n >> q;
    vector<TreeDP::Info> a(n);
    for (auto &[b, c] : a) cin >> b >> c;
    TopTree<TreeDP> tr(a);
    for (i32 i = 0, u, v; i < n - 1; i++) cin >> u >> v, tr.link(u, v);
    while (q--) {
        i32 t;
        cin >> t;
        if (t == 0) {
            i32 a, b, c, d;
            cin >> a >> b >> c >> d;
            tr.cut(a, b), tr.link(c, d);
        } else if (t == 1) {
            i32 p, c, d;
            cin >> p >> c >> d;
            tr.set(p, {c, d});
        } else {
            i32 u, v, x;
            cin >> u >> v >> x;
            auto [a, b] = tr.fold_path(u, v);
            cout << a * x + b << "\n";
        }
    }
}
