/**
 * https://adventofcode.com/2024/day/3
 */
#include <fstream>
#include <icecream.hpp>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

int solve_1(std::vector<std::string> inp) {
    int sum{0};
    for (auto const& line : inp) {
        std::regex r("mul\\(\\d+,\\d+\\)");
        std::smatch match{};
        for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r); i != std::sregex_iterator();
             i++) {
            std::smatch match = *i;
            int a{0};
            int b{0};
            std::sscanf(match[0].str().c_str(), "mul(%d,%d)", &a, &b);
            sum += a * b;
        }
    }
    return sum;
}

int solve_2(std::vector<std::string> inp) {
    int sum{0};
    bool enable{true};
    for (auto const& line : inp) {
        std::regex r("(mul\\(\\d+,\\d+\\))|(don't\\(\\))|(do\\(\\))");
        std::smatch match{};
        for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r); i != std::sregex_iterator();
             i++) {
            std::smatch match = *i;

            if (match[2].length() > 0) {
                enable = false;
            }
            if (match[3].length() > 0) {
                enable = true;
            }
            if (enable && match[1].length()) {
                int a{0};
                int b{0};
                std::sscanf(match[1].str().c_str(), "mul(%d,%d)", &a, &b);
                sum += a * b;
            }
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
