/**
 * https://adventofcode.com/2024/day/20
 *
 * start of refacotring. l.334
 * end: l.225
 */
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <queue>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

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

namespace Dir {
constexpr Pos Up = {0, -1};
constexpr Pos Right = {1, 0};
constexpr Pos Down = {0, 1};
constexpr Pos Left = {-1, 0};
}  // namespace Dir

std::vector<Pos> const dirs{Dir::Up, Dir::Right, Dir::Down, Dir::Left};

struct Grid {
    std::vector<std::string> map_{};
    int64_t row_sz_{};
    int64_t col_sz_{};
    Pos start_{};
    Pos finish_{};
    Pos cheat_{};

    Grid(std::vector<std::string> inp)
        : map_{inp}, row_sz_{static_cast<int64_t>(inp.size())}, col_sz_{static_cast<int64_t>(inp.at(0).size())} {
        assert(col_sz_ > 0);
        assert(row_sz_ > 0);

        for (int64_t row{0}; row < row_sz_; row++) {
            for (int64_t col{0}; col < col_sz_; col++) {
                Pos pos{col, row};
                switch ((*this)[pos]) {
                    case 'S':
                        start_ = pos;
                        break;
                    case 'E':
                        finish_ = pos;
                        break;
                    default:
                        break;
                }
            }
        }

        assert(start_.real() != Pos{}.real());
        assert(start_.imag() != Pos{}.imag());
        assert(finish_.real() != Pos{}.real());
        assert(finish_.imag() != Pos{}.imag());

        map_.at(finish_.imag()).at(finish_.real()) = '.';
        map_.at(start_.imag()).at(start_.real()) = '.';
    }

    char operator[](Pos pos) const {
        assert(within_bounds(pos));
        return map_[pos.imag()][pos.real()];
    }

    bool within_bounds(Pos pos) const {
        if ((pos.real() < 0) || (pos.imag() < 0) || (col_sz_ <= pos.real()) || (row_sz_ <= pos.imag())) {
            return false;
        }
        return true;
    }

    std::vector<Pos> get_neighbours(Pos pos) const {
        std::vector<Pos> out{};
        for (auto dir : dirs) {
            auto cand{pos + dir};
            if (!within_bounds(cand) || (((*this)[cand] == '#') && (cand != cheat_))) {
                continue;
            }
            out.emplace_back(cand);
        }
        return out;
    }
};

struct BFS {
    std::unordered_map<Pos, int64_t, PosHash, PosEqual> visited_{};
    std::unordered_map<Pos, Pos, PosHash, PosEqual> prev_{};
    std::unordered_map<Pos, int, PosHash, PosEqual> path_{};
    Pos root_{};
    Pos finish_{};
    bool success_{false};

    BFS(Grid const& grid, Pos const root, Pos const goal) : root_{root}, finish_{goal} {
        std::queue<Pos> Q;

        visited_[root_] = 0;
        Q.push(root_);
        while (!Q.empty()) {
            auto node = Q.front();
            Q.pop();
            for (auto neighbour : grid.get_neighbours(node)) {
                if (visited_.contains(neighbour)) {
                    continue;
                }
                visited_[neighbour] = visited_[node] + 1;
                prev_[neighbour] = node;
                Q.push(neighbour);
            }
        }

        if (!visited_.contains(grid.finish_)) {
            success_ = false;
            return;
        }
        success_ = true;
    }

    std::unordered_map<Pos, int, PosHash, PosEqual> generate_path() {
        if (!success_) {
            return {};
        }
        Pos current{finish_};
        path_[current] = visited_[current];
        while (current != root_) {
            current = prev_[current];
            path_[current] = visited_[current];
        }
        return path_;
    }

    std::vector<std::tuple<Pos, int64_t>> generate_path_in_order() {
        if (!success_) {
            return {};
        }
        std::vector<std::tuple<Pos, int64_t>> path{};

        Pos current{finish_};
        path.push_back(std::make_tuple(current, visited_[current]));
        while (current != root_) {
            current = prev_[current];
            path.push_back(std::make_tuple(current, visited_[current]));
        }

        std::reverse(path.begin(), path.end());
        return path;
    }
};

void print(Grid grid, std::optional<BFS> bfs = {}) {
    for (int64_t row{0}; row < grid.row_sz_; row++) {
        for (int64_t col{0}; col < grid.col_sz_; col++) {
            Pos pos{col, row};
            if (pos == grid.cheat_) {
                std::cout << "C";
                continue;
            }
            if (bfs.has_value() && bfs.value().path_.contains(pos)) {
                std::cout << "O";
                continue;
            }
            std::cout << grid[pos];
        }
        std::cout << std::endl;
    }
}

// TODO Move to utils
int64_t manhattan_distance(Pos p1, Pos p2) { return std::abs(p2.real() - p1.real()) + std::abs(p2.imag() - p1.imag()); }

int64_t solve(std::vector<std::string> inp, int64_t distance, int64_t threshold) {
    Grid grid(inp);
    BFS bfs(grid, grid.start_, grid.finish_);
    auto path = bfs.generate_path_in_order();

    // Get obstacles next to path
    // Then rerun BFS from that position to see if it generates a shorter path
    std::unordered_map<int64_t, int64_t> saved_time_count{};
    for (auto it = path.begin(); it != path.end(); it++) {
        for (auto it_cand{it}; it_cand != path.end(); it_cand++) {
            if (it_cand == it) {
                continue;
            }

            auto current = std::get<0>(*it);
            auto current_step = std::get<1>(*it);
            auto cand = std::get<0>(*it_cand);
            auto cand_step = std::get<1>(*it_cand);

            int64_t md{manhattan_distance(current, cand)};
            if (md > distance) {
                continue;
            }

            assert(cand_step > current_step);
            int64_t old_distance = cand_step - current_step;
            if (md == old_distance) {
                continue;
            }

            if (old_distance - md < threshold) {
                continue;
            }

            saved_time_count[old_distance - md]++;
        }
    }

    int64_t count{0};
    for (auto [time, c] : saved_time_count) {
        count += c;
    }

    return count;
}

int64_t solve_1(std::vector<std::string> inp, bool sample = false) { return solve(inp, 2, (sample) ? 0 : 100); }

int64_t solve_2(std::vector<std::string> inp, bool sample = false) { return solve(inp, 20, (sample) ? 50 : 100); }

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, true) == 44);
    assert(solve_2(sample, true) == 285);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
