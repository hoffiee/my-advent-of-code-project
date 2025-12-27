/**
 * https://adventofcode.com/2024/day/5
 *
 * Ouf, this got a bit messy, try to clean up a bit, probably would have avoided that if I did some unit tests along the
 * way...
 *
 * Later on I saw someone who sorted their pages with the page order rules as the base for the comparison for sort, so
 * implemented that in C++ and replaced my old solution. I kept my own solution.
 *
 * aoc_tags: sort according to custom rules
 */
#include <algorithm>
#include <fstream>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

bool valid_line(std::unordered_map<int64_t, std::vector<int64_t>> dependencies,
                std::unordered_map<int64_t, bool> printed, std::vector<int64_t> pages) {
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

bool dependencies_fulfilled(std::unordered_map<int64_t, std::vector<int64_t>> dependencies,
                            std::unordered_map<int64_t, bool> printed, int64_t page) {
    for (auto dep : dependencies[page]) {
        if (!printed[dep]) {
            return false;
        }
    }
    return true;
}

std::vector<int64_t> correct_line(std::unordered_map<int64_t, std::vector<int64_t>> dependencies,
                                  std::unordered_map<int64_t, bool> printed, std::vector<int64_t> pages) {
    std::vector<int64_t> out{};
    std::unordered_map<int64_t, std::vector<int64_t>> reduced_dependencies{};
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
    int64_t sum{0};

    std::unordered_map<int64_t, std::vector<int64_t>> dependencies{};
    std::unordered_map<int64_t, bool> printed{};

    bool reading_updates{false};

    for (auto& line : inp) {
        if (line.empty()) {
            // Now we've passed the first part of the input
            reading_updates = true;
            continue;
        }

        if (reading_updates) {
            auto pages{aoc::string::numbers_from_string(line)};
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

int64_t solve_2(std::vector<std::string> inp) {
    int64_t sum{0};

    std::unordered_map<int64_t, std::vector<int64_t>> dependencies{};
    std::unordered_map<int64_t, bool> printed{};

    bool reading_updates{false};

    for (auto& line : inp) {
        if (line.empty()) {
            // Now we've passed the first part of the input
            reading_updates = true;
            continue;
        }

        if (reading_updates) {
            auto pages{aoc::string::numbers_from_string(line)};
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

struct TupleHash {
    size_t operator()(const std::tuple<int64_t, int64_t>& t) const {
        auto hash1 = std::hash<int>{}(std::get<0>(t));
        auto hash2 = std::hash<int>{}(std::get<1>(t));
        return hash1 ^ (hash2 << 1);
    }
};

int64_t solve_2_sort(std::vector<std::string> inp) {
    int64_t sum{0};

    std::unordered_map<std::tuple<int, int>, int, TupleHash> rules{};
    std::unordered_map<int64_t, bool> printed{};

    bool reading_updates{false};

    for (auto& line : inp) {
        if (line.empty()) {
            // Now we've passed the first part of the input
            reading_updates = true;
            continue;
        }

        if (reading_updates) {
            auto pages{aoc::string::numbers_from_string(line)};
            std::vector<int64_t> updated{pages};
            // Sort according to the order in rules
            std::sort(updated.begin(), updated.end(), [&rules](int64_t lhs, int64_t rhs) {
                return rules.contains({lhs, rhs});
            });

            if (pages != updated) {
                sum += updated[updated.size() / 2];
            }
        } else {
            int x{0};
            int y{0};
            assert(std::sscanf(line.c_str(), "%d|%d", &x, &y) == 2);
            rules[std::make_tuple(x, y)];
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 6951);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 4121);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(
        argc, argv, []() {}, solve_1_wrapper, solve_2_wrapper, input);
}
