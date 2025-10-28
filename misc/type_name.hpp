#pragma once

// Not particularly useful but nice to have around

template<typename T> constexpr auto func_name() { return __PRETTY_FUNCTION__; }
template<typename T> constexpr string _type_of_impl() {
    constexpr string_view fn_name = func_name<T>();
    return string{fn_name.begin() + 37, fn_name.end() - 1};
}
template<typename T> constexpr auto type_of(T &&x) {
    return _type_of_impl<decltype(x)>();
}
template<typename T> constexpr auto type_of() { return _type_of_impl<T>(); }
