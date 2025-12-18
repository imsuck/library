#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (false)
    #define DBG_FORMAT_STRUCT(...)
    #define DBG_PRETTY_STRUCT(...)
#else
namespace dbg::options {
    int _ = []() {
        fixed_float = true;
        float_precision = 6;
        trivial_string = true;
        max_container_elements = -1;
        return 0;
    }();
} // namespace dbg::options
#endif
