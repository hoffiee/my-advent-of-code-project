/**
 * https://adventofcode.com/2023/day/3
 *
 * part 1:
 * Create map of valid placings
 * parse numbers and sum if it's within a valid placing
 *
 * part 2:
 * Find valid gears and mark with gear index
 * Find numbers, if within gear index, multiply to gear ratio
 */
#include AOC_HEADER

#include <algorithm>
#include <cctype>
#include <icecream.hpp>
#include <numeric>

static void mark_surrounding_valid(std::vector<std::vector<bool>>& map, size_t rmark, size_t cmark) {
    size_t rlower = rmark > static_cast<size_t>(0) ? rmark - 1 : rmark;
    size_t rupper = rmark + 1 < map.size() ? rmark + 1 : rmark;
    size_t clower = cmark > static_cast<size_t>(0) ? cmark - 1 : cmark;
    size_t cupper = cmark + 1 < map.size() ? cmark + 1 : cmark;

    for (size_t r = rlower; r <= rupper; r++) {
        for (size_t c = clower; c <= cupper; c++) {
            map.at(r).at(c) = true;
        }
    }
}

int solve_1(std::vector<std::string> inp) {
    std::vector<std::vector<bool>> valid_map(inp.size(), std::vector<bool>(inp.at(0).size(), 0));

    // Find all symbols and mark the surrounding valid numbers
    for (size_t r = 0; r < inp.size(); r++) {
        for (size_t c = 0; c < inp.at(r).size(); c++) {
            if (inp.at(r).at(c) == '.' || std::isdigit(inp.at(r).at(c))) {
                continue;
            }
            mark_surrounding_valid(valid_map, r, c);
        }
    }

    // parse number and add if valid
    int sum = 0;
    for (size_t r = 0; r < inp.size(); r++) {
        int number = 0;
        for (size_t c = 0; c < inp.at(r).size(); c++) {
            if (!std::isdigit(inp.at(r).at(c))) {
                continue;
            }
            // found a number, parse and check if valid
            bool valid_number = false;
            // Check range before checking element...
            for (; c < inp.at(r).size() && std::isdigit(inp.at(r).at(c)); c++) {
                number = number * 10 + inp.at(r).at(c) - '0';
                valid_number = valid_number || valid_map.at(r).at(c);
            }
            if (valid_number) {
                sum += number;
            }
            number = 0;
        }
    }
    return sum;
}

struct Gears {
    int gear_count = 0;
    std::vector<std::vector<int>> map;

    Gears(size_t rows, size_t cols) : map(rows, std::vector<int>(cols, 0)){};
    void check_if_gear(std::vector<std::string> schematic, size_t rmark, size_t cmark);
};

void Gears::check_if_gear(std::vector<std::string> schematic, size_t rmark, size_t cmark) {
    size_t rlower = rmark > static_cast<size_t>(0) ? rmark - 1 : rmark;
    size_t rupper = rmark + 1 < map.size() ? rmark + 1 : rmark;
    size_t clower = cmark > static_cast<size_t>(0) ? cmark - 1 : cmark;
    size_t cupper = cmark + 1 < map.size() ? cmark + 1 : cmark;

    int count_numbers = 0;
    for (size_t r = rlower; r <= rupper; r++) {
        for (size_t c = clower; c <= cupper; c++) {
            if (std::isdigit(schematic.at(r).at(c))) {
                count_numbers++;
                for (; c < cupper && std::isdigit(schematic.at(r).at(c)); c++) {
                }
            }
        }
    }

    // only two adjacent part numbers
    if (count_numbers != 2) {
        return;
    }

    gear_count++;
    for (size_t r = rlower; r <= rupper; r++) {
        for (size_t c = clower; c <= cupper; c++) {
            map.at(r).at(c) = gear_count;
        }
    }
}

int solve_2(std::vector<std::string> inp) {
    Gears gears(inp.size(), inp.at(0).size());

    // Find all symbols and mark the surrounding valid numbers
    for (size_t r = 0; r < inp.size(); r++) {
        for (size_t c = 0; c < inp.at(r).size(); c++) {
            if (inp.at(r).at(c) == '.' || std::isdigit(inp.at(r).at(c))) {
                continue;
            }
            gears.check_if_gear(inp, r, c);
        }
    }

    // Gear count is used as indexing, so gear 1 is on index 1 so +1 on length
    std::vector<int> gear_ratios(gears.gear_count + 1, 1);

    // parse number and add if valid
    for (size_t r = 0; r < inp.size(); r++) {
        int number = 0;
        for (size_t c = 0; c < inp.at(r).size(); c++) {
            if (!std::isdigit(inp.at(r).at(c))) {
                continue;
            }

            // found a number, parse and check if it belongs to a gear, if so multiply to gear ratio
            int gear = 0;
            for (; c < inp.at(r).size() && std::isdigit(inp.at(r).at(c)); c++) {
                number = number * 10 + inp.at(r).at(c) - '0';
                if (gears.map.at(r).at(c) > 0) {
                    gear = gears.map.at(r).at(c);
                }
            }
            if (gear > 0) {
                gear_ratios.at(gear) *= number;
            }
            number = 0;
        }
    }
    return std::accumulate(gear_ratios.cbegin() + 1, gear_ratios.cend(), 0);
}
