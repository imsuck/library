#pragma once

char BUF[256 << 20]; // 256 MB
size_t BUFP = sizeof(BUF);
void *operator new(size_t s) { return &BUF[BUFP -= s]; }
void operator delete(void *) noexcept {}
void operator delete(void *, size_t) noexcept {}
template<class T> struct bump {
    using value_type = T;
    bump() {}
    template<class U> bump(U, ...) {}
    template<class U> struct rebind {
        using other = bump<U>;
    };
    T *allocate(size_t n) {
        BUFP -= n * sizeof(T);
        BUFP &= 0 - alignof(T);
        return (T *)(BUF + BUFP);
    }
    void deallocate(T *, size_t) {}
};
