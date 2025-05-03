/**
 * https://adventofcode.com/2017/day/9
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

std::tuple<int64_t, size_t> dive_garbage(std::string const& inp, size_t idx) {
    if (idx >= inp.size()) {
        return {0, idx};
    }
    size_t i{idx};
    int64_t count{0};
    for (; i < inp.size(); i++) {
        switch (inp[i]) {
            case '!': {
                i++;
                break;
            }
            case '>': {
                return {count, i};
            }
            default:
                count++;
                break;
        }
    }
    return {count, i};
}

std::tuple<int64_t, size_t> dive(std::string const& inp, size_t idx, int64_t depth) {
    if (idx >= inp.size()) {
        return {0, idx};
    }

    int64_t sum{0};
    size_t i{idx};
    for (; i < inp.size(); i++) {
        switch (inp[i]) {
            case '!': {
                i++;
                break;
            }
            case '<': {
                auto [_, idx_new] = dive_garbage(inp, i + 1);
                i = idx_new;
                break;
            }
            case '{': {
                auto [add, idx_new] = dive(inp, i + 1, depth + 1);
                i = idx_new;
                sum += add;
                break;
            }
            case '}':
                return {sum + depth, i};
            default:
                break;
        }
    }
    return {sum, i};
}

int64_t solve_1(std::vector<std::string> const& inp) {
    assert(inp.size() == 1);
    auto [sum, idx] = dive(inp[0], 0, 0);
    assert(idx == inp[0].size());
    return sum;
}

int64_t solve_2(std::vector<std::string> const& inp) {
    int64_t sum{0};
    for (size_t i{0}; i < inp[0].size(); i++) {
        switch (inp[0][i]) {
            case '!': {
                i++;
                break;
            }
            case '<': {
                auto [add, idx_new] = dive_garbage(inp[0], i + 1);
                i = idx_new;
                sum += add;
                break;
            }
            default:
                break;
        }
    }
    return sum;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 1);

    auto sample1 = aoc::utils::read_input("day09-sample-1.input");
    assert(solve_1(sample1) == 6);

    auto sample2 = aoc::utils::read_input("day09-sample-2.input");
    assert(solve_1(sample2) == 5);

    auto sample3 = aoc::utils::read_input("day09-sample-3.input");
    assert(solve_1(sample3) == 16);

    auto sample4 = aoc::utils::read_input("day09-sample-4.input");
    assert(solve_1(sample4) == 1);

    auto sample5 = aoc::utils::read_input("day09-sample-5.input");
    assert(solve_1(sample5) == 9);

    auto sample6 = aoc::utils::read_input("day09-sample-6.input");
    assert(solve_1(sample6) == 9);

    auto sample7 = aoc::utils::read_input("day09-sample-7.input");
    assert(solve_1(sample7) == 3);

    auto sample8 = aoc::utils::read_input("day09-sample-8.input");
    assert(solve_2(sample8) == 0);

    auto sample9 = aoc::utils::read_input("day09-sample-9.input");
    assert(solve_2(sample9) == 17);

    auto sample10 = aoc::utils::read_input("day09-sample-10.input");
    assert(solve_2(sample10) == 3);

    auto sample11 = aoc::utils::read_input("day09-sample-11.input");
    assert(solve_2(sample11) == 2);

    auto sample12 = aoc::utils::read_input("day09-sample-12.input");
    assert(solve_2(sample12) == 0);

    auto sample13 = aoc::utils::read_input("day09-sample-13.input");
    assert(solve_2(sample13) == 0);

    auto sample14 = aoc::utils::read_input("day09-sample-14.input");
    assert(solve_2(sample14) == 10);
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
