#pragma once

template<class T, bool auto_resize = true> struct ptr32 {
    ptr32() {}
    ptr32(nullptr_t) : ptr32() {}
    template<class... Args> static ptr32 alloc(Args &&...args) {
        ptr32 p;
        if (del.size()) {
            p = del.back(), del.pop_back();
            *p = T(forward<Args>(args)...);
        } else {
            p.p = pool.size();
            pool.emplace_back(forward<Args>(args)...);
        }
        return p;
    }
    void dealloc(ptr32 p) { del.push_back(p); }

    operator bool() { return p; }
    bool operator==(const ptr32 &r) const { return p == r.p; }
    bool operator!=(const ptr32 &r) const { return p != r.p; }

    T &operator*() { return pool[p]; }
    T *operator->() { return &pool[p]; }

    static enable_if_t<!auto_resize> reserve(int n) { pool.reserve(n + 1); }

  private:
    int p = 0;
    using pool_t = conditional_t<auto_resize, deque<T>, vector<T>>;
    static inline pool_t pool = pool_t(1);
    static inline vector<ptr32> del;
};
