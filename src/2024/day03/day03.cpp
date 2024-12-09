/**
 * https://adventofcode.com/2024/day/3
 */
#include <fstream>
#include <icecream.hpp>
#include <regex>
#include <string>
#include <vector>

int solve_1(std::vector<std::string> inp) {
    int sum{0};
    for (auto const& line : inp) {
        std::regex r("mul\\(\\d+,\\d+\\)");
        std::smatch match{};
        for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r); i != std::sregex_iterator();
             i++) {
            std::smatch match = *i;
            int a{0};
            int b{0};
            std::sscanf(match[0].str().c_str(), "mul(%d,%d)", &a, &b);
            sum += a * b;
        }
    }
    return sum;
}

int solve_2(std::vector<std::string> inp) {
    int sum{0};
    bool enable{true};
    for (auto const& line : inp) {
        std::regex r("(mul\\(\\d+,\\d+\\))|(don't\\(\\))|(do\\(\\))");
        std::smatch match{};
        for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r); i != std::sregex_iterator();
             i++) {
            std::smatch match = *i;

            if (match[2].length() > 0) {
                enable = false;
            }
            if (match[3].length() > 0) {
                enable = true;
            }
            if (enable && match[1].length()) {
                int a{0};
                int b{0};
                std::sscanf(match[1].str().c_str(), "mul(%d,%d)", &a, &b);
                sum += a * b;
            }
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
