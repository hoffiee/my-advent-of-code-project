#include AOC_HEADER

#include <fstream>
#include <iostream>

int main() {
    std::ifstream input_file;
    input_file.open(AOC_TASK ".input");
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::string line;
    std::vector<std::string> terminal_output;
    while (getline(input_file, line)) {
        terminal_output.push_back(line);
    }

    auto [part1, part2] = solve(terminal_output);
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
