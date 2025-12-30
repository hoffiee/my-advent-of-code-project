#include <icecream.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

#include AOC_HEADER

int main(int argc, char** argv) {
    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_1(178416, 676461);
        assert(res == 1650);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_2(178416, 676461);
        assert(res == 1129);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, {});
}
