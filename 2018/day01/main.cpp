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
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::string line;
    std::vector<std::string> frequency_shifts;
    while (getline(input_file, line)) {
        frequency_shifts.emplace_back(line);
    }

    auto [part1, part2] = solve(frequency_shifts);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
