/**
 * https://adventofcode.com/2018/day/8
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

std::tuple<std::vector<int64_t>, int64_t, int64_t> parse_tree(std::vector<int64_t> numbers) {
    if (numbers.size() == 0) {
        return {};
    }
    assert(numbers.size() >= 2);

    auto nr_of_children{numbers[0]};
    auto nr_of_metadata{numbers[1]};
    int64_t node_value{0};
    int64_t sum_of_metadata{0};
    std::vector<int64_t> values{};
    std::vector<int64_t> slice(numbers.begin() + 2, numbers.end());

    for (int64_t child{0}; child < nr_of_children; child++) {
        auto [data, metadata_value, node_value] = parse_tree(slice);
        values.push_back(node_value);
        sum_of_metadata += metadata_value;
        slice = data;
    }

    std::vector<int64_t> metadata(slice.begin(), slice.begin() + nr_of_metadata);
    int64_t metadata_value = std::accumulate(metadata.cbegin(), metadata.cend(), static_cast<int64_t>(0));
    slice.erase(slice.begin(), slice.begin() + nr_of_metadata);
    if (nr_of_children == 0) {
        return {slice, sum_of_metadata + metadata_value, node_value + metadata_value};
    }

    for (auto idx : metadata) {
        if (idx - 1 < static_cast<int64_t>(values.size())) {
            node_value += values[idx - 1];
        }
    }
    return {slice, sum_of_metadata + metadata_value, node_value};
}

int64_t solve_1(std::vector<std::string> const& inp) {
    auto numbers = aoc::string::numbers_from_string(inp[0]);
    auto out = parse_tree(numbers);
    return std::get<1>(out);
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto numbers = aoc::string::numbers_from_string(inp[0]);
    auto out = parse_tree(numbers);
    return std::get<2>(out);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 138);
    assert(solve_2(sample) == 66);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_1(inp);
        assert(res == 41521);
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_2(inp);
        assert(res == 19990);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
