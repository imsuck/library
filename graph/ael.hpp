#pragma once

//! Adjacency edge list
//  Doesn't support g[v][i] D:

template<class E> struct AEL {
    using internal_edge = pair<E, int>;

    AEL() {}
    AEL(int _n) : n(_n), head(n, -1) {}
    AEL(int _n, int m) : AEL(_n) { edges.reserve(m); }

    int size() const { return n; }

    void add_edge(int u, const E &e) {
        edges.emplace_back(e, head[u]), head[u] = (int)edges.size() - 1;
    }

    struct range {
        internal_edge *edges;
        const int first;
        struct iterator {
            internal_edge *edges = edges;
            int p;
            bool operator!=(const iterator &r) const { return p != r.p; }
            void operator++() { p = edges[p].second; }
            E &operator*() { return edges[p].first; }
        };
        iterator begin() { return {edges, first}; }
        iterator end() { return {edges, -1}; }
    };
    struct const_range {
        const internal_edge *edges;
        const int first;
        struct iterator {
            const internal_edge *edges;
            int p;
            bool operator!=(const iterator &r) const { return p != r.p; }
            void operator++() { p = edges[p].second; }
            const E &operator*() const { return edges[p].first; }
        };
        iterator begin() const { return {edges, first}; }
        iterator end() const { return {edges, -1}; }
    };
    range operator[](size_t i) {
        assert(i <= size());
        return {edges.data(), head[i]};
    }
    const_range operator[](size_t i) const {
        assert(i <= size());
        return {edges.data(), head[i]};
    }

    struct iterator {
        AEL *g;
        int p;
        bool operator!=(const iterator &r) const { return p != r.p; }
        void operator++() { p++; }
        range operator*() { return (*g)[p]; }
    };
    struct const_iterator {
        const AEL *g;
        int p;
        bool operator!=(const const_iterator &r) const { return p != r.p; }
        void operator++() { p++; }
        const_range operator*() const { return (*g)[p]; }
    };
    iterator begin() { return {this, 0}; }
    iterator end() { return {this, n}; }
    const_iterator begin() const { return {this, 0}; }
    const_iterator end() const { return {this, n}; }

  private:
    int n;
    vector<int> head;
    vector<internal_edge> edges;
};
