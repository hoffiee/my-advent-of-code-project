#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using std::string;

static int64_t solve(string message, size_t offset) {
    std::unordered_map<char, int64_t> freq;
    size_t i = 0;
    for (; i < message.length(); ++i) {
        ++freq[message.at(i)];
        if (i >= offset) {
            --freq[message.at(i - offset)];
            if (freq[message.at(i - offset)] == 0) {
                freq.erase(message.at(i - offset));
            }
        }
        if (freq.size() == offset) {
            break;
        }
    }
    return static_cast<int64_t>(i + 1);
}

void samples() {
    // auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    // auto [tmp1, tmp2] = read_and_parse_data(sample);
    // assert(solve_1(tmp1, tmp2) == "CMZ");
    // assert(solve_2(tmp1, tmp2) == "MCD");
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve(inp.front(), 4);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve(inp.front(), 14);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
