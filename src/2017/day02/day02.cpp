#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

static int calculate_row_checksum_1(std::vector<int>& input) {
    int min = *std::min_element(input.cbegin(), input.cend());
    int max = *std::max_element(input.cbegin(), input.cend());
    return std::abs(max - min);
}

static int calculate_row_checksum_2(std::vector<int>& input) {
    /* TODO: Is there a way to do this a bit more with something from stl
     * algorithm? */
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 0; j < input.size(); ++j) {
            if (i == j) {
                continue;
            }

            if (input.at(i) % input.at(j) == 0) {
                return input.at(i) / input.at(j);
            }
        }
    }
    return 0;
}

std::pair<int, int> solve(std::vector<std::string> input) {
    int checksum_1 = 0;
    int checksum_2 = 0;

    for (auto& row : input) {
        std::vector<int> numbers;
        std::stringstream ss(row);
        int tmp = 0;
        while (ss >> tmp) {
            numbers.push_back(tmp);
        }

        checksum_1 += calculate_row_checksum_1(numbers);
        checksum_2 += calculate_row_checksum_2(numbers);
    }

    return {
        checksum_1,
        checksum_2,
    };
}
