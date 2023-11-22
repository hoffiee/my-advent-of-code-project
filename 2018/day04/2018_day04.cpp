/**
 * - years can be ignored, all input is during 1518
 * - This solution assumes input has been run through the preprocess script
 * - guard id bounded by <= 9999
 *
 *
1518-11-09 00:03 Guard #877 begins shift
1518-10-16 00:46 wakes up
1518-08-26 00:42 falls asleep
                 ^- 17
                        ^- 24, then we have a guard of maximum id < 9999
 */
#include AOC_HEADER

#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>
#include <unordered_map>

std::unordered_map<int, std::vector<int>> create_guards_sleep_statistics(std::vector<std::string>& input) {
    std::unordered_map<int, std::vector<int>> guards;
    int guard_id = -1;
    int fell_asleep_at_minute = 0;
    for (auto entry : input) {
        switch (entry.at(17)) {
            case 'G': {
                guard_id = std::stoi(entry.substr(24, 28));
                if (!guards.contains(guard_id)) {
                    guards.emplace(guard_id, std::vector<int>(60));
                }
                break;
            }
            case 'f': {
                // Guard falls asleep
                fell_asleep_at_minute = std::stoi(entry.substr(14, 15));
                break;
            }
            case 'w': {
                // Guard wakes up
                if (fell_asleep_at_minute == -1) {
                    throw std::domain_error("Can't wake up if you haven't fallen asleep");
                }
                int woke_up_at = std::stoi(entry.substr(14, 15));
                for (int i = fell_asleep_at_minute; i < woke_up_at; i++) {
                    guards.at(guard_id).at(i)++;
                }
                fell_asleep_at_minute = -1;
                break;
            }
            default:
                throw std::domain_error("Missing case in data.");
                break;
        }
    }
    return guards;
}

int part1(std::unordered_map<int, std::vector<int>>& guards) {
    int sleepiest_guard = -1;
    int sleepiest_max_sleep = -1;
    for (auto guard : guards) {
        int total_sleep = std::accumulate(guard.second.cbegin(), guard.second.cend(), 0);
        if (total_sleep > sleepiest_max_sleep) {
            sleepiest_max_sleep = total_sleep;
            sleepiest_guard = guard.first;
        }
    }
    auto result = std::max_element(guards.at(sleepiest_guard).cbegin(), guards.at(sleepiest_guard).cend());
    int minute = static_cast<int>(std::distance(guards.at(sleepiest_guard).cbegin(), result));
    return sleepiest_guard * minute;
}

int part2(std::unordered_map<int, std::vector<int>>& guards) {
    int guard_id = -1;
    int minute = -1;
    int max_occurences = -1;
    for (auto guard : guards) {
        auto occurence = std::max_element(guard.second.cbegin(), guard.second.cend());
        if (*occurence > max_occurences) {
            max_occurences = *occurence;
            guard_id = guard.first;
            minute = static_cast<int>(std::distance(guard.second.cbegin(), occurence));
        }
    }
    return guard_id * minute;
}

std::pair<int, int> solve(std::vector<std::string>& input) {
    auto guards = create_guards_sleep_statistics(input);
    return {part1(guards), part2(guards)};
}
