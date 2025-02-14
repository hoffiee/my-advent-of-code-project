#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "string_utils.h"

using std::vector;

static int char_to_int(unsigned char ch) {
    int out = 0;
    if (isupper(ch)) {
        out = ch - 'A' + 27;
    } else if (islower(ch)) {
        out = ch - 'a' + 1;
    }
    return out;
}

static int count_and_sum_priorities(std::string input, int occurence) {
    vector<int> character_frequency(26 * 2 + 1, 0);
    for (char item : input) {
        ++character_frequency.at(char_to_int(item));
    }
    auto ind = std::find(character_frequency.begin(), character_frequency.end(), occurence);
    return static_cast<int>(ind - character_frequency.begin());
}

int solve_1(std::vector<std::string> input) {
    int sum_of_priorities = 0;
    for (auto& rucksack : input) {
        auto compartment_1 = rucksack.substr(0, rucksack.size() / 2);
        auto compartment_2 = rucksack.substr(rucksack.size() / 2, rucksack.size() / 2);
        std::sort(compartment_1.begin(), compartment_1.end());
        std::sort(compartment_2.begin(), compartment_2.end());
        {
            auto last = std::unique(compartment_1.begin(), compartment_1.end());
            compartment_1.erase(last, compartment_1.end());
        }
        {
            auto last = std::unique(compartment_2.begin(), compartment_2.end());
            compartment_2.erase(last, compartment_2.end());
        }
        auto rucksack_unique_items = compartment_1 + compartment_2;
        sum_of_priorities += count_and_sum_priorities(rucksack_unique_items, 2);
    }
    return sum_of_priorities;
}

int solve_2(std::vector<std::string> input) {
    int sum_of_priorities = 0;
    for (size_t i = 0; i < input.size() / 3; ++i) {
        std::string combined_unique_rucksacks = "";
        for (size_t ii = 0; ii < 3; ++ii) {
            auto rucksack = input.at(3 * i + ii);
            std::sort(rucksack.begin(), rucksack.end());
            {
                auto last = std::unique(rucksack.begin(), rucksack.end());
                rucksack.erase(last, rucksack.end());
            }
            combined_unique_rucksacks += rucksack;
        }
        sum_of_priorities += count_and_sum_priorities(combined_unique_rucksacks, 3);
    }
    return sum_of_priorities;
}

void samples() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 157);
    assert(solve_2(sample) == 70);
}

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
