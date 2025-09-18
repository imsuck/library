#pragma once

namespace timer {
    using namespace chrono;
    static auto last = steady_clock::now();
    map<string, uint64_t> comp;
    template<bool final = false>
    void add([[maybe_unused]] string const &msg = "") {
#ifdef LOCAL
        auto now = steady_clock::now();
        auto delta = duration_cast<microseconds>(now - last).count();
        last = now;
        if (msg.size() && !final) comp[msg] += delta;

        if (final)
            for (auto &[k, v] : comp) cerr << k << ": " << v * 1e-3L << " ms\n";
#endif
    }
} // namespace timer
