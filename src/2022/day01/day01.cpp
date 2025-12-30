/**
 * https://adventofcode.com/2022/day/1
 */
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

static std::vector<int64_t> process_data(std::vector<std::string> const& data) {
    std::vector<int64_t> calories;
    int64_t current_calories = 0;
    for (auto line : data) {
        if (line.empty()) {
            calories.push_back(current_calories);
            current_calories = 0;
            continue;
        }
        current_calories += stoi(line);
    }
    calories.push_back(current_calories);
    std::sort(calories.rbegin(), calories.rend());
    return calories;
}

int solve_1(std::vector<std::string> input) {
    auto sorted_inventory = process_data(input);
    return sorted_inventory.front();
}

int solve_2(std::vector<std::string> input) {
    auto sorted_inventory = process_data(input);
    return std::accumulate(sorted_inventory.begin(), sorted_inventory.begin() + 3, static_cast<int64_t>(0));
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 71780);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 212489);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
