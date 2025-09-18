#pragma once

// Silly std::vector wrapper I wrote for fun
template<class T> struct Vec {
    Vec() = default;
    Vec(int n) : v(n) {}
    Vec(int n, const T &a) : v(n, a) {}
    Vec(const vector<T> &a) : v(a) {}
    Vec(initializer_list<T> il) : v(il.size()) {
        copy(il.begin(), il.end(), v.begin());
    }

    template<class F, class U = result_of_t<F(T)>> Vec<U> map(F &&f) const {
        vector<U> a;
        a.reserve(v.size());
        for (int i = 0; i < size(); i++) a.push_back(f(move(v[i])));
        return Vec<U>(move(a));
    }
    template<class U, enable_if_t<is_convertible<T, U>::value, int> = 1>
    Vec<U> map() const {
        vector<U> a;
        a.reserve(v.size());
        for (int i = 0; i < size(); i++) a.push_back(U(move(v[i])));
        return Vec<U>(move(a));
    }
    template<class F> Vec<T> filter(F &&f) {
        vector<T> a;
        for (int i = 0; i < size(); i++)
            if (f(v[i])) a.push_back(move(v[i]));
        return v.swap(a), move(*this);
    }
    template<class F> Vec<T> for_each(F &&f) {
        for (int i = 0; i < size(); i++) f(v[i]);
        return move(*this);
    }
    Vec<T> rev() {
        reverse(v.begin(), v.end());
        return move(*this);
    }
    Vec<T> sort() {
        std::sort(v.begin(), v.end());
        return move(*this);
    }
    template<class F> Vec<T> sort(F &&f) {
        std::sort(v.begin(), v.end(), f);
        return move(*this);
    }
    template<class F> Vec<T> inspect(F &&f) const {
        for (int i = 0; i < size(); i++) f(v[i]);
        return move(*this);
    }

    void resize(int n) { v.resize(n); }
    void reserve(int n) { v.reserve(n); }
    void push_back(T &a) { v.push_back(a); }
    void push_back(T &&a) { v.push_back(a); }
    template<class... Args> void emplace_back(Args &&...args) {
        v.emplace_back(forward<Args>(args)...);
    }

    vector<T> &operator*() { return v; }
    const vector<T> &operator*() const { return v; }
    T &operator[](int i) { return v[i]; }
    const T &operator[](int i) const { return v[i]; }
    auto begin() { return v.begin(); }
    auto end() { return v.end(); }
    int size() const { return (int)v.size(); }

  private:
    vector<T> v;
};
