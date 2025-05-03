/**
 * https://adventofcode.com/2019/day/10
 *
 * aoc_tags: 2d grid, line of sight
 */
#include <algorithm>
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <map>
#include <numbers>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "intcode_computer.h"

namespace aoc::y2019::d10 {

// TODO Move to helper and create a template? feels like I can reduce it quite alot given the amount of grid problems
using Pos = std::complex<int64_t>;

struct PosHash {
    std::size_t operator()(const Pos& c) const {
        return std::hash<int64_t>()(c.real()) ^ (std::hash<int64_t>()(c.imag()) << 8);
    }
};

struct PosEqual {
    bool operator()(Pos const& lhs, Pos const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

using Asteroids = std::unordered_map<Pos, int64_t, PosHash, PosEqual>;

Asteroids parse_input(std::vector<std::string> const& inp) {
    Asteroids asteroids{};
    for (int64_t y{0}; y < static_cast<int64_t>(inp.size()); y++) {
        for (int64_t x{0}; x < static_cast<int64_t>(inp.at(0).size()); x++) {
            if (inp[y][x] == '#') {
                asteroids[Pos(x, y)];
            }
        }
    }
    return asteroids;
}

std::tuple<Pos, int64_t> find_location(Asteroids const& asteroids) {
    int64_t max{0};
    Pos location{};
    for (auto const& [asteroid, _] : asteroids) {
        std::unordered_map<double, std::tuple<Pos, int64_t>> line_of_sight{};
        for (auto const& [asteroid_cand, _] : asteroids) {
            if (asteroid == asteroid_cand) {
                continue;
            }
            auto ydiff = asteroid.imag() - asteroid_cand.imag();
            auto xdiff = asteroid.real() - asteroid_cand.real();
            auto angle = std::atan2(ydiff, xdiff);
            line_of_sight[angle] = std::make_tuple(asteroid_cand, ydiff * ydiff + xdiff * xdiff);
        }
        if (static_cast<int64_t>(line_of_sight.size()) > max) {
            max = static_cast<int64_t>(line_of_sight.size());
            location = asteroid;
        }
    }
    return {location, max};
}

int64_t solve_1(std::vector<std::string> const& inp) {
    auto const asteroids = parse_input(inp);
    auto const [pos, count] = find_location(asteroids);
    return count;
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto const asteroids = parse_input(inp);
    auto const [location, _] = find_location(asteroids);
    std::map<double, std::vector<std::tuple<Pos, int64_t>>> line_of_sight{};
    for (auto const& [asteroid_cand, _] : asteroids) {
        if (location == asteroid_cand) {
            continue;
        }
        // By flipping to angle from asteroid_cand to location we get clockwise movement for free
        auto ydiff = location.imag() - asteroid_cand.imag();
        auto xdiff = location.real() - asteroid_cand.real();
        auto angle = std::atan2(ydiff, xdiff);
        // Rotate s.t. upwards becomes 0 rad
        angle -= std::numbers::pi_v<double> / 2.0;
        // shove all negative into a positive so that the ordered map will handle negative after positive ones
        if (angle < 0) {
            angle += 2.0 * std::numbers::pi_v<double>;
        }
        line_of_sight[angle].emplace_back(std::make_tuple(asteroid_cand, ydiff * ydiff + xdiff * xdiff));
    }

    // sort all headings by distance
    for (auto& [_, targets] : line_of_sight) {
        std::sort(targets.begin(), targets.end(),
                  [](auto const& lhs, auto const& rhs) { return std::get<1>(lhs) < std::get<1>(rhs); });
    }

    int count{0};
    for (auto& [heading, targets] : line_of_sight) {
        if (targets.empty()) {
            continue;
        }
        if (++count == 200) {
            auto target_pos = std::get<0>(targets.front());
            int64_t out{target_pos.real() * 100 + target_pos.imag()};
            return out;
        }

        targets.erase(targets.begin());
    }
    return 0;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 8);

    auto sample1 = aoc::utils::read_input("day10-sample-1.input");
    assert(solve_1(sample1) == 33);

    auto sample2 = aoc::utils::read_input("day10-sample-2.input");
    assert(solve_1(sample2) == 35);

    auto sample3 = aoc::utils::read_input("day10-sample-3.input");
    assert(solve_1(sample3) == 41);

    auto sample4 = aoc::utils::read_input("day10-sample-4.input");
    assert(solve_1(sample4) == 210);
    assert(solve_2(sample4) == 802);
}

};  // namespace aoc::y2019::d10

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d10::solve_1(inp);
        assert(part1 == 286);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d10::solve_2(inp);
        assert(part2 == 504);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d10::samples, solve_1_wrapper, solve_2_wrapper, input);
}
