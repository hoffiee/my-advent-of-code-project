#include <cassert>
#include <iostream>

#include "aoc_runner.h"
#include "aoc_utils.h"

#include AOC_HEADER

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input("day04.preprocessed.input");

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_1(inp);
        assert(res == 67558);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_2(inp);
        assert(res == 78990);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
