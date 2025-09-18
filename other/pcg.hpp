#pragma once

struct pcg64 {
    using result_type = uint64_t;

    uint64_t state, inc;

    pcg64(
        uint64_t seed = 0x435577abff26f952,
        uint64_t _inc = 0x2068f28194a9ae8b
    ) : inc(_inc) {
        seed_rng(seed);
    }
    pcg64(seed_seq &sseq) {
        uint64_t a[4];
        sseq.generate(a, a + 4);
        inc = a[0] << 32 | a[1] | 1;
        seed_rng(a[2] << 32 | a[3]);
    }

    void seed_rng(uint64_t s) { state = s + inc, (void)(*this)(); }
    uint64_t operator()() {
        uint64_t x = state;
        state = x * 0x4afbfcc9230ed3f9 + (inc | 1);
        x ^= x >> ((x >> 59) + 5);
        x *= 0x4e42a2ff4fd72915;
        return x ^ x >> 43;
    }

    static constexpr uint64_t min() { return 0; }
    static constexpr uint64_t max() { return -1; }
};
