#include AOC_HEADER

#include <algorithm>
#include <numeric>
#include <unordered_map>

static int solve_1(std::vector<std::string>& ids) {
    int count_2 = 0;
    int count_3 = 0;
    for (auto& id : ids) {
        std::unordered_map<char, int> letters;
        for (auto ch : id) {
            letters[ch]++;
        }
        if (std::find_if(letters.cbegin(), letters.cend(), [](const auto& it) { return 2 == it.second; }) !=
            letters.cend()) {
            ++count_2;
        }
        if (std::find_if(letters.cbegin(), letters.cend(), [](const auto& it) { return 3 == it.second; }) !=
            letters.cend()) {
            ++count_3;
        }
    }
    return count_2 * count_3;
}

static std::string solve_2(std::vector<std::string>& ids) {
    std::string out;
    std::sort(ids.begin(), ids.end());
    auto it = std::adjacent_find(ids.begin(), ids.end(), [](std::string lhs, std::string rhs) {
        int diff = std::inner_product(lhs.cbegin(), lhs.cend(), rhs.cbegin(), 0, std::plus<>(), std::not_equal_to<>());
        return diff == 1;
    });

    if (it == ids.end()) {
        return "";
    }

    std::string w1 = *it;
    std::string w2 = *++it;
    for (size_t i = 0; i < w1.size(); ++i) {
        if (w1.at(i) == w2.at(i)) {
            out.push_back(w1.at(i));
        }
    }
    return out;
}

std::pair<int, std::string> solve(std::vector<std::string>& ids) { return {solve_1(ids), solve_2(ids)}; }
