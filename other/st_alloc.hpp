#pragma once

template<class T> struct st_alloc {
    static inline stack<T> pool;
    void *operator new(size_t) { return pool.emplace(), &pool.top(); }
    void operator delete(void *) {}
};
