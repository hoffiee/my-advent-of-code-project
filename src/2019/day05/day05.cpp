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

namespace aoc::y2019::d5 {

int64_t solve_1(std::vector<std::string> const& inp) {
    auto instr = aoc::string::numbers_from_string(inp[0]);
    IntcodeComputer comp{instr};
    comp.set_input(1);
    comp.exec();
    return comp.output_.back();
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto instr = aoc::string::numbers_from_string(inp[0]);
    IntcodeComputer comp{instr};
    comp.set_input(5);
    comp.exec();
    return comp.output_.back();
}

void samples() {
    // TODO: Fix some checks
    // auto instr = aoc::string::numbers_from_string("3,9,8,9,10,9,4,9,99,-1,8");
    // IntcodeComputer comp{instr};
    // comp.exec(8);
    // IC(comp.output_);
    // assert(comp.output_ == 1);

    // assert(solve_1({"3,9,8,9,10,9,4,9,99,-1,8"}) == 1);
    //
    // auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    // assert(solve_2(sample) == 0);

    // auto sample1 = aoc::utils::read_input("day05-sample-1.input");
    // assert(solve_1(sample1) == 0);
    // assert(solve_2(sample) == 0);
}

};  // namespace aoc::y2019::d5

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d5::solve_1(inp);
        assert(part1 == 13294380);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d5::solve_2(inp);
        assert(part2 == 11460760);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d5::samples, solve_1_wrapper, solve_2_wrapper, input);
}
