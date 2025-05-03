#include <fstream>
#include <icecream.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include AOC_HEADER

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto inst = string_utils::numbers_from_string(inp[0]);
        inst.at(1) = 12;
        inst.at(2) = 2;
        auto part1 = solve_1(inst);
        IC(part1);
        assert(part1 == 3516593);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto inst = string_utils::numbers_from_string(inp[0]);
        auto part2 = solve_2(inst);
        assert(part2 == 7749);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(
        argc, argv, []() { return true; }, solve_1_wrapper, solve_2_wrapper, input);
}
