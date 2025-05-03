#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

std::vector<std::tuple<int, int, int, int>> read_and_parse_data(std::vector<std::string> const& input) {
    std::vector<std::tuple<int, int, int, int>> pairs;
    for (auto const& line : input) {
        int elf_1_start, elf_1_end;
        int elf_2_start, elf_2_end;
        sscanf(line.c_str(), "%d-%d,%d-%d", &elf_1_start, &elf_1_end, &elf_2_start, &elf_2_end);
        pairs.emplace_back(std::make_tuple(elf_1_start, elf_1_end, elf_2_start, elf_2_end));
    }
    return pairs;
}

int solve_1(std::vector<std::tuple<int, int, int, int>> input) {
    int count = 0;
    for (auto& it : input) {
        auto [a, b, c, d] = it;
        if ((a <= c && d <= b) || (c <= a && b <= d)) {
            ++count;
        }
    }
    return count;
}

int solve_2(std::vector<std::tuple<int, int, int, int>> input) {
    int count = 0;
    for (auto& it : input) {
        auto [a, b, c, d] = it;
        if (!((b < c) || (d < a))) {
            ++count;
        }
    }
    return count;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    auto tmp = read_and_parse_data(sample);
    assert(solve_1(tmp) == 2);
    assert(solve_2(tmp) == 4);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto tmp = read_and_parse_data(inp);
        auto part1 = solve_1(tmp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto tmp = read_and_parse_data(inp);
        auto part2 = solve_2(tmp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
