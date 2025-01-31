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
        std::cout << "couldn't read file:" AOC_INPUT << std::endl;
        return -1;
    }
    std::string line;
    getline(input_file, line);

    auto [x, y, dist, dist_to_hq] = solve(line);
    std::cout << x << ":" << y << " | " << dist << " | " << dist_to_hq << std::endl;

    return 0;
}
