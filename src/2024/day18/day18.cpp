/**
 * https://adventofcode.com/2024/day/18
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
    std::unordered_map<Pos, bool, PosHash, PosEqual> obstacles_{};
    int64_t row_sz_{};
    int64_t col_sz_{};
    Pos start_{0, 0};
    Pos finish_{-1, -1};

    Grid(int64_t row, int64_t col) : row_sz_{row}, col_sz_{col}, finish_{col - 1, row - 1} {
        assert(col > 0);
        assert(row > 0);
    }

    void add_obstacle(Pos pos) { obstacles_[pos] = true; }

    char operator[](Pos pos) const {
        if (obstacles_.contains(pos)) {
            return '#';
        }
        return '.';
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
            if (!within_bounds(cand) || obstacles_.contains(cand)) {
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
    int64_t distance_{};
    Pos root_{};
    Pos finish_{};
    bool success_{false};

    BFS(Grid const& grid, Pos const root) : root_{root}, finish_{grid.finish_} {
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
        distance_ = visited_[finish_];
    }

    std::unordered_map<Pos, int, PosHash, PosEqual> generate_path() {
        if (!success_) {
            return {};
        }

        Pos current{finish_};
        path_[current];
        while (current != root_) {
            current = prev_[current];
            path_[current];
        }

        return path_;
    }
};

void print(Grid grid, std::optional<BFS> bfs = {}) {
    for (int64_t row{0}; row < grid.row_sz_; row++) {
        for (int64_t col{0}; col < grid.col_sz_; col++) {
            Pos pos{col, row};
            if (bfs.has_value() && bfs.value().path_.contains(pos)) {
                std::cout << "O";
                continue;
            }
            std::cout << grid[pos];
        }
        std::cout << std::endl;
    }
}

int64_t solve_1(std::vector<std::string> inp, bool sample = false) {
    int64_t size = 71;
    size_t bytes{1024};
    if (sample) {
        size = 7;
        bytes = 12;
    }

    Grid grid(size, size);
    for (size_t byte{0}; byte < bytes; byte++) {
        auto numbers = aoc::string::numbers_from_string(inp[byte]);
        assert(numbers.size() == 2);
        grid.add_obstacle({numbers[0], numbers[1]});
    }

    BFS bfs(grid, grid.start_);
    return bfs.distance_;
}

std::string solve_2(std::vector<std::string> inp, bool sample = false) {
    int64_t size = 71;
    size_t bytes{1024};
    if (sample) {
        size = 7;
        bytes = 12;
    }

    Grid grid(size, size);
    size_t byte{0};
    for (; byte < bytes; byte++) {
        auto numbers = aoc::string::numbers_from_string(inp[byte]);
        assert(numbers.size() == 2);
        grid.add_obstacle({numbers[0], numbers[1]});
    }

    Pos obstacle{0, 0};
    while (byte < inp.size()) {
        BFS bfs(grid, grid.start_);
        if (!bfs.success_) {
            break;
        }
        auto path = bfs.generate_path();

        // search for next obstacles that lands on path
        for (; byte < inp.size(); byte++) {
            auto numbers = aoc::string::numbers_from_string(inp[byte]);
            assert(numbers.size() == 2);
            Pos cand{numbers[0], numbers[1]};
            grid.add_obstacle(cand);

            if (path.contains(cand)) {
                obstacle = cand;
                byte++;
                break;
            }
        }
    }
    return std::to_string(obstacle.real()) + "," + std::to_string(obstacle.imag());
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, true) == 22);
    assert(solve_2(sample, true) == "6,1");
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
