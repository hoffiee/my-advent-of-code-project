#include <fstream>
#include <icecream.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include AOC_HEADER

int main() {
    auto part1 = solve_1(178416, 676461);
    auto part2 = solve_2(178416, 676461);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
