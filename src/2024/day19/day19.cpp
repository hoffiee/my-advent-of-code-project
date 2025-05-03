/**
 * https://adventofcode.com/2024/day/19
 */
#include <cassert>
#include <icecream.hpp>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using StripeMap = std::unordered_map<std::string, size_t>;

// TODO avoid having the cache as a global?
std::unordered_map<std::string, int64_t> cache_{};

int64_t possible(StripeMap const& available_stripes, std::string const& pattern) {
    if (pattern.size() == 0) {
        return 1;
    }

    if (cache_.contains(pattern)) {
        return cache_[pattern];
    }

    int64_t count{0};
    for (auto [stripe, len] : available_stripes) {
        // prune cases where it's longer
        if (len > pattern.size()) {
            continue;
        }

        bool const stripe_match(pattern.compare(0, stripe.size(), stripe) == 0);
        if (!stripe_match) {
            continue;
        }

        std::string reduced{pattern.substr(len, pattern.size() - len)};
        count += possible(available_stripes, reduced);
    }
    cache_[pattern] = count;
    return count;
}

int64_t solve_1(std::vector<std::string> const& inp, bool clear_cache = true) {
    int64_t ans{0};

    if (clear_cache) {
        cache_.clear();
    }

    StripeMap available_stripes{};

    std::regex pattern(R"([a-zA-Z]+)");
    std::sregex_iterator it(inp[0].begin(), inp[0].end(), pattern);
    std::sregex_iterator end{};
    std::sregex_iterator last_match{};
    while (it != end) {
        available_stripes[it->str()] = it->str().size();
        it++;
    }

    std::vector<std::string> desired_patterns{std::next(inp.begin(), 2), inp.end()};
    for (auto const& pattern : desired_patterns) {
        if (possible(available_stripes, pattern) > 0) {
            ans++;
        }
    }

    return ans;
}

int64_t solve_2(std::vector<std::string> const& inp, bool clear_cache = true) {
    int64_t ans{0};
    if (clear_cache) {
        cache_.clear();
    }

    StripeMap available_stripes{};

    // TODO move to string utils
    std::regex pattern(R"([a-zA-Z]+)");
    std::sregex_iterator it(inp[0].begin(), inp[0].end(), pattern);
    std::sregex_iterator end{};

    std::sregex_iterator last_match{};
    while (it != end) {
        available_stripes[it->str()] = it->str().size();
        it++;
    }
    std::vector<std::string> desired_patterns{std::next(inp.begin(), 2), inp.end()};
    for (auto const& pattern : desired_patterns) {
        ans += possible(available_stripes, pattern);
    }
    return ans;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 6);
    assert(solve_2(sample) == 16);

    auto sample1 = aoc::utils::read_input("day19-sample-1.input");
    assert(solve_1(sample1) == 1);
    assert(solve_2(sample1) == 1);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp, false) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
