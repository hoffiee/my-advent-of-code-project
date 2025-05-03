/**
 * https://adventofcode.com/2015/day/17
 *
 * After some issues with long runtimes with my approach of generating all combinations, which had some issues here and
 * there, I found a recursive approach which worked better.
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

struct Container {
    uint64_t id;
    int64_t volume;

    friend std::ostream& operator<<(std::ostream& os, Container const& c) {
        os << c.id << ":" << c.volume;
        return os;
    }
};

bool compare(Container const& lhs, Container const& rhs) { return lhs.id < rhs.id; }

std::vector<Container> get_containers(std::vector<std::string> const& inp) {
    std::vector<Container> containers{};
    uint64_t id{0};
    for (auto number : inp) {
        containers.emplace_back(Container{1ULL << id, std::stoll(number)});
        id++;
    }
    assert(id < 64);
    std::sort(containers.begin(), containers.end(),
              [](auto const& lhs, auto const& rhs) { return lhs.volume > rhs.volume; });
    return containers;
}

void solve(std::vector<Container> const& containers, std::unordered_map<size_t, int64_t>& results, size_t idx,
           int64_t target, int64_t use) {
    if (target < 0) {
        return;
    }
    if (idx == containers.size()) {
        if (target == 0) {
            results[use]++;
        }
        return;
    }
    solve(containers, results, idx + 1, target, use);
    solve(containers, results, idx + 1, target - containers[idx].volume, use + 1);
}

int64_t solve_1(std::vector<std::string> const& inp, int64_t target) {
    auto containers = get_containers(inp);
    std::unordered_map<size_t, int64_t> used{};
    solve(containers, used, 0, target, 0);
    auto sum = std::accumulate(used.cbegin(), used.cend(), static_cast<int64_t>(0),
                               [](int64_t acc, auto const& c) { return acc + c.second; });
    return sum;
}

int64_t solve_2(std::vector<std::string> const& inp, int64_t target) {
    auto containers = get_containers(inp);
    std::unordered_map<size_t, int64_t> used{};
    solve(containers, used, 0, target, 0);

    auto obj = std::min_element(used.cbegin(), used.cend(),
                                [](auto const& lhs, auto const& rhs) { return lhs.first < rhs.first; });
    return obj->second;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, 25) == 4);
    assert(solve_2(sample, 25) == 3);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp, 150);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp, 150);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
