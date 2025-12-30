#include <cassert>
#include <iostream>

#include "aoc_runner.h"
#include "aoc_utils.h"

#include AOC_HEADER

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [res, _] = solve(inp);
        std::cout << "part 1: " << res << std::endl;
        assert(res == 1444896);
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [_, res] = solve(inp);
        std::cout << "part 2: " << res << std::endl;
        assert(res == 404395);
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
