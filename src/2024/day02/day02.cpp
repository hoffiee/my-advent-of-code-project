/**
 * https://adventofcode.com/2024/day/2
 */
#include <cmath>
#include <fstream>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

bool safe_level(std::vector<int64_t> vec) {
    bool safe_level{true};
    int64_t sign = vec[1] - vec[0];
    for (int i = 0; i < static_cast<int>(vec.size()) - 1 && safe_level; i++) {
        int64_t diff = vec[i + 1] - vec[i];
        if ((diff < -3) || (diff == 0) || (3 < diff)) {
            safe_level = false;
        }
        if (std::signbit(sign) != std::signbit(diff)) {
            safe_level = false;
        }
    }
    return safe_level;
}

int solve_1(std::vector<std::string> inp) {
    int count{0};
    for (auto const& line : inp) {
        auto vec = aoc::string::numbers_from_string(line);
        if (safe_level(vec)) {
            count++;
        }
    }
    return count;
}

int solve_2(std::vector<std::string> inp) {
    int count{0};
    for (auto const& line : inp) {
        auto vec = aoc::string::numbers_from_string(line);
        if (safe_level(vec)) {
            count++;
            continue;
        }

        bool safe{false};
        for (int rem = 0; rem < static_cast<int>(vec.size()); rem++) {
            auto reduced{vec};
            reduced.erase(reduced.begin() + rem);
            if (safe_level(reduced)) {
                safe = true;
                break;
            }
        }
        if (safe) {
            count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 218);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 290);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
