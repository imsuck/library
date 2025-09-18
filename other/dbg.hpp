#ifndef LOCAL
    #define dbg(...) void()
    #define debug() if (false)
#else
namespace dbg::options {
    template<> constexpr bool trivial_string() { return true; }
} // namespace dbg::options
#endif
