/**
 * https://adventofcode.com/2024/day/7
 */

#include <omp.h>

#include <cmath>
#include <complex>
#include <fstream>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "string_utils.h"

int64_t op3(int64_t lhs, int64_t rhs) {
    return lhs * std::pow(10, static_cast<int64_t>(std::ceil(std::log10(rhs + 1)))) + rhs;
}

bool test_sequence(int64_t results, int64_t acc, std::vector<int64_t> numbers, bool third = false) {
    if (acc > results) {
        return false;
    }

    if (numbers.size() == 0) {
        return results == acc;
    }

    int64_t num{numbers[0]};
    numbers.erase(numbers.begin());

    return test_sequence(results, acc + num, numbers, third) || test_sequence(results, acc * num, numbers, third) ||
           (third && test_sequence(results, op3(acc, num), numbers, third));
}

int64_t solver(std::vector<std::string>& inp, bool third = false) {
    int64_t sum{0};
#pragma omp parallel for reduction(+ : sum)
    for (auto& line : inp) {
        auto numbers = string_utils::numbers_from_string(line);
        int64_t results{numbers[0]};
        numbers.erase(numbers.begin());
        if (test_sequence(results, 0, numbers, third)) {
            sum += results;
        }
    }
    return sum;
}

int main() {
    auto input = string_utils::read_input(AOC_INPUT);
    auto part1 = solver(input);
    auto part2 = solver(input, true);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
