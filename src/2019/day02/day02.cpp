/**
 * https://adventofcode.com/2019/day/2
 *
 * aoc_tags: intcode
 */
#include AOC_HEADER

#include <omp.h>

#include <algorithm>
#include <exception>
#include <functional>
#include <icecream.hpp>
#include <numeric>

#include "intcode_computer.h"

int64_t solve_1(std::vector<int64_t> const& inp) {
    aoc::y2019::IntcodeComputer comp{inp};
    return comp.exec(0);
}

int64_t solve_2(std::vector<int64_t> const& opcodes) {
    int64_t noun = 0;
    int64_t verb = 0;
    bool found = false;
#pragma omp parallel for
    for (int64_t noun_cand = 0; noun_cand < 100; noun_cand++) {
        if (found) {
            continue;
        }
#pragma omp parallel for
        for (int64_t verb_cand = 0; verb_cand < 100; verb_cand++) {
            if (found) {
                continue;
            }
            std::vector<int64_t> tmp = opcodes;
            tmp.at(1) = noun_cand;
            tmp.at(2) = verb_cand;
            if (solve_1(tmp) == 19690720) {
                noun = noun_cand;
                verb = verb_cand;
                found = true;
            }
        }
    }
    return 100 * noun + verb;
}
