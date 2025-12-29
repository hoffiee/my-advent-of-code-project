#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using std::string;
using std::vector;

static std::pair<std::vector<int>, std::vector<int>> read_and_parse_data(std::vector<std::string> const& input) {
    std::vector<int> player_1{};
    std::vector<int> player_2{};
    for (auto line : input) {
        player_1.push_back(static_cast<int>(line.front() - 'A' + 1));
        player_2.push_back(static_cast<int>(line.back() - 'X' + 1));
    }

    return {player_1, player_2};
}

int solve_1(std::vector<std::string> const& input) {
    auto [player_1, player_2] = read_and_parse_data(input);

    int score = 0;
    for (size_t i = 0; i < player_1.size(); ++i) {
        if (player_1.at(i) == 1) {
            score += 3 * ((player_2.at(i) == 1) + 2 * (player_2.at(i) == 2));
        } else if (player_1.at(i) == 2) {
            score += 3 * ((player_2.at(i) == 2) + 2 * (player_2.at(i) == 3));
        } else if (player_1.at(i) == 3) {
            score += 3 * ((player_2.at(i) == 3) + 2 * (player_2.at(i) == 1));
        }
    }
    return score + std::accumulate(player_2.begin(), player_2.end(), 0);
}

int solve_2(std::vector<std::string> const& input) {
    auto [player_1, player_2] = read_and_parse_data(input);

    int score = 0;
    for (size_t i = 0; i < player_1.size(); ++i) {
        int elf_play = player_1.at(i);

        if (player_2.at(i) == 1) {
            score += 1 * (elf_play == 2) + 2 * (elf_play == 3) + 3 * (elf_play == 1);
        } else if (player_2.at(i) == 2) {
            score += 3;
            score += 1 * (elf_play == 1) + 2 * (elf_play == 2) + 3 * (elf_play == 3);
        } else if (player_2.at(i) == 3) {
            score += 6;
            score += 1 * (elf_play == 3) + 2 * (elf_play == 1) + 3 * (elf_play == 2);
        }
    }
    return score;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 15);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 10595);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 9541);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
