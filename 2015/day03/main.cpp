#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "2015_day03.h"

int main() {
    std::ifstream input_file;
    input_file.open("day03.input");
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::string line;
    getline(input_file, line);

    std::cout << solve(line, false) << std::endl;
    std::cout << solve(line, true) << std::endl;

    return 0;
}
