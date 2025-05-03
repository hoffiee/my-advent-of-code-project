/**
 * https://adventofcode.com/2015/day/13
 *
 * aoc_tags: combinatorics
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

namespace aoc::y2015::d13 {

using HappinessMap = std::unordered_map<std::string, std::unordered_map<std::string, int64_t>>;

HappinessMap parse_input(std::vector<std::string> const& inp) {
    HappinessMap happiness{};
    for (auto const& statement : inp) {
        auto const decomposed = aoc::string::split(statement, ' ');
        assert(decomposed.size() == 11u);

        int64_t sign{1};
        if (decomposed[2] == "lose") {
            sign = -1;
        }

        std::string const other_guest(decomposed[10].cbegin(), decomposed[10].cend() - 1u);
        happiness[decomposed[0]][other_guest] = sign * std::stoi(decomposed[3]);
    }
    return happiness;
}

int64_t calculate_happiness(HappinessMap& map, std::vector<std::string> const& guests) {
    int64_t sum{0};
    for (size_t i{0}; i < guests.size(); i++) {
        size_t next_i{(i + 1) % guests.size()};
        sum += map[guests.at(i)][guests.at(next_i)];
        sum += map[guests.at(next_i)][guests.at(i)];
    }
    return sum;
}

int64_t find_optimal_seating_score(HappinessMap& map, std::vector<std::string> guests) {
    int64_t best{0};
    while (std::next_permutation(guests.begin(), guests.end())) {
        auto cand = calculate_happiness(map, guests);
        if (cand > best) {
            best = cand;
        }
    }
    return best;
}

int64_t solve_1(std::vector<std::string> const& inp) {
    auto happiness = parse_input(inp);

    std::vector<std::string> guests{};
    for (auto const& [key, val] : happiness) {
        guests.push_back(key);
    }
    std::sort(guests.begin(), guests.end());

    return find_optimal_seating_score(happiness, guests);
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto happiness = parse_input(inp);

    // Utilize that accessing a key with [] with unordered_map will insert a
    // default value in the map, i.e. 0 which is what we want.
    std::vector<std::string> guests{"me"};
    for (auto const& [key, val] : happiness) {
        guests.push_back(key);
    }
    std::sort(guests.begin(), guests.end());

    return find_optimal_seating_score(happiness, guests);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 330);
    assert(solve_2(sample) == 286);
}

}  // namespace aoc::y2015::d13

using namespace aoc::y2015::d13;
int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

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
