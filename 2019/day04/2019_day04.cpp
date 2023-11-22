#include AOC_HEADER

#include <icecream.hpp>

bool criteria_length(std::string inp) { return inp.size() == 6; }

bool criteria_adjacent_digits(std::string inp) {
    int count_adjacent = 0;
    for (size_t i = 0; i < inp.size() - 1; i++) {
        if (inp.at(i) == inp.at(i + 1)) {
            count_adjacent++;
        }
    }
    return count_adjacent >= 1;
}

bool criteria_monotonic_sequence(std::string inp) {
    for (size_t i = 0; i < inp.size() - 1; i++) {
        if (inp.at(i) > inp.at(i + 1)) {
            return false;
        }
    }
    return true;
}

int solve_1(int min, int max) {
    int count = 0;
    for (int i = min; i <= max; i++) {
        bool criterias_fulfilled = true;
        std::string cand = std::to_string(i);
        criterias_fulfilled = criterias_fulfilled && criteria_length(cand);
        criterias_fulfilled = criterias_fulfilled && criteria_adjacent_digits(cand);
        criterias_fulfilled = criterias_fulfilled && criteria_monotonic_sequence(cand);
        if (criterias_fulfilled) {
            count++;
        }
    }
    return count;
}

bool criteria_adjacent_digits_detailed(std::string inp) {
    int count_adjacent = 0;
    for (size_t i = 0; i < inp.size() - 1; i++) {
        // If we find adjacent digits, we count them, and if there are more
        // than two we invalidate it. if we brake out early we may miss series
        // of 4 or more or something like that.
        int count = 0;
        while (i + 1 < inp.size() && inp.at(i) == inp.at(i + 1)) {
            count++;
            i++;
        }
        count_adjacent += count == 1 ? 1 : 0;
    }
    return count_adjacent >= 1;
}

int solve_2(int min, int max) {
    int count = 0;
    for (int i = min; i <= max; i++) {
        bool criterias_fulfilled = true;
        std::string cand = std::to_string(i);
        criterias_fulfilled = criterias_fulfilled && criteria_length(cand);
        criterias_fulfilled = criterias_fulfilled && criteria_adjacent_digits(cand);
        criterias_fulfilled = criterias_fulfilled && criteria_adjacent_digits_detailed(cand);
        criterias_fulfilled = criterias_fulfilled && criteria_monotonic_sequence(cand);
        if (criterias_fulfilled) {
            count++;
        }
    }
    return count;
}
