#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "string_utils.h"

#include AOC_HEADER

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [part1, _] = solve(inp.front());
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [_, part2] = solve(inp.front());
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
