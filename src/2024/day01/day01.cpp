/**
 * https://adventofcode.com/2024/day/1
 */
#include <fstream>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

int solve_1(std::vector<std::string> inp) {
    std::vector<int> lst1{};
    std::vector<int> lst2{};

    for (auto& line : inp) {
        int num1{};
        int num2{};
        std::stringstream ss(line);
        ss >> num1 >> num2;
        lst1.push_back(num1);
        lst2.push_back(num2);
    }

    std::sort(lst1.begin(), lst1.end());
    std::sort(lst2.begin(), lst2.end());

    assert(lst1.size() == lst2.size());
    int sum{std::inner_product(lst1.cbegin(), lst1.cend(), lst2.cbegin(), static_cast<int>(0), std::plus<>(),
                               [](auto const& lhs, auto const& rhs) { return std::abs(lhs - rhs); })};

    return sum;
}

int solve_2(std::vector<std::string> inp) {
    std::vector<int> lst1{};
    std::unordered_map<int, int> lst2{};

    for (auto& line : inp) {
        int num1{};
        int num2{};
        std::stringstream ss(line);
        ss >> num1 >> num2;
        lst1.push_back(num1);
        lst2[num2]++;
    }

    return std::accumulate(lst1.cbegin(), lst1.cend(), static_cast<int>(0),
                           [&lst2](auto const sum, auto const val) { return sum + lst2[val] * val; });
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 11);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
