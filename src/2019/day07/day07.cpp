/**
 * https://adventofcode.com/2019/day/7
 *
 * aoc_tags: intcode
 */
#include <algorithm>
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <map>
#include <numbers>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "intcode_computer.h"
#include "string_utils.h"

namespace aoc::y2019::d7 {

struct Amplifier {
    int64_t& input_;
    int64_t output_{};
    aoc::y2019::IntcodeComputer comp_;

    Amplifier(std::vector<int64_t> const& program, int64_t const phase, int64_t& input)
        : input_(input), comp_{aoc::y2019::IntcodeComputer{program}} {
        comp_.set_input(phase);
    }

    void run() {
        comp_.set_input(input_);
        comp_.exec();
        output_ = comp_.output_.back();
    }
};

int64_t solve_1(std::vector<std::string> const& inp) {
    auto program = string_utils::numbers_from_string(inp[0]);

    std::vector<int> phases = {0, 1, 2, 3, 4};

    int64_t start{0};
    int64_t max{0};
    do {
        Amplifier A1(program, phases[0], start);
        Amplifier A2(program, phases[1], A1.output_);
        Amplifier A3(program, phases[2], A2.output_);
        Amplifier A4(program, phases[3], A3.output_);
        Amplifier A5(program, phases[4], A4.output_);

        A1.run();
        A2.run();
        A3.run();
        A4.run();
        A5.run();

        if (A5.output_ > max) {
            max = A5.output_;
        }
    } while (std::next_permutation(phases.begin(), phases.end()));

    return max;
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto program = string_utils::numbers_from_string(inp[0]);

    std::vector<int> phases = {5, 6, 7, 8, 9};
    int64_t max{0};
    do {
        int64_t y{0};
        int64_t y_z1{-1};

        Amplifier A1(program, phases[0], y);
        Amplifier A2(program, phases[1], A1.output_);
        Amplifier A3(program, phases[2], A2.output_);
        Amplifier A4(program, phases[3], A3.output_);
        Amplifier A5(program, phases[4], A4.output_);

        // continue until we've reached a stable point
        while (y != y_z1) {
            A1.run();
            A2.run();
            A3.run();
            A4.run();
            A5.run();

            y_z1 = y;
            y = A5.output_;
        }
        max = std::max({max, A5.output_});
    } while (std::next_permutation(phases.begin(), phases.end()));
    return max;
}

void samples() {
    assert(solve_1({"3,15,3,16,1002,16,10,16,1,16,"
                    "15,15,4,15,99,0,0"}) == 43210);
    assert(solve_1({"3,23,3,24,1002,24,10,24,1002,23,-1,23,"
                    "101,5,23,23,1,24,23,23,4,23,99,0,0"}) == 54321);
    assert(solve_1({"3,31,3,32,1002,32,10,32,1001,31,-2,31,"
                    "1007,31,0,33,1002,33,7,33,1,33,31,31,"
                    "1,32,31,31,4,31,99,0,0,0"}) == 65210);

    assert(solve_2({"3,26,1001,26,-4,26,3,27,1002,27,2,27,1,"
                    "27,26,27,4,27,1001,28,-1,28,1005,28,6,"
                    "99,0,0,5"}) == 139629729);
    assert(solve_2({"3,52,1001,52,-5,52,3,53,1,52,56,54,1007,"
                    "54,5,55,1005,55,26,1001,54,-5,54,1105,1,"
                    "12,1,53,54,53,1008,54,0,55,1001,55,1,55,"
                    "2,53,55,53,4,53,1001,56,-1,56,1005,56,6,"
                    "99,0,0,0,0,10"}) == 18216);
}

};  // namespace aoc::y2019::d7

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d7::solve_1(inp);
        assert(part1 == 14902);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d7::solve_2(inp);
        assert(part2 == 6489132);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d7::samples, solve_1_wrapper, solve_2_wrapper, input);
}
