#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <unordered_map>

static bool valid_passphrase_1(const std::string& passphrase) {
    std::string word;
    std::unordered_map<std::string, int> words;
    for (std::stringstream ss(passphrase); ss >> word;) {
        if (words.contains(word)) {
            return false;
        }
        words[word]++;
    }
    return true;
}

static bool valid_passphrase_2(const std::string& passphrase) {
    std::set<std::vector<char>> words;
    std::string word;
    std::stringstream ss(passphrase);
    size_t word_count = 0;
    while (ss >> word) {
        ++word_count;
        std::vector<char> chars(word.cbegin(), word.cend());
        std::sort(chars.begin(), chars.end());
        words.insert(std::move(chars));
    }
    return word_count == words.size();
}

std::pair<int, int> solve(std::vector<std::string>& input) {
    std::vector<bool> valid_passphrases_1;
    std::transform(input.cbegin(), input.cend(), std::back_inserter(valid_passphrases_1), valid_passphrase_1);

    std::vector<bool> valid_passphrases_2;
    std::transform(input.cbegin(), input.cend(), std::back_inserter(valid_passphrases_2), valid_passphrase_2);

    return {
        std::count(valid_passphrases_1.cbegin(), valid_passphrases_1.cend(), true),
        std::count(valid_passphrases_2.cbegin(), valid_passphrases_2.cend(), true),
    };
}
