#ifndef LOCAL
    #define dbg(...) void()
    #define debug() if (false)
#else
namespace dbg::options {
    int _ = []() {
        fixed_float = false;
        float_precision = 6;
        trivial_string = true;
        max_container_elements = -1;
        return 0;
    }();
} // namespace dbg::options
#endif
