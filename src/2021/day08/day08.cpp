/**
 * https://adventofcode.com/2021/day/8
 */
#include <cstdint>
#include <icecream.hpp>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

int64_t solve_1(std::vector<std::string> inp) {
    int64_t count{0};
    for (auto const& line : inp) {
        auto split = aoc::string::split(line, '|');
        auto digits = aoc::string::split(split.back(), ' ');
        for (auto const& digit : digits) {
            switch (digit.size()) {
                case 0:
                    // remnant from bad split function, do nothing
                    break;
                case 2:  // 1
                case 3:  // 7
                case 4:  // 4
                case 7:  // 8
                    count++;
                    break;
                case 5:  // 2,3,5
                case 6:  // 6,9
                    // do nothing
                    break;
                default:
                    assert(false);
            }
        }
    }
    return count;
}

std::size_t intersection_size(std::set<char> const& set, std::string const& str) {
    std::set<char> out{};
    std::set<char> str_set(str.cbegin(), str.cend());
    std::set_intersection(set.cbegin(), set.cend(), str_set.cbegin(), str_set.cend(), std::inserter(out, out.begin()));
    return out.size();
}

int64_t solve_2(std::vector<std::string> inp) {
    int64_t count{0};
    for (auto const& line : inp) {
        auto split = aoc::string::split(line, '|');
        auto pilots = aoc::string::split(split.front(), ' ');
        auto digits = aoc::string::split(split.back(), ' ');

        std::unordered_map<int, std::set<char>> display{};

        for (auto const& digit : pilots) {
            switch (digit.size()) {
                case 0:
                    // remnant from bad split function, do nothing
                    break;
                case 2:  // 1
                    display[1] = std::set<char>(digit.cbegin(), digit.cend());
                    break;
                case 3:  // 7
                    display[7] = std::set<char>(digit.cbegin(), digit.cend());
                    break;
                case 4:  // 4
                    display[4] = std::set<char>(digit.cbegin(), digit.cend());
                    break;
                case 7:  // 8
                    display[8] = std::set<char>(digit.cbegin(), digit.cend());
                    break;
                case 5:  // 2,3,5
                case 6:  // 0,6,9
                    break;
                default:
                    assert(false);
            }
        }

        // Check that we get what we expect from the pilots. Could probably be
        // reduced if there's an issue
        assert(!display[1].empty());
        assert(!display[4].empty());
        assert(!display[7].empty());
        assert(!display[8].empty());

        int64_t number{0};
        for (auto const& digit : digits) {
            switch (digit.size()) {
                case 0:
                    // remnant from bad split function, do nothing
                    break;
                case 2:  // 1
                    number = 10 * number + 1;
                    break;
                case 3:  // 7
                    number = 10 * number + 7;
                    break;
                    break;
                case 4:  // 4
                    number = 10 * number + 4;
                    break;
                case 7:  // 8
                    number = 10 * number + 8;
                    break;
                case 5: {  // 2,3,5
                    if (intersection_size(display[1], digit) == 2) {
                        number = 10 * number + 3;
                    } else if (intersection_size(display[4], digit) == 2) {
                        number = 10 * number + 2;
                    } else {
                        number = 10 * number + 5;
                    }
                    break;
                }
                case 6:  // 0,6,9
                    if (intersection_size(display[7], digit) == 2) {
                        number = 10 * number + 6;
                    } else if (intersection_size(display[4], digit) == 4) {
                        number = 10 * number + 9;
                    } else {
                        number = 10 * number + 0;
                    }
                    break;
                default:
                    assert(false);
            }
        }
        count += number;
    }
    return count;
}

void checks() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 26);
    assert(solve_2({"acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf"}) == 5353);
    assert(solve_2(sample) == 61229);
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

    return aoc::run(argc, argv, checks, solve_1_wrapper, solve_2_wrapper, input);
}
