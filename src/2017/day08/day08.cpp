/**
 * https://adventofcode.com/2017/day/8
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

struct CPU {
    std::unordered_map<std::string, int64_t> registers_{};
    int64_t max_value_{INT64_MIN};

    CPU() = default;
    bool check(std::string const& reg, std::string const& cond, int64_t val) {
        if (cond == ">") {
            return (registers_[reg] > val);
        } else if (cond == "<") {
            return (registers_[reg] < val);
        } else if (cond == ">=") {
            return (registers_[reg] >= val);
        } else if (cond == "<=") {
            return (registers_[reg] <= val);
        } else if (cond == "==") {
            return (registers_[reg] == val);
        } else if (cond == "!=") {
            return (registers_[reg] != val);
        } else {
            IC(reg, cond, val);
            assert(false);
        }
        return false;
    }

    void oper(std::string const& reg, std::string const& oper, int64_t val) {
        if (oper == "inc") {
            registers_[reg] += val;
        } else if (oper == "dec") {
            registers_[reg] -= val;
        } else {
            IC(reg, oper, val);
            assert(false);
        }
        max_value_ = std::max(registers_[reg], max_value_);
    }

    int64_t max() const {
        return (*std::max_element(registers_.cbegin(), registers_.cend(),
                                  [](auto const& lhs, auto const& rhs) { return lhs.second < rhs.second; }))
            .second;
    }
};

CPU solve(std::vector<std::string> const& inp) {
    CPU cpu{};
    for (auto const& instr : inp) {
        auto words = aoc::string::split(instr, ' ');
        assert(words.size() == 7);
        if (cpu.check(words[4], words[5], std::stoll(words[6]))) {
            cpu.oper(words[0], words[1], std::stoll(words[2]));
        }
    }
    return cpu;
}

int64_t solve_1(std::vector<std::string> const& inp) {
    auto cpu = solve(inp);
    return cpu.max();
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto cpu = solve(inp);
    return cpu.max_value_;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 1);
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
