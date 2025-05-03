/**
 * https://adventofcode.com/2015/day/12
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

int64_t solve_1(std::vector<std::string> const& inp) {
    auto numbers = string_utils::numbers_from_string(inp[0]);
    return std::accumulate(numbers.cbegin(), numbers.cend(), static_cast<int64_t>(0));
}

int64_t solve_2(std::vector<std::string> const& inp_) {
    // Moved over to python for this one.
    return 0;
}

void samples() {}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp);
        assert(part2 > 43050);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
