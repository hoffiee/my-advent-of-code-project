#include "string_utils.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace string_utils {

std::vector<int64_t> numbers_from_string(std::string str) {
    std::vector<int64_t> out{};

    std::regex number_regex(R"(-?\d+)");
    std::sregex_iterator current_match(str.begin(), str.end(), number_regex);
    std::sregex_iterator last_match{};

    while (current_match != last_match) {
        out.emplace_back(std::stoll(current_match->str()));
        current_match++;
    }
    return out;
}

std::vector<uint64_t> unumbers_from_string(std::string str) {
    std::vector<uint64_t> out{};

    std::regex number_regex(R"(-?\d+)");
    std::sregex_iterator current_match(str.begin(), str.end(), number_regex);
    std::sregex_iterator last_match{};

    while (current_match != last_match) {
        out.emplace_back(std::stoll(current_match->str()));
        current_match++;
    }
    return out;
}
}  // namespace string_utils
