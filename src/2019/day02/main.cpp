#include <fstream>
#include <icecream.hpp>
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
    std::vector<int> opcodes;

    std::string line;
    getline(input_file, line);
    std::stringstream iss(line);
    int number = 0;
    while (iss >> number) {
        opcodes.push_back(number);
        if (iss.peek() == ',') {
            iss.ignore();
        }
    }

    // fix according to task
    auto opcodes_part_2 = opcodes;
    opcodes.at(1) = 12;
    opcodes.at(2) = 2;

    auto part1 = solve_1(opcodes);
    auto part2 = solve_2(opcodes_part_2);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
