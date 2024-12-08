/**
 * https://adventofcode.com/2023/day/15
 *
 * p2: 259550 - too high
 * p2: 262930 - too high (not checked but larger than previous)
 */
#include AOC_HEADER

#include <string_utils.h>

#include <icecream.hpp>
#include <numeric>

size_t internal::hash(std::string inp) {
    size_t sum = 0;
    for (auto ch : inp) {
        sum += static_cast<size_t>(ch);
        sum *= 17;
        sum %= 256;
    }
    return sum;
}

int solve_1(std::vector<std::string> inp) {
    auto entries = string_utils::split_string(inp.at(0), ',');
    return static_cast<int>(std::accumulate(entries.cbegin(), entries.cend(), static_cast<ssize_t>(0),
                                            [](auto sum, auto& str) { return sum + internal::hash(str); }));
}

int solve_2(std::vector<std::string> inp) {
    auto steps = string_utils::split_string(inp.at(0), ',');
    std::vector<std::vector<std::pair<std::string, int>>> boxes(256, std::vector<std::pair<std::string, int>>());
    for (auto& step : steps) {
        if (step.back() == '-') {
            auto lens = string_utils::split_string(step, '-');
            auto& box = boxes[internal::hash(lens.at(0))];
            if (auto it = std::find_if(box.begin(), box.end(), [&](auto& obj) { return obj.first == lens.at(0); });
                it != box.end()) {
                box.erase(it);
            }
        } else {
            auto lens = string_utils::split_string(step, '=');
            int focal_length = std::stoi(lens.at(1));

            auto& box = boxes[internal::hash(lens.at(0))];
            if (auto it = std::find_if(box.begin(), box.end(), [&](auto& obj) { return obj.first == lens.at(0); });
                it != box.end()) {
                it->second = focal_length;

            } else {
                box.emplace_back(std::make_pair(lens.at(0), focal_length));
            }
        }
    }

    int sum = 0;
    for (size_t i = 0; i < boxes.size(); i++) {
        if (boxes.at(i).size() == 0) {
            continue;
        }
        auto& box = boxes.at(i);
        for (size_t j = 0; j < box.size(); j++) {
            sum += static_cast<int>(i + 1) * static_cast<int>(j + 1) * box.at(j).second;
        }
    }

    return sum;
}
