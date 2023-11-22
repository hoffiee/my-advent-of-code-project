#include AOC_HEADER

#include <cmath>
#include <cstdint>

static uint64_t highest_bit(const uint64_t n) { return 1 << (uint64_t)log2((double)n); }

static uint64_t part1(uint64_t n) { return (n ^ highest_bit(n)) << 1 | 1; }

std::tuple<uint64_t, uint64_t> solve(uint64_t n) { return {part1(n), 0}; }
