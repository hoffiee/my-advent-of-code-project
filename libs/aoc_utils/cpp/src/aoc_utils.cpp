#include "aoc_utils.h"

#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>

std::vector<std::string> aoc::utils::read_input(std::string const& filename) {
    std::ifstream input_file{};
    input_file.open(filename);
    if (!input_file.is_open()) {
        std::cerr << "couldn't read file" << std::endl;
        return {};
    }
    std::vector<std::string> input{};
    std::string line{};
    while (getline(input_file, line)) {
        input.push_back(line);
    }
    return input;
}

int64_t aoc::math::lcm(std::vector<int64_t> vec) {
    assert(vec.size() >= 2);

    int64_t res = vec.at(0);
    for (size_t i = 1; i < vec.size(); i++) {
        res = ((vec[i] * res)) / (std::gcd(vec[i], res));
    }
    return res;
}

int64_t aoc::math::mod(int64_t a, int64_t b) {
    auto const babs = std::abs(b);
    return ((a % babs) + babs) % babs;
}

namespace aoc {
namespace string {

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
}  // namespace string
}  // namespace aoc

std::string aoc::string::join(std::vector<std::string> const& vec, std::string const delim) {
    std::string out{};
    for (auto entry : vec) {
        if (out.size() != 0) {
            out += delim;
        }
        out += entry;
    }
    return out;
}

std::vector<std::string> aoc::string::split(std::string str, char delim) {
    std::stringstream ss(str);
    std::string tmp{};
    std::vector<std::string> out{};
    while (getline(ss, tmp, delim)) {
        out.push_back(tmp);
    }
    return out;
}
