/**
 * https://adventofcode.com/2021/day/14
 */
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2021::d14 {

using Rules = std::unordered_map<std::string, char>;

struct Counter {
    std::unordered_map<char, int64_t> counter_{};

    int64_t& operator[](char const key) { return counter_[key]; }

    Counter& operator+=(Counter const& rhs) {
        for (auto const& [key, val] : rhs.counter_) {
            counter_[key] += val;
        }
        return *this;
    }

    int64_t diff() const {
        int64_t min{INT64_MAX};
        int64_t max{0};
        for (auto const& [_, count] : counter_) {
            min = std::min(min, count);
            max = std::max(max, count);
        }
        return max - min;
    }
};

struct Solver {
    std::unordered_map<std::string, Counter> cache_;
    std::string polymer_template_{};
    Rules rules_;

    Solver(std::vector<std::string> const& inp) {
        polymer_template_ = inp.at(0);
        std::vector<std::string> inp_slice(inp.cbegin() + 2, inp.cend());
        for (auto const& rule : inp_slice) {
            auto line = aoc::string::split(rule, ' ');
            assert(line.size() == 3u);
            assert(line.at(0).size() == 2u);
            assert(line.at(2).size() == 1u);
            rules_[line.at(0)] = line.at(2).front();
        }
    }

    int64_t count(int64_t const steps) {
        Counter counter{};
        for (auto const& polymer : polymer_template_) {
            counter[polymer]++;
        }
        for (size_t i{0}; i < polymer_template_.size() - 1u; i++) {
            counter += recurse(polymer_template_.at(i), polymer_template_.at(i + 1), steps);
        }
        return counter.diff();
    }

    Counter recurse(char lhs, char rhs, int64_t const steps) {
        if (steps <= 0) {
            return {};
        }

        std::string entry{std::string{lhs, rhs} + std::to_string(steps)};

        if (cache_.contains(entry)) {
            return cache_.at(entry);
        }

        Counter counter{};
        std::string pair{lhs, rhs};
        counter[rules_.at(pair)]++;

        counter += recurse(lhs, rules_.at(pair), steps - 1);
        counter += recurse(rules_.at(pair), rhs, steps - 1);

        cache_[entry] = counter;
        return counter;
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Solver solver{inp};
    return solver.count(10);
}

int64_t solve_2(std::vector<std::string> inp) {
    Solver solver{inp};
    return solver.count(40);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 1588);
    assert(solve_2(sample) == 2188189693529);
}

};  // namespace aoc::y2021::d14

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2021::d14::solve_1(inp);
        assert(part1 == 2345);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2021::d14::solve_2(inp);
        assert(part2 == 2432786807053);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2021::d14::samples, solve_1_wrapper, solve_2_wrapper, input);
}
