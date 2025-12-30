/**
 * https://adventofcode.com/2015/day/8
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

int64_t solve_1(std::vector<std::string> const& inp) {
    int64_t sum{0};
    for (auto const& word : inp) {
        assert(word.front() == '"');
        assert(word.back() == '"');

        sum += word.size();
        std::string decoded{};
        int64_t len{0};
        for (size_t i{1}; i < word.size() - 1; i++) {
            if (word[i] != '\\') {
                decoded += word[i];
                len++;
            } else if (word.substr(i, 2) == "\\\"") {
                decoded += '"';
                i++;
                len++;
            } else if (word.substr(i, 2) == "\\\\") {
                decoded += '"';
                i++;
                len++;
            } else if (word.substr(i, 2) == "\\x") {
                int ch{std::stoi(word.substr(i + 2, 2), nullptr, 16)};
                decoded += static_cast<char>(ch);
                i += 3;
                len++;
            } else {
                assert(false);
            }
        }
        assert(len == static_cast<int64_t>(decoded.size()));
        sum -= decoded.size();
    }
    return sum;
}

int64_t solve_2(std::vector<std::string> const& inp) {
    int64_t sum{0};
    for (auto const& word : inp) {
        sum -= word.size();
        std::string encoded{"\""};
        for (auto ch : word) {
            switch (ch) {
                case '"':
                    encoded += "\\\"";
                    break;
                case '\\':
                    encoded += "\\\\";
                    break;
                default:
                    encoded += ch;
                    break;
            }
        }
        encoded += "\"";
        sum += encoded.size();
    }
    return sum;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 12);
    assert(solve_2(sample) == 19);

    auto sample1 = aoc::utils::read_input("day08-sample-1.input");
    assert(solve_1(sample1) == 3 - 1 + 6 - 2 + 8 - 2);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_1(inp);
        assert(res == 1333);
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_2(inp);
        assert(res == 2046);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
