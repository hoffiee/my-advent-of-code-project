/**
 * https://adventofcode.com/2017/day/11
 *
 * aoc_tags: hex grid, flat topped, axial coordinates
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

struct HexTile {
    int64_t q_{};
    int64_t r_{};

    static std::unordered_map<std::string, HexTile> dirs;

    HexTile() = default;
    HexTile(int64_t q, int64_t r) : q_(q), r_(r){};

    int64_t distance(HexTile const& tile) const {
        return std::max({std::abs(q_ - tile.q_), std::abs(r_ - tile.r_), std::abs((q_ + r_) - (tile.q_ + tile.r_))});
    };

    HexTile& operator+=(HexTile const& tile) {
        q_ += tile.q_;
        r_ += tile.r_;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, HexTile const& ht) {
        os << ht.q_ << ":" << ht.r_;
        return os;
    }
};

// TODO: Euf, I don't like this. Probably better to set as a property of Hexgrid
std::unordered_map<std::string, HexTile> HexTile::dirs{{"n", {0, -1}},  {"s", {0, 1}},  {"ne", {1, -1}},
                                                       {"nw", {-1, 0}}, {"se", {1, 0}}, {"sw", {-1, 1}}};

struct HexTileHash {
    std::size_t operator()(const HexTile& ht) const { return std::hash<int>()(ht.q_) ^ (std::hash<int>()(ht.r_) << 8); }
};

struct HexTileEqual {
    bool operator()(HexTile const& lhs, HexTile const& rhs) const { return lhs.q_ == rhs.q_ && lhs.r_ == rhs.r_; }
};

struct HexGrid {
    std::unordered_map<HexTile, int64_t, HexTileHash, HexTileEqual> grid_{};
    HexTile current_{};

    HexGrid() = default;

    void move(std::string dir) {
        assert(HexTile::dirs.contains(dir));
        current_ += HexTile::dirs[dir];

        int64_t const distance{current_.distance({0, 0})};
        grid_[current_] = distance;
    }
};

int64_t solve_1(std::vector<std::string> const& inp) {
    auto steps = aoc::string::split(inp[0], ',');
    HexGrid grid{};
    for (auto const& step : steps) {
        grid.move(step);
    }
    return grid.current_.distance({0, 0});
}

int64_t solve_2(std::vector<std::string> const& inp) {
    auto steps = aoc::string::split(inp[0], ',');
    HexGrid grid{};
    for (auto const& step : steps) {
        grid.move(step);
    }
    int64_t max{0};
    for (auto const& [_, dist] : grid.grid_) {
        if (dist > max) {
            max = dist;
        }
    }
    return max;
}

void samples() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 3);
    assert(solve_2(sample) == 3);

    auto sample1 = string_utils::read_input("day11-sample-1.input");
    assert(solve_1(sample1) == 0);
    assert(solve_2(sample) == 3);

    auto sample2 = string_utils::read_input("day11-sample-2.input");
    assert(solve_1(sample2) == 2);
    assert(solve_2(sample) == 3);

    auto sample3 = string_utils::read_input("day11-sample-3.input");
    assert(solve_1(sample3) == 3);
    assert(solve_2(sample) == 3);
}

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp);
        assert(part1 == 705);
        std::cout << "part 1: " << part1 << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp);
        assert(part2 == 1469);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
