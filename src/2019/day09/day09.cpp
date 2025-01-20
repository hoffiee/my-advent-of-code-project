/**
 * https://adventofcode.com/2019/day/5
 *
 * aoc_tags: intcode
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
#include "intcode_computer.h"
#include "string_utils.h"

namespace aoc::y2019::d9 {

int64_t solve_1(std::vector<std::string> const& inp) {
    auto instrs = string_utils::numbers_from_string(inp[0]);
    aoc::y2019::IntcodeComputer comp{instrs};
    comp.set_input(1);
    comp.exec();
    return comp.output_.back();
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto instrs = string_utils::numbers_from_string(inp[0]);
    aoc::y2019::IntcodeComputer comp{instrs};
    comp.set_input(2);
    comp.exec();
    return comp.output_.back();
}

void samples() {
    // TODO: Figure out some better prechecks...
    for (auto entry : std::vector<std::vector<int64_t>>{
             {1, 0, 0, 0, 99},
             {2, 3, 0, 3, 99},
             {2, 4, 4, 5, 99, 0},
             {1, 1, 1, 4, 99, 5, 6, 0, 99},

             {109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99},
             {1102, 34915192, 34915192, 7, 4, 7, 99, 0},
             {104, 1125899906842624, 99},
         }) {
        aoc::y2019::IntcodeComputer comp{entry};
        comp.set_input(1);
        comp.exec();
        comp.print();
        IC(comp.output_);
    }

    // auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    // assert(solve_1(sample) == 1);
    // assert(solve_2(sample) == 0);
    //
    // auto sample1 = string_utils::read_input("day09-sample-1.input");
    // assert(solve_1(sample1) == 0);
    // assert(solve_2(sample) == 0);
    //
    // auto sample2 = string_utils::read_input("day09-sample-2.input");
    // assert(solve_1(sample2) == 0);
    // assert(solve_2(sample) == 0);
    //
    // auto sample3 = string_utils::read_input("day09-sample-3.input");
    // assert(solve_1(sample3) == 0);
    // assert(solve_2(sample) == 0);
}

};  // namespace aoc::y2019::d9

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d9::solve_1(inp);
        assert(part1 == 2399197539);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d9::solve_2(inp);
        assert(part2 == 35106);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d9::samples, solve_1_wrapper, solve_2_wrapper, input);
}
