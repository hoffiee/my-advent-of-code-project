/**
 * https://adventofcode.com/2023/day/1
 *
 * This is a bit inefficient, I assume std::string continues to search the rest
 * of the string if it doesn't match the current position so even if we will
 * ignore a match later on we continue the search, so a method which only
 * matches the current position would speed this up a bit.
 */
#include AOC_HEADER

#include <algorithm>
#include <cctype>
#include <icecream.hpp>
#include <string_view>

int solve_1(std::vector<std::string> inp) {
    auto condition_fcn = [](auto entry) { return std::isdigit(entry); };

    int sum = 0;
    for (auto line : inp) {
        int first = *std::find_if(line.begin(), line.end(), condition_fcn) - '0';
        int second = *std::find_if(line.rbegin(), line.rend(), condition_fcn) - '0';
        sum += first * 10 + second;
    }
    return sum;
}

static int match_digit(std::string_view line, size_t i) {
    const std::vector<std::string> digits{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    if (std::isdigit(line.at(i))) {
        return line.at(i) - '0';
    }

    for (size_t j = 0; j < digits.size(); j++) {
        if (line.substr(i, digits.at(j).size()) == digits.at(j)) {
            return static_cast<int>(j) + 1;
        }
    }
    return -1;
}

int solve_2(std::vector<std::string> inp) {
    int sum = 0;
    for (auto line : inp) {
        int first = 0;
        for (size_t i = 0; i < line.size(); i++) {
            if (int res = match_digit(line, i); res > -1) {
                first = res;
                break;
            }
        }

        int second = 0;
        for (size_t i = line.size() - 1; 0 <= i; i--) {
            if (int res = match_digit(line, i); res > -1) {
                second = res;
                break;
            }
        }
        sum += first * 10 + second;
    }
    return sum;
}
