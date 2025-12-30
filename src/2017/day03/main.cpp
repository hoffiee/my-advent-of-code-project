#include <cassert>
#include <iostream>

#include "aoc_runner.h"
#include "aoc_utils.h"

#include AOC_HEADER

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const&) -> void {
        auto [res, _] = solve(265149);
        assert(res == 438);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const&) -> void {
        auto [_, res] = solve(265149);
        assert(res == 266330);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, {});
}
