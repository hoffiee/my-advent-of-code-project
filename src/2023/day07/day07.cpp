/**
 * https://adventofcode.com/2023/day/7
 */
#include AOC_HEADER

#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <map>

#include "aoc_utils.h"
#include "string_utils.h"

enum class HandType : int {
    undetermined = 0,
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind,
};

__attribute__((unused)) static std::string HandType_to_str(HandType inp) {
    switch (inp) {
        case HandType::undetermined:
            return "HandType::undetermined";
        case HandType::high_card:
            return "HandType::high_card";
        case HandType::one_pair:
            return "HandType::one_pair";
        case HandType::two_pair:
            return "HandType::two_pair";
        case HandType::three_of_a_kind:
            return "HandType::three_of_a_kind";
        case HandType::full_house:
            return "HandType::full_house";
        case HandType::four_of_a_kind:
            return "HandType::four_of_a_kind";
        case HandType::five_of_a_kind:
            return "HandType::five_of_a_kind";
    }
    return "undetermined";
}

std::ostream& operator<<(std::ostream& os, const HandType& obj) {
    os << static_cast<std::underlying_type<HandType>::type>(obj);
    return os;
}

struct Hand {
    std::vector<int> cards;
    int bid = 0;
    HandType type = HandType::undetermined;

    Hand(std::string line, bool joker);
    bool operator<(const Hand& other) const;

   private:
    int char_to_numeric(char label, bool joker);
    void set_type();
};

bool Hand::operator<(const Hand& other) const {
    if (type == other.type) {
        assert(cards.size() == other.cards.size());
        for (size_t i = 0; i < cards.size(); i++) {
            if (cards.at(i) == other.cards.at(i)) {
                continue;
            }
            return (cards.at(i) < other.cards.at(i));
        }
    }
    return (type < other.type);
}

Hand::Hand(std::string line, bool joker) : cards(5) {
    auto input = aoc::string::split(line, ' ');
    assert(input.at(0).size() == 5);

    // Store in order given by input
    bid = std::stoi(input.at(1));
    for (size_t i = 0; i < cards.size(); i++) {
        cards.at(i) = char_to_numeric(input.at(0).at(i), joker);
    }

    set_type();
}

void Hand::set_type() {
    std::map<int, int> _cards;
    for (auto it : cards) {
        _cards[it]++;
    }

    int joker_count = 0;
    if (auto search = _cards.find(1); search != _cards.end()) {
        joker_count = search->second;
        _cards.erase(search);
    }

    auto max_count = std::max_element(_cards.begin(), _cards.end(), [](auto& lhs, const auto& rhs) {
                         return lhs.second < rhs.second;
                     })->second;

    if (max_count + joker_count == 5) {
        type = HandType::five_of_a_kind;
        return;
    }

    if (max_count + joker_count == 4) {
        type = HandType::four_of_a_kind;
        return;
    }

    int pair_count =
        static_cast<int>(std::count_if(_cards.cbegin(), _cards.cend(), [](auto elem) { return elem.second == 2; }));
    if ((std::any_of(_cards.cbegin(), _cards.cend(), [&](auto elem) { return elem.second == 3; }) &&
         std::any_of(_cards.cbegin(), _cards.cend(), [&](auto elem) { return elem.second == 2; })) ||
        (pair_count == 2 && joker_count == 1)) {
        type = HandType::full_house;
        return;
    }

    if (std::any_of(_cards.cbegin(), _cards.cend(), [&](auto elem) { return elem.second + joker_count == 3; })) {
        type = HandType::three_of_a_kind;
        return;
    }

    // If we have jokers but we aren't at 2 pairs bump it up
    if (joker_count > 0 && pair_count < 2) {
        pair_count++;
    }

    switch (pair_count) {
        case 2:
            type = HandType::two_pair;
            break;
        case 1:
            type = HandType::one_pair;
            break;
        case 0:
            type = HandType::high_card;
            break;
        default:
            throw std::logic_error("Whoopsie");
    }
}

int Hand::char_to_numeric(char label, bool joker) {
    switch (label) {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            if (joker) {
                return 1;
            }
            return 11;
        case 'T':
            return 10;
            break;
        default:
            return label - '0';
            break;
    }
    return -1;
}

static int64_t calculate_total_winnings(std::vector<Hand> hands) {
    int64_t out = 0;
    for (size_t i = 0; i < hands.size(); i++) {
        out += static_cast<int64_t>((static_cast<int64_t>(i) + 1) * hands.at(i).bid);
    }
    return out;
}

int64_t solve_1(std::vector<std::string> inp) {
    std::vector<Hand> hands;
    for (auto& line : inp) {
        hands.emplace_back(Hand(line, false));
    }

    std::sort(hands.begin(), hands.end());

    return calculate_total_winnings(hands);
}

int64_t solve_2(std::vector<std::string> inp) {
    std::vector<Hand> hands;
    for (auto& line : inp) {
        hands.emplace_back(Hand(line, true));
    }

    std::sort(hands.begin(), hands.end());

    return calculate_total_winnings(hands);
}
