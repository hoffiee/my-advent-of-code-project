/**
 * https://adventofcode.com/2021/day/10
 */
#include <cstdint>
#include <fstream>
#include <icecream.hpp>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

char matching_closure(char open) {
    switch (open) {
        case '<':
            return '>';
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
    }
    return ' ';
}

// TODO: refactor to onle one corrupt_line instead of corrupt_line/corrupt_stack
char corrupt_line(std::string_view line) {
    std::string const valid_open{"<([{"};
    std::string const valid_close{">)]}"};
    std::stack<char> stack{};
    for (char chr : line) {
        if (valid_open.find(chr) != std::string::npos) {
            stack.push(chr);
        }
        if (valid_close.find(chr) != std::string::npos) {
            if (stack.size() > 0 && matching_closure(stack.top()) == chr) {
                stack.pop();
            } else {
                return chr;
            }
        }
    }
    return ' ';
}

std::stack<char> corrupt_stack(std::string_view line) {
    std::string const valid_open{"<([{"};
    std::string const valid_close{">)]}"};
    std::stack<char> stack{};
    for (char chr : line) {
        if (valid_open.find(chr) != std::string::npos) {
            stack.push(chr);
        }
        if (valid_close.find(chr) != std::string::npos) {
            if (stack.size() > 0 && matching_closure(stack.top()) == chr) {
                stack.pop();
            }
        }
    }
    return stack;
}

int64_t solve_1(std::vector<std::string> inp) {
    int64_t sum{0};
    std::unordered_map<char, int64_t> const score_table{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}, {' ', 0}};

    for (auto& line : inp) {
        sum += score_table.at(corrupt_line(line));
    }
    return sum;
}

int64_t solve_2(std::vector<std::string> inp) {
    std::unordered_map<char, int64_t> score_table{{')', 1}, {']', 2}, {'}', 3}, {'>', 4}, {' ', 0}};

    std::vector<int64_t> scores{};
    for (auto& line : inp) {
        if (score_table.at(corrupt_line(line)) > 0) {
            // corrupt lines, disregard
            continue;
        }

        auto stack = corrupt_stack(line);

        int64_t score = 0;
        while (!stack.empty()) {
            score = 5 * score + score_table[matching_closure(stack.top())];
            stack.pop();
        }
        scores.push_back(score);
    }
    std::sort(scores.begin(), scores.end());

    return scores.at(scores.size() / 2);
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
