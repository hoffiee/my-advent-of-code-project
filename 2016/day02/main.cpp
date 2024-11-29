#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include AOC_HEADER

int main() {
    std::ifstream input_file;
    input_file.open(AOC_INPUT);
    if (!input_file.is_open()) {
        std::cout << "couldn't read file " AOC_TASK ".input" << std::endl;
        return -1;
    }
    std::string line;
    std::vector<std::string> instructions;
    while (getline(input_file, line)) {
        instructions.emplace_back(line);
    }

    auto [part1, part2] = solve(instructions);
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
