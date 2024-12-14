/**
 * https://adventofcode.com/2023/day/10
 *
 * aoc_tags: 2d grid, BFS, count inside loop
 *
 * Saw some alternatives for this one, either count edges to be inside outside on each row. Also saw some mentions of
 * the shoelace formula, but didn't look into that one.
 */
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <queue>
#include <string>
#include <vector>

#include "string_utils.h"

using Pos = std::complex<int64_t>;

struct PosHash {
    std::size_t operator()(const Pos& col) const {
        return std::hash<int>()(col.real()) ^ (std::hash<int>()(col.imag()) << 8);
    }
};

struct PosEqual {
    bool operator()(Pos const& lhs, Pos const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

namespace Dir {
constexpr Pos North{0, -1};
constexpr Pos East{1, 0};
constexpr Pos South{0, 1};
constexpr Pos West{-1, 0};
};  // namespace Dir

struct Grid {
    std::vector<std::string> map_{};
    int64_t row_sz_{};
    int64_t col_sz_{};
    Pos start_{};

    // NOTE! This is order sensitive as the comparison to change the start character needs to come out in the same order
    // as these would be produced!
    std::unordered_map<char, std::vector<Pos>> const dirs_{
        {'|', {Dir::North, Dir::South}}, {'-', {Dir::East, Dir::West}},  {'L', {Dir::North, Dir::East}},
        {'J', {Dir::North, Dir::West}},  {'7', {Dir::South, Dir::West}}, {'F', {Dir::East, Dir::South}},
    };

    Grid(std::vector<std::string> const& inp)
        : row_sz_{static_cast<int64_t>(inp.size())}, col_sz_{static_cast<int64_t>(inp.at(0).size())} {
        for (auto line : inp) {
            map_.push_back(line);
        }

        bool changed{false};
        for (int64_t row{0}; row < row_sz_; row++) {
            for (int64_t col{0}; col < col_sz_; col++) {
                if (map_[row][col] == 'S') {
                    start_ = Pos{col, row};

                    std::vector<Pos> connected_to{};
                    if (within_bounds(start_ + Dir::North) &&
                        std::string{"|7F"}.find((*this)[start_ + Dir::North]) != std::string::npos) {
                        connected_to.emplace_back(Dir::North);
                    }
                    if (within_bounds(start_ + Dir::East) &&
                        std::string{"-J7"}.find((*this)[start_ + Dir::East]) != std::string::npos) {
                        connected_to.emplace_back(Dir::East);
                    }
                    if (within_bounds(start_ + Dir::South) &&
                        std::string{"|LJ"}.find((*this)[start_ + Dir::South]) != std::string::npos) {
                        connected_to.emplace_back(Dir::South);
                    }
                    if (within_bounds(start_ + Dir::West) &&
                        std::string{"-LF"}.find((*this)[start_ + Dir::West]) != std::string::npos) {
                        connected_to.emplace_back(Dir::West);
                    }
                    assert(connected_to.size() == 2);

                    for (auto ch : std::string("|-JL7F")) {
                        if (connected_to == dirs_.at(ch)) {
                            map_[row][col] = ch;
                            changed = true;
                        }
                    }
                }
            }
        }
        // S must be replaced to it's proper character for part 2 to work.
        assert(changed);
    }

    char operator[](Pos pos) const { return map_.at(pos.imag()).at(pos.real()); }

    bool within_bounds(Pos pos) const {
        if ((pos.real() < 0) || (pos.imag() < 0) || (static_cast<int>(map_.at(0).size()) <= pos.real()) ||
            (static_cast<int>(map_.size()) <= pos.imag())) {
            return false;
        }
        return true;
    }

    std::vector<Pos> get_neighbours(Pos pos) const {
        if (dirs_.contains((*this)[pos])) {
            std::vector<Pos> out(2, pos);
            for (size_t i{0}; i < out.size(); i++) {
                out[i] += dirs_.at((*this)[pos])[i];
            }
            return out;
        }
        return {};
    }
};

struct BFS {
    std::unordered_map<Pos, int, PosHash, PosEqual> visited_{};
    int64_t distance_{};

    BFS(Grid const& grid, Pos const root) {
        std::queue<Pos> Q;

        visited_[root] = 0;
        Q.push(root);
        while (!Q.empty()) {
            auto node = Q.front();
            Q.pop();
            for (auto neighbour : grid.get_neighbours(node)) {
                if (visited_.contains(neighbour)) {
                    continue;
                }
                visited_[neighbour] = visited_[node] + 1;
                Q.push(neighbour);
            }
        }
        for (auto const& [node, steps] : visited_) {
            if (steps > distance_) {
                distance_ = steps;
            }
        }
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Grid grid(inp);
    return BFS(grid, grid.start_).distance_;
}

int64_t solve_2(std::vector<std::string> inp) {
    Grid grid(inp);
    BFS bfs(grid, grid.start_);
    std::unordered_map<Pos, int, PosHash, PosEqual> contained{};

    for (int64_t row{0}; row < grid.row_sz_; row++) {
        bool within{false};
        for (int64_t col{0}; col < grid.col_sz_; col++) {
            Pos node{col, row};
            if (bfs.visited_.contains(node)) {
                if (std::string{"|LJ"}.find(grid[node]) != std::string::npos) {
                    within = !within;
                }
            } else if (within) {
                contained[node]++;
            }
        }
    }
    return static_cast<int64_t>(contained.size());
}

int main() {
    auto sample1 = string_utils::read_input("day10-sample-1.input");
    assert(solve_1(sample1) == 4);

    auto sample2 = string_utils::read_input("day10-sample-2.input");
    assert(solve_1(sample2) == 4);

    auto sample3 = string_utils::read_input("day10-sample-3.input");
    assert(solve_1(sample3) == 8);

    auto sample4 = string_utils::read_input("day10-sample-4.input");
    assert(solve_1(sample4) == 8);

    auto input = string_utils::read_input(AOC_INPUT);
    auto part1 = solve_1(input);

    auto sample5 = string_utils::read_input("day10-sample-5.input");
    assert(solve_2(sample5) == 4);

    auto sample6 = string_utils::read_input("day10-sample-6.input");
    assert(solve_2(sample6) == 4);

    auto sample7 = string_utils::read_input("day10-sample-7.input");
    assert(solve_2(sample7) == 8);

    auto sample8 = string_utils::read_input("day10-sample-8.input");
    assert(solve_2(sample8) == 10);

    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
