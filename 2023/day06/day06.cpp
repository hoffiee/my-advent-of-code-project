/**
 * https://adventofcode.com/2023/day/6
 */
#include AOC_HEADER

#include <string_utils.h>

#include <algorithm>
#include <cmath>
#include <icecream.hpp>

static int64_t calculate_possibilities(int64_t T, int64_t d) {
    /**
     * s = vt
     * v = t_hold
     * T = t + t_hold
     *
     * T: total time
     * S: distance to beat
     *
     * gives
     *
     * t = T/2 +- sqrt( T*T/4 - S)
     *
     * t must be integers in the non inclusive range (T/2 - sqrt(T*T/4 - S), T/2 + sqrt(T*T/4 - S))
     */
    double diff = std::sqrt(static_cast<double>(T) * static_cast<double>(T) / 4 - static_cast<double>(d));
    double lower = static_cast<double>(T) / 2.0 - diff;
    double upper = static_cast<double>(T) / 2.0 + diff;
    return static_cast<int64_t>(std::ceil(upper) - std::floor(lower) - 1);
}

int solve_1(std::vector<std::string> inp) {
    std::vector<int> time;
    std::stringstream ss_time(inp.at(0).substr(inp.at(0).find(":") + 1));
    int tmp = 0;
    while (ss_time >> tmp) {
        time.push_back(tmp);
    }

    std::vector<int> distance;
    std::stringstream ss_dist(inp.at(1).substr(inp.at(1).find(":") + 1));
    while (ss_dist >> tmp) {
        distance.push_back(tmp);
    }

    int prod = 1;
    for (size_t i = 0; i < time.size(); i++) {
        prod *= static_cast<int>(calculate_possibilities(time.at(i), distance.at(i)));
    }

    return prod;
}

int64_t solve_2(std::vector<std::string> inp) {
    for (auto& line : inp) {
        line.erase(std::remove_if(line.begin(), line.end(), [](auto x) { return std::isspace(x); }), line.end());
    }

    int64_t T = std::stoll(inp.at(0).substr(inp.at(0).find(":") + 1));
    int64_t d = std::stoll(inp.at(1).substr(inp.at(1).find(":") + 1));

    return calculate_possibilities(T, d);
}
