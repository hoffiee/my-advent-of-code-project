/**
 * https://adventofcode.com/2023/day/12
 */
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d12 {

std::unordered_map<std::string, int64_t> cache{};

std::string cache_key(std::string rec, std::vector<size_t> const& cfg) {
    for (auto const size : cfg) {
        rec += ",";
        rec += std::to_string(size);
    }
    return rec;
}

int64_t count_arrangements(std::string const rec, std::vector<size_t> const& cfg, int d = 0) {
    if (rec.empty()) {
        return cfg.empty() ? 1 : 0;
    }

    if (cfg.empty()) {
        return (rec.find('#') != std::string::npos) ? 0 : 1;
    }

    auto const key = cache_key(rec, cfg);
    if (cache.contains(key)) {
        return cache.at(key);
    }

    int64_t count{0};
    bool const starts_with_period{rec.at(0) == '.'};
    bool const starts_with_questionmark{rec.at(0) == '?'};
    bool const starts_with_pound{rec.at(0) == '#'};

    // we have or we guess .
    if (starts_with_period || starts_with_questionmark) {
        count += count_arrangements(std::string(rec.cbegin() + 1u, rec.cend()), cfg, d + 1);
    }

    // we have or we guess #
    if (starts_with_pound || starts_with_questionmark) {
        bool const next_arrangement_fits{cfg.at(0) < rec.size()};
        if (next_arrangement_fits) {
            std::string const tmp{rec.cbegin(), rec.cbegin() + cfg.at(0)};
            bool const no_period{tmp.find('.') == std::string::npos};
            bool const next_not_pound{rec.at(cfg.at(0)) != '#'};
            if (no_period && next_not_pound) {
                auto const new_cfg = std::vector<size_t>{cfg.cbegin() + 1u, cfg.cend()};
                auto const new_rec = std::string(rec.cbegin() + cfg.at(0) + 1u, rec.cend());
                count += count_arrangements(new_rec, new_cfg, d + 1);
            }
        }

        bool const next_arrangement_equal_size{cfg.at(0) == rec.size()};
        if (next_arrangement_equal_size && cfg.size() == 1u) {
            bool const no_period{rec.find('.') == std::string::npos};
            if (no_period) {
                count += 1;
            }
        }
    }

    cache[key] = count;
    return count;
}

int64_t solve_1(std::vector<std::string> inp) {
    int64_t count{0};
    for (auto const& line : inp) {
        auto tmp = aoc::string::split(line, ' ');
        auto rec = tmp[0];
        std::vector<size_t> cfg = aoc::string::unumbers_from_string(tmp[1]);
        count += count_arrangements(rec, cfg);
    }
    return count;
}

int64_t solve_2(std::vector<std::string> inp) {
    std::vector<std::string> extended{};
    for (auto const& line : inp) {
        auto tmp = aoc::string::split(line, ' ');

        std::string expanded{tmp[0]};
        for (size_t i{0}; i < 4; i++) {
            expanded += "?" + tmp[0];
        }
        expanded += " " + tmp[1];
        for (size_t i{0}; i < 4; i++) {
            expanded += "," + tmp[1];
        }
        extended.push_back(expanded);
    }
    return solve_1(extended);
}

void samples() {
    assert(count_arrangements("", {}) == 1);
    assert(count_arrangements("", {1}) == 0);
    assert(count_arrangements(".", {}) == 1);
    assert(count_arrangements("?", {}) == 1);
    assert(count_arrangements("#", {}) == 0);
    assert(count_arrangements("...", {}) == 1);
    assert(count_arrangements("...", {1}) == 0);

    assert(count_arrangements("#", {1}) == 1);
    assert(count_arrangements("###", {3}) == 1);
    assert(count_arrangements("###", {3, 1}) == 0);
    assert(count_arrangements(".###", {
                                          3,
                                      }) == 1);
    assert(count_arrangements(".###", {3, 1}) == 0);
    assert(count_arrangements(".###.", {3, 1}) == 0);
    assert(count_arrangements(".##..", {2}) == 1);

    assert(count_arrangements(".?", {1}) == 1);
    assert(count_arrangements("?.", {1}) == 1);
    assert(count_arrangements("??", {1}) == 2);
    assert(count_arrangements("???", {2}) == 2);
    assert(count_arrangements("???", {3}) == 1);

    assert(count_arrangements("?###?", {3}) == 1);
    assert(count_arrangements("?###?", {3, 1}) == 0);

    assert(count_arrangements("???.###", {1, 1, 3}) == 1);
    assert(count_arrangements(".??..??...?##.", {1, 1, 3}) == 4);
    assert(count_arrangements("????.#...#...", {4, 1, 1}) == 1);
    assert(count_arrangements("????.######..#####.", {1, 6, 5}) == 4);
    assert(count_arrangements("?###????????", {3, 2, 1}) == 10);
    assert(count_arrangements("?#?#?#?#?#?#?#?", {1, 3, 1, 6}) == 1);

    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 21);
    assert(solve_2(sample) == 525152);
}

};  // namespace aoc::y2023::d12

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2023::d12::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2023::d12::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2023::d12::samples, solve_1_wrapper, solve_2_wrapper, input);
}
