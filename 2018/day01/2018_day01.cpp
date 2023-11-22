#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>

std::pair<int, int> solve(std::vector<std::string> frequency_shifts) {
    std::vector<int> frequency_diffs;
    auto calc_diff = [](const std::string& shift) {
        switch (shift.at(0)) {
            case '+':
                return std::stoi(shift.substr(1));
            case '-':
                return -std::stoi(shift.substr(1));
        }
        return 0;
    };

    std::transform(frequency_shifts.cbegin(), frequency_shifts.cend(), std::back_inserter(frequency_diffs), calc_diff);

    std::unordered_map<int, bool> frequencies{{0, 0}};
    int curr_freq = 0;

    /* If any of these two are positive we will never find the same frequency
     * again, skip iterate over and just return 0 in that case */
    bool all_positive =
        std::all_of(frequency_diffs.cbegin(), frequency_diffs.cend(), [](const int n) { return n >= 0; });
    bool all_negative =
        std::all_of(frequency_diffs.cbegin(), frequency_diffs.cend(), [](const int n) { return n < 0; });

    for (auto it = frequency_diffs.cbegin(); !all_positive && !all_negative; ++it) {
        if (it == frequency_diffs.cend()) {
            it = frequency_diffs.cbegin();
        }
        curr_freq += *it;
        if (frequencies.contains(curr_freq)) {
            break;
        }
        frequencies.insert_or_assign(curr_freq, 0);
    }
    return {std::accumulate(frequency_diffs.cbegin(), frequency_diffs.cend(), 0), curr_freq};
}
