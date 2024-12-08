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
    std::vector<std::string> commands;
    while (getline(input_file, line)) {
        commands.emplace_back(line);
    }

    auto [lights_count, total_brightness] = solve(commands);
    std::cout << lights_count << std::endl;
    std::cout << total_brightness << std::endl;

    return 0;
}
