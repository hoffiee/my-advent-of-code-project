/**
 * https://adventofcode.com/2024/day/11
 *
 * Notes to self
 *  - using asserts along the way is key to check assumptions!
 */
#include <cmath>
#include <complex>
#include <cstdint>
#include <icecream.hpp>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

uint64_t nr_of_digits(uint64_t number) {
    if (number == 0) return 1;
    return floor(log10(number)) + 1;
}

std::unordered_map<uint64_t, uint64_t> create_stones(std::string const& inp) {
    auto numbers = aoc::string::numbers_from_string(inp);
    std::unordered_map<uint64_t, uint64_t> stones{};
    for (auto num : numbers) {
        stones[num]++;
    }
    return stones;
}

uint64_t solve(std::string inp, uint64_t steps) {
    auto stones = create_stones(inp);
    for (uint64_t i{0}; i < steps; i++) {
        std::unordered_map<uint64_t, uint64_t> stones_new{};
        for (auto const [stone, count] : stones) {
            auto digits = nr_of_digits(stone);
            if (stone == 0) {
                stones_new[1] += count;
                assert(stone >= 0);
            } else if (digits % 2 == 0) {
                std::string num_str{std::to_string(stone)};
                uint64_t left_stone{static_cast<uint64_t>(std::stoll(num_str.substr(0, num_str.length() / 2)))};
                uint64_t right_stone{
                    static_cast<uint64_t>(std::stoll(num_str.substr(num_str.length() / 2, num_str.length())))};

                stones_new[left_stone] += count;
                stones_new[right_stone] += count;
                assert(left_stone >= 0);
                assert(right_stone >= 0);
                assert(stone >= 0);
            } else {
                uint64_t st = stone * static_cast<uint64_t>(2024);
                stones_new[st] += count;
                assert(st >= 0);
            }
        }

        stones.clear();
        for (auto [stone, count] : stones_new) {
            stones[stone] = count;
        }
    }

    uint64_t sum{0};
    for (auto [stone, count] : stones) {
        sum += count;
    }

    return sum;
}

void samples() {
    assert(solve({"125 17"}, 1) == 3);
    assert(solve({"125 17"}, 2) == 4);
    assert(solve({"125 17"}, 3) == 5);
    assert(solve({"125 17"}, 4) == 9);
    assert(solve({"125 17"}, 5) == 13);
    assert(solve({"125 17"}, 6) == 22);
    assert(solve({"125 17"}, 25) == 55312);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve(inp[0], 25) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve(inp[0], 75) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
