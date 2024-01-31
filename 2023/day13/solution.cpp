/**
 * https://adventofcode.com/2023/day/13
 *
 * p2: 37416 - correct! but I'm not getting that anymore, so somewhere in my
 * refactoring I broke this.. So there's some edgecase I'm not testing.
 */
#include AOC_HEADER

#include <icecream.hpp>
#include <bitset>

// static int find_reflection_point(std::vector<int> inp) {
//     // Reflection that reaches the wall, I assume that there may be larger
//     // reflections that isn't valid in the input
//     ssize_t reflection_point = 0;
//     for (ssize_t i = 0; i < static_cast<ssize_t>(inp.size()) - 1; i++) {
//         if (inp[static_cast<size_t>(i)] == inp[static_cast<size_t>(i + 1)]) {
//             bool reflection = true;
//             // search outwards
//             for (ssize_t j = 1; 0 <= i - j && i + j + 1 < static_cast<ssize_t>(inp.size()); j++) {
//                 if (inp[static_cast<size_t>(i - j)] != 
//                         inp[static_cast<size_t>(i + j + 1)]) {
//                     reflection = false;
//                     break;
//                 }
// 
//             }
//             if (reflection) {
//                 reflection_point = i + 1;
//                 break;
//             }
//         }
//     }
//     return static_cast<int>(reflection_point);
// }

static int hamming_distance(int lhs, int rhs) {
    int x = lhs ^ rhs;
    std::bitset<64> bits(static_cast<unsigned long long>(x));
    return static_cast<int>(bits.count());
}

static std::pair<int, bool> find_reflection_point(std::vector<int> inp, bool fix_smudge) {
    // Reflection that reaches the wall, I assume that there may be larger
    // reflections that isn't valid in the input
    ssize_t reflection_point = 0;
    bool fixed_smudge = !fix_smudge;
    for (ssize_t i = 0; i < static_cast<ssize_t>(inp.size()) - 1; i++) {
        if (hamming_distance(inp[static_cast<size_t>(i)], inp[static_cast<size_t>(i + 1)]) <= (fix_smudge ? 1 : 0)) {
            bool reflection = true;
            int smudges = 0;
            // search outwards
            for (ssize_t j = 0; 0 <= i - j && i + j + 1 < static_cast<ssize_t>(inp.size()); j++) {
                int distance = hamming_distance(inp[static_cast<size_t>(i - j)], inp[static_cast<size_t>(i + j + 1)]);
                if (distance == 0) {
                    continue;
                }

                if (fix_smudge && distance == 1) {
                    smudges++;
                }

                if (smudges > 1 || distance > (fix_smudge ? 1 : 0)) {
                    reflection = false;
                    break;
                }
            }
            // Only care about one fixed smudge when we are looking for an allowed distance range
            if (smudges == 1) {
                fixed_smudge = true;
            }
            if (reflection && fixed_smudge) {
                reflection_point = i + 1;
                break;
            }
        }
    }
    return {static_cast<int>(reflection_point), fixed_smudge};
}

static std::tuple<std::vector<int>, std::vector<int>> parse_data(std::vector<std::string> inp) {
    std::vector<int> horizontal;
    for (auto& row: inp) {
        int val = 0;
        for (size_t i = 0; i < row.size(); i++) {
            val <<= 1;
            val += row.at(i) == '#' ? 1 : 0;
        }
        horizontal.push_back(val);
    }
    // IC(horizontal);

    std::vector<int> vertical;
    for (size_t i = 0; i < inp.at(0).size(); i++) {
        int val = 0;
        for (size_t j = 0; j < inp.size(); j++) {
            val <<= 1;
            val += inp[j][i] == '#' ? 1 : 0;
        }
        vertical.push_back(val);
    }
    // IC(vertical);

    return {horizontal, vertical};
}

int solve_1(std::vector<std::string> inp) {
    int count_columns = 0;
    int count_rows = 0;
    auto start = inp.begin();
    for (auto it = inp.begin(); it != inp.end(); it++) {
        if (*it == "") {
            start++;
            continue;
        }

        // Find the end of this block
        for (; it != inp.end() - 1 && *(it+1) != ""; it++) {
        }

        std::vector<std::string> tmp = std::vector<std::string>(start, it + 1);
        IC(tmp);

        auto [horizontal, vertical] = parse_data(tmp);
        auto [count_horizontal, ignore1] = find_reflection_point(horizontal, false);
        auto [count_vertical, ignore2] = find_reflection_point(vertical, false);
        IC(count_horizontal, count_vertical);

        if (count_horizontal > 0 && count_vertical) {
            throw std::logic_error("both shouldn't be positive!");
        }

        if (count_vertical > count_horizontal) {
            count_columns += count_vertical;
        }
        else {
            count_rows += count_horizontal;
        }

        start = it + 1;
    }
    // IC(count_columns, count_rows);

    return count_columns + 100*count_rows;
}

int solve_2(std::vector<std::string> inp) {
    icecream::ic.enable();

    int count_columns = 0;
    int count_rows = 0;
    auto start = inp.begin();
    for (auto it = inp.begin(); it != inp.end(); it++) {
        if (*it == "") {
            start++;
            continue;
        }

        // Find the end of this block
        for (; it != inp.end() - 1 && *(it+1) != ""; it++) {
        }

        std::vector<std::string> tmp = std::vector<std::string>(start, it + 1);
        IC(tmp);

        auto [horizontal, vertical] = parse_data(tmp);
        IC(horizontal, vertical);

        auto [count_horizontal, fixed_horizontal] = find_reflection_point(horizontal, true);
        IC(count_horizontal, fixed_horizontal);
        auto [count_vertical, fixed_vertical] = find_reflection_point(vertical, true);
        IC(count_vertical, fixed_vertical);

        if (count_horizontal == 0 && count_vertical == 0) {
            throw std::logic_error("both should be positive!");
        }

        if ((count_horizontal > 0 && fixed_horizontal) && (count_vertical > 0 && fixed_vertical)) {
            throw std::logic_error("both shouldn't be true!");
        }

        if (count_horizontal > 0 && fixed_horizontal) {
            count_rows += count_horizontal;
        }
        else if (count_vertical > 0 && fixed_vertical) {
            count_columns += count_vertical;
        }
        else {
            throw std::logic_error("no case fulfilled.");
            // count_rows += count_horizontal_smudge;
            // count_columns += count_vertical_smudge;

        }

        start = it + 1;
    }
    IC(count_columns, count_rows);

    return count_columns + 100*count_rows;

    return 0;
}
