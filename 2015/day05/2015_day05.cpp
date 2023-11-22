#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <unordered_map>

static bool has_three_vovels(std::string& input) {
    auto is_vovel = [](const char ch) {
        std::unordered_map<char, int> vovels{
            {'a', 0}, {'e', 0}, {'i', 0}, {'o', 0}, {'u', 0},
        };
        return vovels.contains(ch);
    };
    return 3 <= std::count_if(input.cbegin(), input.cend(), is_vovel);
}

static bool has_two_consecutive_letters(std::string& input) {
    for (size_t i = 0; i < input.size() - 1; ++i) {
        if (input.at(i) == input.at(i + 1)) {
            return true;
        }
    }
    return false;
}

static bool contains_invalid_words(std::string& input) {
    for (auto word : {"ab", "cd", "pq", "xy"}) {
        if (input.find(word) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool is_nice_string(std::string& input) {
    bool nice = has_three_vovels(input);
    if (nice) {
        nice = has_two_consecutive_letters(input);
    }
    if (nice) {
        nice = !contains_invalid_words(input);
    }
    return nice;
}

int solve_1(std::vector<std::string>& input) {
    int nice_words = 0;
    for (auto& word : input) {
        nice_words += 1 * is_nice_string(word);
    }
    return nice_words;
}

static bool contains_one_letter_that_repeats(std::string& word) {
    size_t characters = 2;
    for (size_t i = 0; i < word.size() - characters; ++i) {
        if (word.substr(i + characters).find(word.substr(i, characters)) != std::string::npos) {
            return true;
        }
    }
    return false;
}

static bool contains_two_letters_with_one_between(std::string& word) {
    for (size_t i = 0; i < word.size() - 2; ++i) {
        if (word.at(i) != word.at(i + 1) && word.at(i) == word.at(i + 2)) {
            return true;
        }
    }
    return false;
}

bool is_nice_string_2(std::string& word) {
    bool nice = contains_two_letters_with_one_between(word);
    if (nice) {
        nice = contains_one_letter_that_repeats(word);
    }
    return nice;
}

int solve_2(std::vector<std::string>& input) {
    int nice_words = 0;
    for (auto& word : input) {
        bool nice = is_nice_string_2(word);
        nice_words += 1 * nice;
    }
    return nice_words;
}
