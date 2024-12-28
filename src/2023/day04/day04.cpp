/**
 * https://adventofcode.com/2023/day/4
 */
#include AOC_HEADER

#include <string_utils.h>

#include <cmath>
#include <icecream.hpp>
#include <numeric>
#include <unordered_map>

#include "aoc_utils.h"

struct Card {
    int id = 0;
    int win_count = 0;
    std::unordered_map<int, bool> winning_numbers;
    std::vector<int> numbers;

    Card(std::string input);

   private:
    void calculate_winning_count();
};

Card::Card(std::string input) {
    id = std::stoi(input.substr(5, 3));

    // 0: winning numbers | 1: card numbers
    auto card_numbers = aoc::string::split(input.substr(input.find(":") + 2), '|');

    {
        std::stringstream ss(card_numbers.at(0));
        int read = 0;
        while (ss >> read) {
            winning_numbers.insert({read, true});
        }
    }

    {
        std::stringstream ss(card_numbers.at(1));
        int read = 0;
        while (ss >> read) {
            numbers.push_back(read);
        }
    }
    calculate_winning_count();
}

void Card::calculate_winning_count() {
    for (auto number : numbers) {
        if (winning_numbers.contains(number)) {
            win_count++;
        }
    }
}

int solve_1(std::vector<std::string> inp) {
    int sum = 0;
    for (auto card_inp : inp) {
        Card card(card_inp);
        if (card.win_count > 0) {
            sum += static_cast<int>(std::pow(2, card.win_count - 1));
        }
    }
    return sum;
}

int solve_2(std::vector<std::string> inp) {
    std::unordered_map<size_t, Card> cards;

    for (auto card_inp : inp) {
        int id = std::stoi(card_inp.substr(5, 3));
        cards.emplace(id, Card(card_inp));
    }

    // originals, copies, size +1 to allow card id to match vector index
    std::vector<size_t> games(cards.size() + 1, 0);
    for (size_t i = 1; i < games.size(); i++) {
        for (size_t j = 1; j <= static_cast<size_t>(cards.at(i).win_count) && j < games.size(); j++) {
            // Add original + copies
            games.at(i + j) += 1 + games.at(i);
        }
    }

    return static_cast<int>(std::accumulate(games.begin() + 1, games.end(), cards.size()));
}
