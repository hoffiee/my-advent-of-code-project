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
    std::vector<std::string> words;
    while (getline(input_file, line)) {
        words.push_back(line);
    }

    std::cout << solve_1(words) << std::endl;
    std::cout << solve_2(words) << std::endl;

    return 0;
}
