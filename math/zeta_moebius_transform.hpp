#pragma once

template<class T> void multiple_fzt(vector<T> &a) {
    const int n = (int)a.size();
    vector<char> sieve(n, true);
    for (int p = 2; p < n; p += 1 + p % 2) {
        if (!sieve[p]) continue;
        for (int k = (n - 1) / p; k > 0; k--) {
            sieve[k * p] = false;
            a[k] += a[k * p];
        }
    }
}
template<class T> void multiple_fmt(vector<T> &a) {
    const int n = (int)a.size();
    vector<char> sieve(n, true);
    for (int p = 2; p < n; p += 1 + p % 2) {
        if (!sieve[p]) continue;
        for (int k = 1; k * p < n; k++) {
            sieve[k * p] = false;
            a[k] -= a[k * p];
        }
    }
}
template<class T> void divisor_fzt(vector<T> &a) {
    const int n = (int)a.size();
    vector<char> sieve(n, true);
    for (int p = 2; p < n; p += 1 + p % 2) {
        if (!sieve[p]) continue;
        for (int k = 1; k * p < n; k++) {
            sieve[k * p] = false;
            a[k * p] += a[k];
        }
    }
}
template<class T> void divisor_fmt(vector<T> &a) {
    const int n = (int)a.size();
    vector<char> sieve(n, true);
    for (int p = 2; p < n; p += 1 + p % 2) {
        if (!sieve[p]) continue;
        for (int k = (n - 1) / p; k > 0; k--) {
            sieve[k * p] = false;
            a[k * p] -= a[k];
        }
    }
}

template<class T> vector<T> gcd_convolution(vector<T> a, vector<T> b) {
    assert(a.size() == b.size());
    multiple_fzt(a), multiple_fzt(b);
    for (int i = 0; i < a.size(); i++) a[i] *= b[i];
    multiple_fmt(a);
    return a;
}
template<class T> vector<T> lcm_convolution(vector<T> a, vector<T> b) {
    assert(a.size() == b.size());
    divisor_fzt(a), divisor_fzt(b);
    for (int i = 0; i < a.size(); i++) a[i] *= b[i];
    divisor_fmt(a);
    return a;
}
