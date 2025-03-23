/**
 * https://adventofcode.com/2015/day/14
 *
 * aoc_tags: simulation
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
#include "string_utils.h"

namespace aoc::y2015::d14 {

int64_t solve_1(std::vector<std::string> const& inp, int64_t seconds) {
    int64_t longest_distance{0};
    for (auto const& line : inp) {
        auto const numbers = string_utils::numbers_from_string(line);
        assert(numbers.size() == 3);
        int64_t speed{numbers.at(0)};
        int64_t travel_time{numbers.at(1)};
        int64_t rest_time{numbers.at(2)};
        int64_t chunk_time{travel_time + rest_time};
        int64_t nr_full_chunks{seconds / (travel_time + rest_time)};
        int64_t time_left{seconds - chunk_time * nr_full_chunks};
        int64_t partial_travel_time{std::min(travel_time, time_left)};
        int64_t distance{speed * (travel_time * nr_full_chunks + partial_travel_time)};
        if (distance > longest_distance) {
            longest_distance = distance;
        }
    }
    return longest_distance;
}

struct Reindeer {
    int64_t speed_{};
    int64_t travel_time_{};
    int64_t rest_time_{};
    int64_t chunk_time_{};
    int64_t distance_{0};
    int64_t score_{0};

    Reindeer(int64_t speed, int64_t travel_time, int64_t rest_time)
        : speed_{speed}, travel_time_{travel_time}, rest_time_{rest_time}, chunk_time_{travel_time + rest_time} {}

    int64_t distance() const { return distance_; }

    int64_t simulate(int64_t second) {
        int64_t nr_full_chunks{second / (chunk_time_)};
        int64_t time_left{second - chunk_time_ * nr_full_chunks};
        int64_t partial_travel_time{std::min(travel_time_, time_left)};
        distance_ = speed_ * (travel_time_ * nr_full_chunks + partial_travel_time);
        return distance_;
    }

    void one_point() { score_++; }
    int64_t score() const { return score_; }

    friend std::ostream& operator<<(std::ostream& os, Reindeer const& r) {
        os << r.speed_ << "," << r.travel_time_ << "," << r.rest_time_;
        return os;
    }
};

int64_t solve_2(std::vector<std::string> const& inp, int64_t seconds) {
    std::vector<Reindeer> reindeers{};
    for (auto const& line : inp) {
        auto const numbers = string_utils::numbers_from_string(line);
        assert(numbers.size() == 3);
        reindeers.emplace_back(Reindeer{numbers.at(0), numbers.at(1), numbers.at(2)});
    }

    for (int64_t second{1}; second <= seconds; second++) {
        int64_t furthest{0};
        for (auto& reindeer : reindeers) {
            int64_t cand{reindeer.simulate(second)};
            if (cand > furthest) {
                furthest = cand;
            }
        }
        for (auto& reindeer : reindeers) {
            if (furthest == reindeer.distance()) {
                reindeer.one_point();
            }
        }
    }

    int64_t max_score{0};
    for (auto const& reindeer : reindeers) {
        if (auto cand = reindeer.score(); cand > max_score) {
            max_score = cand;
        }
    }

    return max_score;
}

void samples() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, 1000) == 1120);
    assert(solve_2(sample, 1000) == 689);
}

}  // namespace aoc::y2015::d14

using namespace aoc::y2015::d14;
int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp, 2503);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp, 2503);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
