/**
 * https://adventofcode.com/2021/day/3
 */
#include AOC_HEADER

#include <algorithm>
#include <bitset>
#include <icecream.hpp>
#include <numeric>

int solve_1(std::vector<std::string> inp) {
    int nr_of_bits = static_cast<int>(inp.at(0).size());

    std::vector<int> count(nr_of_bits, 0);
    for (auto it : inp) {
        for (int i = 0; i < nr_of_bits; i++) {
            if (it.at(i) == '1') {
                count.at(i)++;
            }
        }
    }

    std::string gamma_results;
    std::transform(count.begin(), count.end(), std::back_inserter(gamma_results),
                   [&inp](auto elem) { return elem >= static_cast<int>(inp.size() / 2) ? '1' : '0'; });
    std::string epsilon_results;
    std::transform(count.begin(), count.end(), std::back_inserter(epsilon_results),
                   [&inp](auto elem) { return elem >= static_cast<int>(inp.size() / 2) ? '0' : '1'; });

    int gamma = static_cast<int>(std::bitset<32>(gamma_results).to_ulong());
    int epsilon = static_cast<int>(std::bitset<32>(epsilon_results).to_ulong());

    return gamma * epsilon;
}

static size_t count(std::vector<std::string>& inp, size_t index) {
    size_t sum = 0;
    for (auto it : inp) {
        sum += static_cast<size_t>(it.at(index) == '1');
    }
    return sum;
}

static int filter_and_deduce(std::vector<std::string> inp,
                             std::function<char(std::vector<std::string>&, size_t)> common_char_fcn) {
    size_t index = 0;
    while (inp.size() > 1U && index < inp.at(0).size()) {
        char common_char = common_char_fcn(inp, index);
        IC(index, count(inp, index), common_char);

        inp.erase(std::remove_if(inp.begin(), inp.end(),
                                 [index, common_char](auto it) { return it.at(index) != common_char; }),
                  inp.end());

        IC(inp);
        index++;
    }
    IC(inp);

    if (inp.size() != 1u) {
        throw std::logic_error("Array should not be empty.");
    }

    return static_cast<int>(std::bitset<32>(inp.at(0)).to_ulong());
}

static char most_common(std::vector<std::string>& inp, size_t index) {
    size_t ones = count(inp, index);
    size_t zeros = inp.size() - ones;
    char common_char = '1';
    if (ones > zeros) {
        common_char = '1';
    } else if (zeros > ones) {
        common_char = '0';
    }
    return common_char;
}

static char least_common(std::vector<std::string>& inp, size_t index) {
    size_t ones = count(inp, index);
    size_t zeros = inp.size() - ones;
    char least_common_char = '0';

    if (ones < zeros) {
        least_common_char = '1';
    } else if (zeros < ones) {
        least_common_char = '0';
    }

    return least_common_char;
}

int solve_2(std::vector<std::string> inp) {
    IC(inp);

    int oxygen_generator_rating = filter_and_deduce(inp, most_common);
    int co2_scrubber_rating = filter_and_deduce(inp, least_common);
    IC(oxygen_generator_rating, co2_scrubber_rating);

    return oxygen_generator_rating * co2_scrubber_rating;
}
