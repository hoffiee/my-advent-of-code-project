/**
 * With and without openmp, quite a good speedup for part 2
 *
 * day02 git:(master) ✗ hyperfine 2019_day02
 * Benchmark 1: 2019_day02
 *   Time (mean ± σ):     267.7 ms ±   4.2 ms    [User: 867.6 ms, System: 34.7
 * ms] Range (min … max):   261.3 ms … 274.6 ms    10 runs day02 git:(master) ✗
 * hyperfine 2019_day02 Benchmark 1: 2019_day02 Time (mean ± σ):      6.612 s ±
 * 0.155 s    [User: 6.292 s, System: 0.186 s] Range (min … max):    6.448 s
 * …  6.878 s    10 runs
 *
 */
#include AOC_HEADER

#include <omp.h>

#include <algorithm>
#include <exception>
#include <functional>
#include <icecream.hpp>
#include <numeric>

int solve_1(std::vector<int>& opcodes) {
    icecream::ic.disable();
    IC(opcodes);
    for (size_t i = 0; i < opcodes.size(); i += 4) {
        IC(opcodes.at(i));
        switch (opcodes.at(i)) {
            case 1: {
                // addition
                size_t src_a = static_cast<size_t>(opcodes.at(i + 1));
                size_t src_b = static_cast<size_t>(opcodes.at(i + 2));
                size_t dst = static_cast<size_t>(opcodes.at(i + 3));
                int a = opcodes.at(src_a);
                int b = opcodes.at(src_b);
                IC(opcodes.at(dst) = a + b);
                break;
            }
            case 2: {
                // multiplication
                size_t src_a = static_cast<size_t>(opcodes.at(i + 1));
                size_t src_b = static_cast<size_t>(opcodes.at(i + 2));
                size_t dst = static_cast<size_t>(opcodes.at(i + 3));
                int a = opcodes.at(src_a);
                int b = opcodes.at(src_b);
                IC(opcodes.at(dst) = a * b);
                break;
            }
            case 99: {
                // Not sure I like this...
                goto exit_operations;
                break;
            }
            default:
                throw std::domain_error("Shouldn't receive anything different than 1, 2, 99");
                break;
        }
    }
exit_operations:
    IC(opcodes);
    return opcodes.at(0);
}

int solve_2(std::vector<int>& opcodes) {
    int noun = 0;
    int verb = 0;
    bool found = false;
#pragma omp parallel for
    for (int noun_cand = 0; noun_cand < 100; noun_cand++) {
        if (found) {
            continue;
        }
#pragma omp parallel for
        for (int verb_cand = 0; verb_cand < 100; verb_cand++) {
            if (found) {
                continue;
            }
            std::vector<int> tmp = opcodes;
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
