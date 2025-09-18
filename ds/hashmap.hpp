#pragma once

template<class K, class V, class Hash> struct hash_map_base {
    using u32 = uint32_t;
    using u64 = uint64_t;
    using node = pair<K, V>;

    u32 sz = 0, cap = 8, mask = cap - 1, load = 75;
    vector<node> data;
    vector<bool> used;
    V def_val{};

    hash_map_base() : data(cap), used(cap) {}

    void reserve(int n) { extend(100 * n / load); }
    int size() const { return sz; }
    bool empty() const { return sz == 0; }
    void set_default(V v) { def_val = v; }
    void set_load_factor(u32 nload) { load = nload; }

    V &operator[](const K &k) { return *emplace(k, def_val); }
    V *emplace(const K &k, const V &v) {
        u32 hash = chash(k);
        for (;;) {
            if (!used[hash]) {
                if (100 * sz >= load * cap) {
                    extend(cap + 1);
                    return emplace(k, v);
                }
                sz++;
                data[hash] = {k, v};
                used[hash] = true;
                return &data[hash].second;
            }
            if (data[hash].first == k) return &data[hash].second;
            ++hash &= mask;
        }
    }
    void erase(const K &k) {
        u32 hash = chash(k);
        for (;;) {
            if (!used[hash]) return;
            if (data[hash].first == k) {
                sz--;
                used[hash] = false;
                ++hash &= mask;
                for (; used[hash]; ++hash &= mask) {
                    auto [tmp_k, tmp_v] = data[hash];
                    sz--;
                    used[hash] = false;
                    emplace(tmp_k, tmp_v);
                }
                return;
            }
            ++hash &= mask;
        }
    }
    V *find(const K &k) {
        u32 hash = chash(k);
        for (;;) {
            if (!used[hash]) return nullptr;
            if (data[hash].first == k) return &data[hash].second;
            ++hash &= mask;
        }
    }

  private:
    void extend(int _n) {
        while (cap < _n) cap *= 2;
        mask = cap - 1;
        vector<node> d(cap);
        vector<bool> u(cap);
        for (int i = 0; i < used.size(); i++) {
            if (used[i]) {
                u32 hash = chash(data[i].first);
                while (u[hash]) ++hash &= mask;
                d[hash] = data[i];
                u[hash] = true;
            }
        }
        data.swap(d), used.swap(u);
    }
    u32 chash(const K &k) {
        static const u64 a = mt19937_64((u64)make_unique<char>().get())() | 1;
        return u32(a * Hash{}(k) >> 32) & mask;
    }
};
template<class K, class V, class Hash = hash<K>>
struct hash_map : hash_map_base<K, V, Hash> {
    using base = hash_map_base<K, V, Hash>;
    struct iter {
        hash_map &hm;
        int p;
        iter(hash_map &_hm, int _p) : hm(_hm), p(_p) {
            while (p < hm.cap && !hm.used[p]) p++;
        }
        bool operator!=(const iter &o) const { return p != o.p; }
        void operator++() {
            p++;
            while (p < hm.cap && !hm.used[p]) p++;
        }
        pair<K, V> &operator*() { return hm.data[p]; }
    };
    iter begin() { return {*this, 0}; }
    iter end() { return {*this, (int)base::cap}; }
};
struct _null_type {};
template<class K, class Hash = hash<K>>
struct hash_set : hash_map_base<K, _null_type, Hash> {
    using base = hash_map_base<K, _null_type, Hash>;
    struct iter {
        hash_set &hs;
        int p;
        iter(hash_set &_mp, int _p) : hs(_mp), p(_p) {
            while (p < hs.cap && !hs.used[p]) p++;
        }
        bool operator!=(const iter &o) const { return p != o.p; }
        void operator++() {
            p++;
            while (p < hs.cap && !hs.used[p]) p++;
        }
        const K &operator*() { return hs.data[p].first; }
    };
    iter begin() { return {*this, 0}; }
    iter end() { return {*this, (int)base::cap}; }
    void insert(const K &k) { base::emplace(k, {}); }
    template<class... Ts> void emplace(Ts &&...x) {
        base::emplace({forward<Ts>(x)...}, {});
    }
};
