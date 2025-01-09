/**
 * https://adventofcode.com/2016/day/10
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

struct Bot {
    std::string name_{};
    std::string low_{};
    std::string high_{};
    bool valid_{false};

    Bot() = default;
    Bot(std::string name, std::string low, std::string high) : name_{name}, low_{low}, high_{high}, valid_{true} {}

    friend std::ostream& operator<<(std::ostream& os, Bot const& b) {
        os << b.name_ << "<" << b.low_ << "|" << b.high_ << ">";
        return os;
    }
};

std::tuple<int, int> solve(std::vector<std::string> const& inp, bool exit_early, std::tuple<int, int> target) {
    std::unordered_map<std::string, std::vector<int>> inventory{};
    std::unordered_map<std::string, Bot> graph{};

    for (auto const& line : inp) {
        switch (line[0]) {
            case 'v': {
                auto words = aoc::string::split(line, ' ');
                assert(words.size() == 6);
                inventory[words[4][0] + words[5]].push_back(std::stoi(words[1]));
                break;
            }
            case 'b': {
                auto words = aoc::string::split(line, ' ');
                assert(words.size() == 12);
                auto src = words[0][0] + words[1];
                auto dst_low = words[5][0] + words[6];
                auto dst_high = words[10][0] + words[11];
                graph[src] = Bot{src, dst_low, dst_high};
                break;
            }
            default:
                assert(false);
        }
    }

    bool work_done{true};
    int bot_target_check{};
    while (work_done) {
        work_done = false;
        for (auto& [bot, content] : inventory) {
            if (bot[0] == '0') {
                continue;
            }

            assert(content.size() < 3);
            if (content.size() < 2) {
                continue;
            }

            if ((content[0] == std::get<0>(target) || content[1] == std::get<0>(target)) &&
                (content[0] == std::get<1>(target) || content[1] == std::get<1>(target))) {
                if (exit_early) {
                    return {std::stoi(bot.substr(1)), 0};
                }
                bot_target_check = std::stoi(bot.substr(1));
            }
            work_done = true;
            inventory[graph[bot].low_].push_back(*std::min_element(content.cbegin(), content.cend()));
            inventory[graph[bot].high_].push_back(*std::max_element(content.cbegin(), content.cend()));
            content.clear();
        }
    }

    assert(inventory["o0"].size() == 1);
    assert(inventory["o1"].size() == 1);
    assert(inventory["o2"].size() == 1);

    return {bot_target_check, inventory["o0"][0] * inventory["o1"][0] * inventory["o2"][0]};
}

int64_t solve_1(std::vector<std::string> const& inp, std::tuple<int, int> target = {17, 61}) {
    return std::get<0>(solve(inp, true, target));
}

int64_t solve_2(std::vector<std::string> const& inp, std::tuple<int, int> target = {17, 61}) {
    return std::get<1>(solve(inp, false, target));
}

void samples() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, {2, 5}) == 2);
    assert(solve_2(sample, {2, 5}) == 5 * 2 * 3);
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
