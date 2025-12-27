/**
 * https://adventofcode.com/2024/day/10
 */
#include <complex>
#include <cstdint>
#include <icecream.hpp>
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

struct Map {
    std::unordered_map<Pos, int, PosHash, PosEqual> grid_{};
    using Score = int64_t;
    std::unordered_map<Pos, Score, PosHash, PosEqual> trailheads_{};
    int sz_row_{};
    int sz_col_{};

    Map(std::vector<std::string>& inp) {
        sz_col_ = inp.at(0).size();
        sz_row_ = inp.size();

        for (int r{0}; r < static_cast<int>(inp.size()); r++) {
            for (int c{0}; c < static_cast<int>(inp.size()); c++) {
                if (inp[r][c] == '.') {
                    continue;
                }
                grid_[Pos{c, r}] = static_cast<int>(inp[r][c] - '0');

                if (inp[r][c] == '0') {
                    trailheads_[Pos{c, r}] = static_cast<int>(inp[r][c] - '0');
                }
            }
        }
    }

    std::vector<Pos> neighbours(Pos pos) const {
        std::vector<Pos> out{};
        std::vector<Pos> const dirs{
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1},
        };
        for (auto const& dir : dirs) {
            auto cand = pos + dir;
            if (grid_.contains(cand)) {
                if (grid_.at(pos) + 1 == grid_.at(cand)) {
                    out.push_back(cand);
                }
            }
        }
        return out;
    }

    friend std::ostream& operator<<(std::ostream& stream, Map& map) {
        stream << "[" << map.sz_col_ << "," << map.sz_row_ << "]" << std::endl;
        for (int r{0}; r < map.sz_row_; r++) {
            for (int c{0}; c < map.sz_row_; c++) {
                if (map.grid_.contains(Pos{c, r})) {
                    stream << map.grid_[Pos{c, r}];
                } else {
                    stream << ".";
                }
            }
            stream << std::endl;
        }
        return stream;
    }
};

struct DFS {
    // Searches for number of reachable 9, regular DFS
    std::unordered_map<Pos, bool, PosHash, PosEqual> visited_{};
    std::queue<Pos> queue_{};
    std::unordered_map<Pos, bool, PosHash, PosEqual> trails_{};

    DFS(Map const& G, Pos root) {
        visited_[root] = true;
        queue_.push(root);

        while (!queue_.empty()) {
            auto v = queue_.front();
            queue_.pop();

            if (G.grid_.at(v) == 9) {
                trails_[v] = true;
                continue;
            }

            for (auto const n : G.neighbours(v)) {
                if (!visited_.contains(n)) {
                    visited_[n] = true;
                    queue_.push(n);
                }
            }
        }
    }
};

struct DFS2 {
    // This one doesn't care how many 9 we find, it does however care about how many paths to a reachable 9 we can take.
    // So a DFS where we remove the check for already visited paths Can be optimized to keep track of which paths
    // reaches a 9, and if I end up on a node that leads to a 9, increment it. Then we can reintroduce the visited check
    // and maybe save some computation.
    std::queue<Pos> queue_{};
    std::unordered_map<Pos, int64_t, PosHash, PosEqual> trails_{};

    DFS2(Map const& G, Pos root) {
        queue_.push(root);
        while (!queue_.empty()) {
            auto v = queue_.front();
            queue_.pop();
            if (G.grid_.at(v) == 9) {
                trails_[v]++;
                continue;
            }
            for (auto const n : G.neighbours(v)) {
                queue_.push(n);
            }
        }
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Map map(inp);
    int64_t sum{0};
    for (auto const& [trailhead, score] : map.trailheads_) {
        DFS dfs(map, trailhead);
        sum += static_cast<int64_t>(dfs.trails_.size());
    }
    return sum;
}

int64_t solve_2(std::vector<std::string> inp) {
    Map map(inp);
    int64_t sum{0};
    for (auto const& [trailhead, score] : map.trailheads_) {
        DFS2 dfs(map, trailhead);
        for (auto const& [trail, score] : dfs.trails_) {
            sum += score;
        }
    }
    return sum;
}

void samples() {
    auto sample1 = aoc::utils::read_input("day10-sample-1.input");
    assert(solve_1(sample1) == 1);

    auto sample2 = aoc::utils::read_input("day10-sample-2.input");
    assert(solve_1(sample2) == 2);

    auto sample3 = aoc::utils::read_input("day10-sample-3.input");
    assert(solve_1(sample3) == 4);

    auto sample4 = aoc::utils::read_input("day10-sample-4.input");
    assert(solve_1(sample4) == 3);

    auto sample5 = aoc::utils::read_input("day10-sample-5.input");
    assert(solve_1(sample5) == 36);
    assert(solve_2(sample5) == 81);

    auto sample6 = aoc::utils::read_input("day10-sample-6.input");
    assert(solve_2(sample6) == 3);

    auto sample7 = aoc::utils::read_input("day10-sample-7.input");
    assert(solve_2(sample7) == 13);

    auto sample8 = aoc::utils::read_input("day10-sample-8.input");
    assert(solve_2(sample8) == 227);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 811);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 1794);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
