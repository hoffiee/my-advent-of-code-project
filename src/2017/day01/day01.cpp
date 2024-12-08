#include AOC_HEADER

#include <iostream>
#include <vector>

static int sum_of_matching_digits(std::string& input, size_t step) {
    int count = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input.at(i) == input.at((i + step) % input.size())) {
            count += static_cast<int>(input.at(i) - '0');
        }
    }
    return count;
}

std::pair<int, int> solve(std::string input) {
    int count1 = sum_of_matching_digits(input, 1);
    int count2 = sum_of_matching_digits(input, input.size() / 2);

    return {
        count1,
        count2,
    };
}
