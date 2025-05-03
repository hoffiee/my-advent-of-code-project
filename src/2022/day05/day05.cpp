#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

#define MAX_CRATES 9

using std::pair;
using std::string;
using std::tuple;
using std::vector;
using stacks_t = vector<vector<char>>;
using instructions_t = vector<tuple<int, int, int>>;

tuple<stacks_t, instructions_t> read_and_parse_data(std::vector<std::string> const& input) {
    stacks_t stack_of_crates{MAX_CRATES};
    instructions_t instructions;
    bool parsing_stack_of_crates = true;
    for (auto const& line : input) {
        if (line.empty()) {
            parsing_stack_of_crates = false;
            continue;
        }
        if (parsing_stack_of_crates) {
            for (size_t i = 1; i < line.length(); i += 4) {
                if (line.at(i) != ' ' && !std::isdigit(line.at(i))) {
                    auto start = stack_of_crates.at(i / 4).begin();
                    stack_of_crates.at(i / 4).insert(start, line.at(i));
                }
            }
        } else {
            std::stringstream ss{line};
            string skip_word;
            int count = -1;
            int from = -1;
            int to = -1;
            ss >> skip_word >> count >> skip_word >> from >> skip_word >> to;
            instructions.emplace_back(std::make_tuple(count, from - 1, to - 1));
        }
    }
    return {stack_of_crates, instructions};
}

string construct_output(stacks_t stack_of_crates) {
    string out = "";
    for (auto& stack : stack_of_crates) {
        if (!stack.empty()) {
            out += stack.back();
        }
    }
    return out;
}

string solve_1(stacks_t stack_of_crates, instructions_t instructions) {
    for (auto [count, from, to] : instructions) {
        std::move(stack_of_crates.at(from).rbegin(), stack_of_crates.at(from).rbegin() + count,
                  std::back_inserter(stack_of_crates.at(to)));
        stack_of_crates.at(from).erase(stack_of_crates.at(from).end() - count, stack_of_crates.at(from).end());
    }
    return construct_output(stack_of_crates);
}

string solve_2(stacks_t stack_of_crates, instructions_t instructions) {
    for (auto [count, from, to] : instructions) {
        std::move(stack_of_crates.at(from).end() - count, stack_of_crates.at(from).end(),
                  std::back_inserter(stack_of_crates.at(to)));
        stack_of_crates.at(from).erase(stack_of_crates.at(from).end() - count, stack_of_crates.at(from).end());
    }
    return construct_output(stack_of_crates);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    auto [tmp1, tmp2] = read_and_parse_data(sample);
    assert(solve_1(tmp1, tmp2) == "CMZ");
    assert(solve_2(tmp1, tmp2) == "MCD");
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [tmp1, tmp2] = read_and_parse_data(inp);
        auto part1 = solve_1(tmp1, tmp2);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto [tmp1, tmp2] = read_and_parse_data(inp);
        auto part2 = solve_2(tmp1, tmp2);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
