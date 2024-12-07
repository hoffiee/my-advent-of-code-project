/**
 * https://adventofcode.com/2024/day/2
 */
#include <cmath>
#include <fstream>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "string_utils.h"

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
        auto vec = string_utils::numbers_from_string(line);
        if (safe_level(vec)) {
            count++;
        }
    }
    return count;
}

int solve_2(std::vector<std::string> inp) {
    int count{0};
    for (auto const& line : inp) {
        auto vec = string_utils::numbers_from_string(line);
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

int main() {
    std::ifstream input_file;
    // input_file.open(AOC_SAMPLE_INPUT);
    input_file.open(AOC_INPUT);
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::vector<std::string> input;
    std::string line;
    while (getline(input_file, line)) {
        input.push_back(line);
    }

    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
