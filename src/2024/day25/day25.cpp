/**
 * https://adventofcode.com/2024/day/25
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "string_utils.h"

int64_t solve_1(std::vector<std::string> inp) {
    std::vector<std::vector<int64_t>> keys{};
    std::vector<std::vector<int64_t>> locks{};
    for (size_t row{0}; row <= inp.size() / 8; row++) {
        auto line = inp.at(row * 8);
        assert(line.size() == 5);
        if (line == "#####") {
            std::vector<int64_t> lock{};
            for (size_t col{0}; col < 5; col++) {
                int64_t count{0};
                for (; count < 6; count++) {
                    if (inp.at(8 * row + count + 1).at(col) == '.') {
                        break;
                    }
                }
                lock.push_back(count);
            }
            locks.push_back(lock);
        } else if (line == ".....") {
            std::vector<int64_t> key{};
            for (size_t col{0}; col < 5; col++) {
                int64_t count{0};
                for (; count < 7; ++count) {
                    if (inp.at(8 * row + count).at(col) != '.') {
                        break;
                    }
                }
                key.push_back(6 - count);
            }
            keys.push_back(key);
        } else {
            assert(false);
        }
    }

    int64_t sum{0};
    for (auto const& lock : locks) {
        for (auto const& key : keys) {
            assert(key.size() == 5);
            assert(lock.size() == 5);
            // assume ok, remove if not
            sum++;
            for (size_t i{0}; i < 5; i++) {
                if (key[i] + lock[i] > 5) {
                    sum--;
                    break;
                }
            }
        }
    }
    return sum;
}

int main() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 3);

    auto input = string_utils::read_input(AOC_INPUT);
    auto part1 = solve_1(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;

    return 0;
}
