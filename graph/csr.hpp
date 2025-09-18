#pragma once

template<class E> struct CSR {
    CSR() {}
    CSR(int _n, const vector<pair<int, E>> &_edges) :
        n(_n), start(n + 1), edges((int)_edges.size()) {
        for (auto &[from, _] : _edges) start[from + 1]++;
        for (int i = 1; i <= n; i++) start[i] += start[i - 1];
        auto cnt = start;
        for (auto &[from, e] : _edges) edges[cnt[from]++] = e;
    }

    int size() const { return n; }

    struct range {
        E *edges;
        const int first, last;
        struct iterator {
            E *elist;
            int p;
            bool operator!=(const iterator &r) const { return p != r.p; }
            void operator++() { p++; }
            E &operator*() { return elist[p]; }
        };
        E &operator[](size_t i) {
            assert(i < size());
            return edges[first + i];
        }
        E &back() { return edges[last - 1]; }
        iterator begin() { return {edges, first}; }
        iterator end() { return {edges, last}; }
        int size() const { return last - first; }
        bool empty() const { return first == last; }
    };
    struct const_range {
        const E *edges;
        const int first, last;
        struct iterator {
            const E *elist;
            int p;
            bool operator!=(const iterator &r) const { return p != r.p; }
            void operator++() { p++; }
            const E &operator*() const { return elist[p]; }
        };
        const E &operator[](size_t i) const {
            assert(i < size());
            return edges[first + i];
        }
        const E &back() const { return edges[last - 1]; }
        iterator begin() const { return {edges, first}; }
        iterator end() const { return {edges, last}; }
        int size() const { return last - first; }
        bool empty() const { return first == last; }
    };
    range operator[](size_t i) {
        assert(i < size());
        return {edges.data(), start[i], start[i + 1]};
    }
    const_range operator[](size_t i) const {
        assert(i < size());
        return {edges.data(), start[i], start[i + 1]};
    }

    struct iterator {
        CSR *g;
        int p;
        bool operator!=(const iterator &r) const { return p != r.p; }
        void operator++() { p++; }
        range operator*() { return (*g)[p]; }
    };
    struct const_iterator {
        const CSR *g;
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
    vector<int> start;
    vector<E> edges;
};
