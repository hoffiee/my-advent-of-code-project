#include "string_utils.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace string_utils {

std::vector<std::string> read_input(std::string filename) {
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

std::vector<std::string> split_string(std::string str, char delim) {
    std::stringstream ss(str);
    std::string tmp{};
    std::vector<std::string> out{};
    while (getline(ss, tmp, delim)) {
        out.push_back(tmp);
    }
    return out;
}

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

}  // namespace string_utils
