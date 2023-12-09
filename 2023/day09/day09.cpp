/**
 * https://adventofcode.com/2023/day/9
 */
#include AOC_HEADER

#include <omp.h>
#include <string_utils.h>

#include <algorithm>
#include <icecream.hpp>
#include <numeric>

static std::vector<std::vector<int>> parse_line(const std::string& line) {
    auto split_line = string_utils::split_string(line, ' ');
    std::vector<std::vector<int>> history(1, std::vector<int>(split_line.size(), 0));
    for (size_t i = 0; i < split_line.size(); i++) {
        history.at(0).at(i) = std::stoi(split_line.at(i));
    }
    return history;
}

static std::vector<int> diff(const std::vector<int>& v) {
    std::vector<int> out(v.size() - 1, 0);
    for (size_t i = 0; i < v.size() - 1; i++) {
        out[i] = v[i + 1] - v[i];
    }
    return out;
}

static bool continue_differentiate(const std::vector<int>& v) {
    return std::any_of(v.cbegin(), v.cend(), [](const int& val) { return val != 0; });
}

int solve_1(std::vector<std::string> inp) {
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < inp.size(); i++) {
        auto history = parse_line(inp.at(i));

        while (continue_differentiate(history.back())) {
            history.push_back(diff(history.back()));
        }

        for (size_t i = history.size() - 1; i > 0; i--) {
            auto& current = history[i];
            auto& next = history[i - 1];
            next.push_back(next.back() + current.back());
        }
        sum += history.front().back();
    }
    return sum;
}

int solve_2(std::vector<std::string> inp) {
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < inp.size(); i++) {
        auto history = parse_line(inp.at(i));

        while (continue_differentiate(history.back())) {
            history.push_back(diff(history.back()));
        }

        for (size_t i = history.size() - 1; i > 0; i--) {
            auto& current = history[i];
            auto& next = history[i - 1];
            next.insert(next.cbegin(), next.front() - current.front());
        }
        sum += history.front().front();
    }
    return sum;
}
