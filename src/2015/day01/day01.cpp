#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "aoc_runner.h"
#include "aoc_utils.h"

static std::pair<int, int> solve(std::string input) {
    int floor = 0;
    int position = -1;

    for (size_t i = 0; i < input.size(); ++i) {
        floor += (input.at(i) == '(') ? +1 : -1;

        if (floor < 0 && position == -1) {
            position = static_cast<int>(i + 1);
        }
    }
    return {floor, position};
}

static void test() {
    assert(solve("(())").first == 0);
    assert(solve("(((").first == 3);
    assert(solve("(()(()(").first == 3);
    assert(solve("))(((((").first == 3);
    assert(solve("())").first == -1);
    assert(solve("))(").first == -1);
    assert(solve(")))").first == -3);
    assert(solve(")())())").first == -3);
    {
        auto [floor, position] = solve(")");
        assert(floor == -1);
        assert(position == 1);
    }
    {
        auto [floor, position] = solve("()())");
        assert(floor == -1);
        assert(position == 5);
    }
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [part1, _] = solve(inp.front());
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [_, part2] = solve(inp.front());
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, test, solve_1_wrapper, solve_2_wrapper, input);
}
