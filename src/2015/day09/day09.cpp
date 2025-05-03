/**
 * https://adventofcode.com/2015/day/9
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

using Graph = std::unordered_map<std::string, std::unordered_map<std::string, int64_t>>;
std::tuple<Graph, std::vector<std::string>> parse_input(std::vector<std::string> const& inp) {
    Graph graph{};
    std::vector<std::string> locations{};
    for (auto const& line : inp) {
        auto dat = aoc::string::split(line, ' ');
        assert(dat.size() == 5);

        graph[dat[0]][dat[2]] = std::stoll(dat[4]);
        graph[dat[2]][dat[0]] = std::stoll(dat[4]);
    }
    for (auto const& [key, _] : graph) {
        locations.emplace_back(key);
    }
    return {graph, locations};
}

int64_t solve_1(std::vector<std::string> const& inp) {
    auto [graph, locations] = parse_input(inp);

    int64_t shortest{INT64_MAX};
    do {
        int64_t cand_dist{0};
        for (size_t i{0}; i < locations.size() - 1; i++) {
            cand_dist += graph[locations[i]][locations[i + 1]];
            if (cand_dist > shortest) {
                break;
            }
        }
        if (cand_dist < shortest) {
            shortest = cand_dist;
        }
    } while (std::next_permutation(locations.begin(), locations.end()));
    return shortest;
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto [graph, locations] = parse_input(inp);
    int64_t longest{0};
    do {
        int64_t cand_dist{0};
        for (size_t i{0}; i < locations.size() - 1; i++) {
            cand_dist += graph[locations[i]][locations[i + 1]];
        }
        if (cand_dist > longest) {
            longest = cand_dist;
        }
    } while (std::next_permutation(locations.begin(), locations.end()));
    return longest;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 605);
    assert(solve_2(sample) == 982);
}

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
