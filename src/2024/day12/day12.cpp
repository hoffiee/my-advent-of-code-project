/**
 * https://adventofcode.com/2024/day/12
 *
 * aoc_tags: flood fill, 2d grid, count sides of 2d object
 */
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdint>
#include <icecream.hpp>
#include <list>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using Pos = std::complex<int>;

struct PosHash {
    std::size_t operator()(const Pos& c) const {
        return std::hash<int>()(c.real()) ^ (std::hash<int>()(c.imag()) << 8);
    }
};

struct PosEqual {
    bool operator()(Pos const& lhs, Pos const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

struct Region {
    char type_{'0'};
    std::unordered_map<Pos, int, PosHash, PosEqual> positions_{};
    int64_t perimeter_{};

    Region() = default;
    Region(char type) : type_{type} {};

    int64_t get_area() const { return static_cast<int64_t>(positions_.size()); };

    int64_t get_perimeter() const { return perimeter_; };

    int64_t count_sides() const {
        std::unordered_map<Pos, int, PosHash, PosEqual> corners{};
        int64_t sides{};
        for (auto entry : positions_) {
            auto node = std::get<0>(entry);

            // Expand and iterate around corner of a box, so center point of the box is at uneven numbers, and corners
            // will end up with even numbers.
            node *= 2;
            node += Pos{1, 1};
            std::vector<Pos> const dirs{{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
            for (auto dir : dirs) {
                corners[node + dir]++;
            }
        }

        for (auto [corner_candidate, count] : corners) {
            switch (count) {
                case 1:
                case 3:
                    // If we find 1 or 3 blocks, there are 1 corner
                    sides++;
                    break;
                case 2: {
                    // 2 blocks, we need to figure out if they are adjacent. Find the blocks that are part of the corner
                    // and mark with true.
                    std::vector<bool> setup(4, false);
                    std::vector<Pos> const dirs{{-1, -1}, {0, -1}, {-1, 0}, {0, 0}};
                    for (size_t i{0}; i < 4; i++) {
                        auto corner_adj = corner_candidate / 2 + dirs[i];
                        if (positions_.contains(corner_adj)) {
                            setup[i] = true;
                        }
                    }
                    if (setup[0] == setup[3] && setup[1] == setup[2]) {
                        sides += 2;
                    }
                    break;
                }
                case 4:
                    break;
                default:
                    assert(false);
                    break;
            }
        }
        return sides;
    }
};

struct Grid {
    std::vector<std::string> map_{};
    std::unordered_map<Pos, bool, PosHash, PosEqual> visited_{};
    int row_sz_{};
    int col_sz_{};

    Grid(std::vector<std::string> const& inp)
        : row_sz_{static_cast<int>(inp.size())}, col_sz_{static_cast<int>(inp.at(0).size())} {
        for (auto line : inp) {
            map_.push_back(line);
        }
    }

    char operator[](Pos pos) const { return map_.at(pos.imag()).at(pos.real()); }

    bool within_bounds(Pos pos) const {
        if ((pos.real() < 0) || (pos.imag() < 0) || (static_cast<int>(map_.at(0).size()) <= pos.real()) ||
            (static_cast<int>(map_.size()) <= pos.imag())) {
            return false;
        }
        return true;
    }

    std::vector<Pos> get_neighbours(Pos pos, char type) const {
        std::vector<Pos> neighbours{};
        std::vector<Pos> const dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto dir : dirs) {
            if (!within_bounds(pos + dir)) {
                continue;
            }
            auto neighbour = pos + dir;
            if ((*this)[neighbour] == type) {
                neighbours.emplace_back(neighbour);
            }
        }
        return neighbours;
    }

    Region get_region(Pos start) {
        if (visited_[start]) {
            return Region{};
        }

        Region reg{(*this)[start]};
        std::queue<Pos> Q{};
        reg.positions_[start];
        visited_[start] = true;

        Q.push(start);
        while (!Q.empty()) {
            auto node = Q.front();
            Q.pop();

            auto neighbours = get_neighbours(node, reg.type_);
            reg.perimeter_ += static_cast<int64_t>(4 - neighbours.size());
            for (auto neighbour : neighbours) {
                if (visited_[neighbour]) {
                    continue;
                }
                visited_[neighbour] = true;
                Q.push(neighbour);
                reg.positions_[neighbour];
            }
        }
        return reg;
    };
};

int64_t solve_1(std::vector<std::string> inp) {
    Grid grid(inp);
    int64_t sum{};
    for (int row{0}; row < grid.row_sz_; row++) {
        for (int col{0}; col < grid.col_sz_; col++) {
            auto reg{grid.get_region(Pos{col, row})};
            if (reg.type_ == '0') {
                continue;
            }
            sum += reg.get_area() * reg.get_perimeter();
        }
    }
    return sum;
}

int64_t solve_2(std::vector<std::string> inp) {
    Grid grid(inp);
    int64_t sum{0};
    for (int row{0}; row < grid.row_sz_; row++) {
        for (int col{0}; col < grid.col_sz_; col++) {
            auto reg{grid.get_region(Pos{col, row})};
            if (reg.type_ == '0') {
                continue;
            }
            auto sides{reg.count_sides()};
            sum += reg.get_area() * sides;
        }
    }
    return sum;
}

void samples() {
    auto sample1 = aoc::utils::read_input("day12-sample-1.input");
    assert(solve_1(sample1) == 140);
    assert(solve_2(sample1) == 80);

    auto sample2 = aoc::utils::read_input("day12-sample-2.input");
    assert(solve_1(sample2) == 772);
    assert(solve_2(sample2) == 436);

    auto sample3 = aoc::utils::read_input("day12-sample-3.input");
    assert(solve_1(sample3) == 1930);
    assert(solve_2(sample3) == 1206);

    auto sample4 = aoc::utils::read_input("day12-sample-4.input");
    assert(solve_2(sample4) == 236);

    auto sample5 = aoc::utils::read_input("day12-sample-5.input");
    assert(solve_2(sample5) == 368);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 1437300);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 849332);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
