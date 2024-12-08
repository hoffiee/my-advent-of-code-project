/**
 * https://adventofcode.com/2023/day/2
 *
 * This is where it would be nice to parse data and solve both parts in one go
 * but I'm ok with the current solution
 */
#include AOC_HEADER

#include <string_utils.h>

#include <algorithm>
#include <icecream.hpp>
#include <numeric>
#include <sstream>

static std::vector<int> get_counts(std::string hand) {
    int cubes = 0;
    std::string colour;

    std::vector<int> count(3, 0);
    const std::vector<char> colour_index{'r', 'g', 'b'};

    std::stringstream sshand(hand);
    while (sshand >> cubes >> colour) {
        for (size_t i = 0; i < colour_index.size(); i++) {
            if (colour.at(0) == colour_index.at(i)) {
                count.at(i) += cubes;
                break;
            }
        }
    }
    return count;
}

int solve_1(std::vector<std::string> inp) {
    int count_valid_ids = 0;
    for (auto game : inp) {
        std::stringstream ss(game);

        std::string ignore;
        int id = 0;
        ss >> ignore >> id;

        auto hands = string_utils::split_string(game.substr(game.find(":") + 2), ';');
        bool game_valid = true;
        for (auto hand : hands) {
            auto count = get_counts(hand);
            if (count.at(0) > 12 || count.at(1) > 13 || count.at(2) > 14) {
                game_valid = false;
            }
        }
        if (game_valid) {
            count_valid_ids += id;
        }
    }
    return count_valid_ids;
}

int solve_2(std::vector<std::string> inp) {
    int sum_of_sets_power = 0;
    for (auto game : inp) {
        std::stringstream ss(game);

        std::vector<int> min_cubes(3, 0);
        auto hands = string_utils::split_string(game.substr(game.find(":") + 2), ';');
        for (auto hand : hands) {
            auto count = get_counts(hand);
            for (size_t i = 0; i < min_cubes.size(); i++) {
                min_cubes.at(i) = std::max({min_cubes.at(i), count.at(i)});
            }
        }
        sum_of_sets_power += std::accumulate(min_cubes.begin(), min_cubes.end(), 1, std::multiplies<int>());
    }

    return sum_of_sets_power;
}
