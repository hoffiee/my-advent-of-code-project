/**
 * https://adventofcode.com/2024/day/5
 *
 * Ouf, this got a bit messy, try to clean up a bit, probably would have avoided that if I did some unit tests along the
 * way...
 */
#include <algorithm>
#include <fstream>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "string_utils.h"

bool valid_line(std::unordered_map<int, std::vector<int>> dependencies, std::unordered_map<int, bool> printed,
                std::vector<int> pages) {
    for (auto num : pages) {
        for (auto dep : dependencies[num]) {
            if (std::find(pages.begin(), pages.end(), dep) == pages.end()) {
                continue;
            }
            if (!printed[dep]) {
                return false;
            }
        }
        printed[num] = true;
    }
    return true;
}

bool dependencies_fulfilled(std::unordered_map<int, std::vector<int>> dependencies,
                            std::unordered_map<int, bool> printed, int page) {
    for (auto dep : dependencies[page]) {
        if (!printed[dep]) {
            return false;
        }
    }
    return true;
}

std::vector<int> correct_line(std::unordered_map<int, std::vector<int>> dependencies,
                              std::unordered_map<int, bool> printed, std::vector<int> pages) {
    std::vector<int> out{};

    // Make into own function
    std::unordered_map<int, std::vector<int>> reduced_dependencies{};
    for (auto x : pages) {
        reduced_dependencies[x];
        for (auto y : dependencies[x]) {
            if (std::find(pages.begin(), pages.end(), y) == pages.end()) {
                continue;
            }
            reduced_dependencies[x].push_back(y);
        }
    }
    for (ssize_t i{0}; i < static_cast<ssize_t>(pages.size());) {
        auto page = pages.at(i);

        if (printed[page]) {
            i++;
            continue;
        }

        if (dependencies_fulfilled(reduced_dependencies, printed, page)) {
            out.push_back(page);
            printed[page] = true;
            i++;
            continue;
        }

        for (auto dep : reduced_dependencies[page]) {
            if (printed[dep] || !dependencies_fulfilled(reduced_dependencies, printed, dep)) {
                continue;
            }

            out.push_back(dep);
            printed[dep] = true;
            break;
        }
    }

    assert(out.size() == pages.size());

    return out;
}

int solve_1(std::vector<std::string> inp) {
    int sum{0};

    std::unordered_map<int, std::vector<int>> dependencies{};
    std::unordered_map<int, bool> printed{};

    bool reading_updates{false};

    for (auto& line : inp) {
        if (line.empty()) {
            // Now we've passed the first part of the input
            reading_updates = true;
            continue;
        }

        if (reading_updates) {
            auto pages{string_utils::numbers_from_string(line)};
            if (!valid_line(dependencies, printed, pages)) {
                continue;
            }
            sum += pages.at(pages.size() / 2);
        } else {
            int x{0};
            int y{0};
            assert(std::sscanf(line.c_str(), "%d|%d", &x, &y) == 2);
            dependencies[y].push_back(x);
            printed[x];
        }
    }

    return sum;
}

int solve_2(std::vector<std::string> inp) {
    int sum{0};

    std::unordered_map<int, std::vector<int>> dependencies{};
    std::unordered_map<int, bool> printed{};

    bool reading_updates{false};

    for (auto& line : inp) {
        if (line.empty()) {
            // Now we've passed the first part of the input
            reading_updates = true;
            continue;
        }

        if (reading_updates) {
            auto pages{string_utils::numbers_from_string(line)};
            if (valid_line(dependencies, printed, pages)) {
                continue;
            }

            auto new_order = correct_line(dependencies, printed, pages);

            sum += new_order.at(pages.size() / 2);
        } else {
            int x{0};
            int y{0};
            assert(std::sscanf(line.c_str(), "%d|%d", &x, &y) == 2);
            dependencies[y].push_back(x);
            printed[x];
        }
    }

    return sum;
}

int main() {
    std::ifstream input_file;
    // input_file.open(AOC_SAMPLE_INPUT);
    input_file.open(AOC_INPUT);
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::vector<std::string> input;
    std::string line;
    while (getline(input_file, line)) {
        input.push_back(line);
    }

    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
