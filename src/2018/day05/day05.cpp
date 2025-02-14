#include AOC_HEADER

#include <omp.h>

#include <cctype>
#include <exception>
#include <iostream>
#include <vector>

int solve_1(std::string input) {
    for (ssize_t i = 0; i < static_cast<ssize_t>(input.size()) - 1 && input.size() > 1; i++) {
        if (i < 0) {
            i = 0;
        }
        char unit_1 = input.at(static_cast<size_t>(i));
        char unit_2 = input.at(static_cast<size_t>(i) + 1);

        if (!std::isalpha(unit_1) || !std::isalpha(unit_2)) {
            throw std::domain_error("non alphabetical character");
        }

        // Common case, if they are the same, we continue to the next
        if (unit_1 == unit_2) {
            continue;
        }

        if (unit_1 == std::toupper(unit_2) || unit_1 == std::tolower(unit_2)) {
            input.erase(static_cast<size_t>(i), 2);
            i -= 2;
        }
    }
    return static_cast<int>(input.size());
}

int solve_2(std::string input) {
#if 1
    /**
     * day05 git:(master) ✗ hyperfine ./2018_day05
     * Benchmark 1: ./2018_day05
     * Time (mean ± σ):      2.547 s ±  0.440 s    [User: 7.070 s, System: 0.026
     * s] Range (min … max):    2.244 s …  3.722 s    10 runs
     *
     * a fair bit of an improvement, and it was suprisingly easy to get it
     * working...
     */
    // https://github.com/ysh329/OpenMP-101
    // https://riptutorial.com/openmp
    std::vector<int> results('z' - 'a', 0);
#pragma omp parallel for
    for (char i = 'a'; i < 'z'; i++) {
        std::string tmp(input);
        // TODO: do lambda and only iterate once?
        tmp.erase(std::remove(tmp.begin(), tmp.end(), i), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), std::toupper(i)), tmp.end());
        results.at(static_cast<size_t>(i - 'a')) = solve_1(tmp);
    }
    return *std::min_element(results.cbegin(), results.cend());
#else
    /**
     * day05 git:(master) ✗ hyperfine ./2018_day05
     * Benchmark 1: ./2018_day05
     * Time (mean ± σ):      7.296 s ±  0.057 s    [User: 7.218 s, System: 0.028
     * s] Range (min … max):    7.221 s …  7.370 s    10 runs
     */
    int min = solve_1(input);
    for (char i = 'a'; i < 'z'; i++) {
        std::string tmp(input);
        tmp.erase(std::remove(tmp.begin(), tmp.end(), i), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), std::toupper(i)), tmp.end());
        int score = solve_1(tmp);
        if (score < min) {
            min = score;
        }
    }
    return min;
#endif
}
