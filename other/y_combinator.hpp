#pragma once

template<class F> struct y_comb_t : F {
    template<class T> y_comb_t(T &&_f) : F(forward<T>(_f)) {}
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return F::operator()(/* ref */(*this), forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }
