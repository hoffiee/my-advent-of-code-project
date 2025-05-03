/**
 * https://adventofcode.com/2015/day/10
 *
 * https://www.youtube.com/watch?v=ea7lJkEhytA
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

int64_t solve(std::vector<std::string> const& inp, int64_t steps) {
    std::string current{inp[0]};
    for (int64_t step{0}; step < steps; step++) {
        char current_digit{current.front()};
        int64_t count{0};
        std::string next{};
        for (size_t i{0}; i < current.size(); i++) {
            if (current[i] == current_digit) {
                count++;
                continue;
            }
            next += std::to_string(count) + current_digit;
            current_digit = current[i];
            count = 1;
        }
        if (count > 0) {
            next += std::to_string(count) + current_digit;
        }
        current = next;
    }
    return current.size();
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve(sample, 1) == 2);
    assert(solve(sample, 5) == 6);

    auto sample1 = aoc::utils::read_input("day10-sample-1.input");
    assert(solve(sample1, 1) == 2);

    auto sample2 = aoc::utils::read_input("day10-sample-2.input");
    assert(solve(sample2, 1) == 4);

    auto sample3 = aoc::utils::read_input("day10-sample-3.input");
    assert(solve(sample3, 1) == 6);

    auto sample4 = aoc::utils::read_input("day10-sample-4.input");
    assert(solve(sample4, 1) == 6);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve(inp, 40);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve(inp, 50);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
