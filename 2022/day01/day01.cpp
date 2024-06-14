/**
 * https://adventofcode.com/2022/day/1
 */
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

static void solution_1(std::vector<int64_t> sorted_inventory) {
    std::cout << "Biggest inventory: " << sorted_inventory.front() << std::endl;
}

static void solution_2(std::vector<int64_t> sorted_inventory) {
    std::cout << "sum: "
              << std::accumulate(sorted_inventory.begin(), sorted_inventory.begin() + 3, static_cast<int64_t>(0))
              << std::endl;
}

static std::vector<int64_t> read_and_process_data(std::string filename) {
    std::fstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "failed to open: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<int64_t> calories;
    int64_t current_calories = 0;
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) {
            calories.push_back(current_calories);
            current_calories = 0;
            continue;
        }
        current_calories += stoi(line);
    }
    calories.push_back(current_calories);
    std::sort(calories.rbegin(), calories.rend());
    return calories;
}

int main(void) {
    auto sample_input = read_and_process_data("day01-sample.input");
    solution_1(sample_input);
    solution_2(sample_input);

    auto input = read_and_process_data("day01.input");
    solution_1(input);
    solution_2(input);
}
