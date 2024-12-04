/**
 * https://adventofcode.com/2024/day/4
 */
#include <fstream>
#include <icecream.hpp>
#include <string>
#include <vector>
#include <regex>


int count_substring(std::string_view str, std::string_view substr) {
    int count{0};
    std::string::size_type pos{0};
    while ((pos = str.find(substr, pos)) != std::string::npos) {
            count++;
            pos += substr.length();
    }
    return count;
}

int count_diagonals(std::vector<std::string>& inp, size_t r, size_t c) {
    int count{0};
    if (
            inp.at(r).at(c) == 'X'
            && inp.at(r+1).at(c+1) == 'M'
            && inp.at(r+2).at(c+2) == 'A'
            && inp.at(r+3).at(c+3) == 'S'
            ) {
        count++;
    }
    if (
            inp.at(r).at(c) == 'S'
            && inp.at(r+1).at(c+1) == 'A'
            && inp.at(r+2).at(c+2) == 'M'
            && inp.at(r+3).at(c+3) == 'X'
            ) {
        count++;
    }

    if (
            inp.at(r+3).at(c) == 'X'
            && inp.at(r+2).at(c+1) == 'M'
            && inp.at(r+1).at(c+2) == 'A'
            && inp.at(r).at(c+3) == 'S'
            ) {
        count++;
    }
    if (
            inp.at(r+3).at(c) == 'S'
            && inp.at(r+2).at(c+1) == 'A'
            && inp.at(r+1).at(c+2) == 'M'
            && inp.at(r).at(c+3) == 'X'
            ) {
        count++;
    }
    return count;
}

bool find_pattern(std::vector<std::string> const& inp, size_t r, size_t c) {
    if (
        inp.at(r).at(c) == 'M'
        && inp.at(r).at(c+2) == 'S'
        && inp.at(r+1).at(c+1) == 'A'
        && inp.at(r+2).at(c) == 'M'
        && inp.at(r+2).at(c+2) == 'S'
       ) {
        return true;
    }

    if (
        inp.at(r).at(c) == 'S'
        && inp.at(r).at(c+2) == 'M'
        && inp.at(r+1).at(c+1) == 'A'
        && inp.at(r+2).at(c) == 'S'
        && inp.at(r+2).at(c+2) == 'M'
       ) {
        return true;
    }

    return false;
}

std::vector<std::string> transpose(std::vector<std::string> inp) {
    std::vector<std::string> transposed{};
    for (size_t c{0}; c < inp.at(0).size(); c++) {
        std::string row{};
        for (size_t r{0}; r < inp.size(); r++) {
            row += inp.at(r).at(c);
        }
        transposed.emplace_back(row);
    }
    return transposed;
}

int solve_1(std::vector<std::string> inp) {
    int sum{0};

    std::string s1{"XMAS"};
    std::string s2{"SAMX"};
    for (auto& line: inp) {
        sum += count_substring(line, s1);
        sum += count_substring(line, s2);
    }

    auto transposed{transpose(inp)};

    for (auto& line: transposed) {
        sum += count_substring(line, s1);
        sum += count_substring(line, s2);
    }

    for (size_t r{0}; r < inp.size() - 3; r++) {
        for (size_t c{0}; c < inp.size() - 3; c++) {
            sum += count_diagonals(inp, r, c);
        }
    }

    return sum;
}

int solve_2(std::vector<std::string> inp) {
    int sum{0};
    for (size_t r{0}; r < inp.size() - 2; r++) {
        for (size_t c{0}; c < inp.at(r).size() - 2; c++) {
            sum += find_pattern(inp, r, c);
        }
    }

    auto transposed{transpose(inp)};
    for (size_t r{0}; r < transposed.size() - 2; r++) {
        for (size_t c{0}; c < transposed.at(r).size() - 2; c++) {
            sum += find_pattern(transposed, r, c);
        }
    }
    return sum;
}

int main() {
    std::ifstream input_file;
    // input_file.open(AOC_SAMPLE_INPUT);
    input_file.open(AOC_INPUT);
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::vector<std::string> input;
    std::string line;
    while (getline(input_file, line)) {
        input.push_back(line);
    }

    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
