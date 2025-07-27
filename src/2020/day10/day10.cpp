/**
 * https://adventofcode.com/2020/day/10
 *
 * Assumptions and notes about input:
 * - assumption that only one valid chain that uses all adapters
 * - all adapters are unique
 */
#include <icecream.hpp>
#include <ranges>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2020::d10 {

std::pair<std::vector<int64_t>, int64_t> parse(std::vector<std::string> const& inp) {
    std::vector<int64_t> ratings{};
    int64_t max_jolt{0};
    for (auto const& line : inp) {
        ratings.push_back(std::stoi(line));
        max_jolt = std::max(max_jolt, ratings.back());
    }
    int64_t const device_rating{max_jolt + 3};
    ratings.push_back(0);
    ratings.push_back(device_rating);
    return {ratings, device_rating};
}

struct Differences {
    std::array<int64_t, 4> count_{0};
    void increment(int64_t const diff) {
        assert(0 <= diff);
        assert(diff < static_cast<int64_t>(count_.size()));
        count_[diff]++;
    }

    Differences& operator+=(Differences const& other) {
        for (std::size_t i{0}; i < count_.size(); i++) {
            count_[i] += other.count_[i];
        }
        return *this;
    }

    int64_t product() const { return count_[1] * count_[3]; }
};

std::optional<Differences> combine(int64_t target_rating, int64_t last_adapter, int64_t last_diff,
                                   std::vector<int64_t> available_ratings) {
    Differences differences{};
    differences.increment(last_diff);

    if (available_ratings.empty() && (last_adapter + 3 >= target_rating)) {
        return differences;
    }

    std::vector<int64_t> unused{};
    for (std::size_t i{0}; i < available_ratings.size(); i++) {
        int64_t diff{available_ratings.at(i) - last_adapter};
        if (diff <= 0 || 3 < diff) {
            break;
        }

        // Afterwards when going through it again, I noticed that keeping the
        // unused isn't necessary due to the problem formulation, but keeping
        // it anyways for nostalgic reasons
        std::vector<int64_t> tmp{unused};
        tmp.insert(tmp.end(), available_ratings.begin() + 1, available_ratings.end());

        auto res = combine(target_rating, available_ratings.at(i), diff, tmp);

        if (res.has_value()) {
            return differences += res.value();
        }
        // Seems that we never backtrack either...
        assert(false);

        unused.push_back(available_ratings.at(i));
    }

    return {};
}

using Cache = std::unordered_map<int64_t, int64_t>;

struct Solver {
    std::unordered_map<int64_t, int64_t> cache_{};
    std::unordered_map<int64_t, bool> available_ratings_{};

    Solver(std::vector<int64_t> const& ratings) {
        for (auto const& rating : ratings) {
            available_ratings_[rating] = true;
        }
    }

    int64_t solve(int64_t const rating) {
        if (rating == 0) {
            return 1;
        }

        if (cache_.contains(rating)) {
            return cache_[rating];
        }

        int64_t count{0};
        for (std::int64_t i{rating - 3}; i < rating; i++) {
            if (!available_ratings_.contains(i)) {
                continue;
            }
            count += solve(i);
        }

        cache_[rating] = count;

        return count;
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    auto [ratings, device_rating] = parse(inp);
#if 0
    // original solution, but after running it and seeing it solve it I noticed
    // that it never backtracked. As shown by the assert(false); in the loop.
    // So I tested just simply calculating the differences along the list of
    // sorted unique adapters which also solved it, so my dynamic programming
    // approach (or whatever it's called) feels great now..
    std::sort(ratings.begin(), ratings.end());

    auto val = combine(device_rating, 0, 0, ratings);
    assert(val.has_value());
    val.value().increment(3);
    return val.value().product();
#else
    std::sort(ratings.begin(), ratings.end());

    Differences differences{};
    for (std::size_t i{0}; i < ratings.size() - 1; i++) {
        int64_t diff = ratings.at(i + 1) - ratings.at(i);
        differences.increment(diff);
    }
    return differences.product();
#endif
}

int64_t solve_2(std::vector<std::string> inp) {
    auto [ratings, device_rating] = parse(inp);
    Solver solver{ratings};
    return solver.solve(device_rating);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 35);
    assert(solve_2(sample) == 8);

    auto sample1 = aoc::utils::read_input("day10-sample-1.input");
    assert(solve_1(sample1) == 220);
    assert(solve_2(sample1) == 19208);
}

};  // namespace aoc::y2020::d10

int main(int argc, char** argv) {
    IC_CONFIG.line_wrap_width(160);

    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2020::d10::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2020::d10::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2020::d10::samples, solve_1_wrapper, solve_2_wrapper, input);
}
