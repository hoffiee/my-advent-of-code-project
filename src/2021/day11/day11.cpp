/**
 * https://adventofcode.com/2021/day/11
 */
#include <array>
#include <icecream.hpp>
#include <queue>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2021::d11 {

using Pos = aoc::grid2d::Pos;
using Grid = std::vector<std::vector<int64_t>>;
using Flashed = std::vector<std::vector<bool>>;

constexpr std::array<Pos, 8> directions{
    Pos{-1, -1}, Pos{-1, 0}, Pos{-1, 1}, Pos{0, -1}, Pos{0, 1}, Pos{1, -1}, Pos{1, 0}, Pos{1, 1},
};

bool valid(Grid const& grid, Pos const& pos) {
    if (pos.x < 0 || static_cast<int64_t>(grid.at(0).size()) <= pos.x) {
        return false;
    }
    if (pos.y < 0 || static_cast<int64_t>(grid.size()) <= pos.y) {
        return false;
    }
    return true;
}

bool all_zero(Grid const& grid) {
    for (auto const& row : grid) {
        for (auto const& col : row) {
            if (col > 0) {
                return false;
            }
        }
    }
    return true;
}

Grid parse(std::vector<std::string> const& inp) {
    Grid grid(inp.size(), std::vector<int64_t>(inp.at(0).size(), 0));
    for (std::size_t row{0}; row < inp.size(); row++) {
        for (std::size_t col{0}; col < inp.size(); col++) {
            grid.at(row).at(col) = inp.at(row).at(col) - '0';
        }
    }
    return grid;
}

void reset_flashed(Grid& grid) {
    for (auto& row : grid) {
        for (auto& col : row) {
            if (col > 9) {
                col = 0;
            }
        }
    }
}

int64_t count_flashed(Flashed& flashed) {
    int64_t count{0};
    for (auto const& row : flashed) {
        for (auto const& col : row) {
            if (col) {
                count++;
            }
        }
    }
    return count;
}

void process_check_directions(std::queue<Pos>& process, Grid const& grid, Pos const& node) {
    for (auto const dir : directions) {
        Pos cand{node + dir};
        if (valid(grid, cand)) {
            process.push(cand);
        }
    }
}

void process_queue(std::queue<Pos>& process, Grid& grid, Flashed& flashed) {
    while (!process.empty()) {
        Pos const node = process.front();
        process.pop();

        grid.at(node.y).at(node.x)++;
        if (grid.at(node.y).at(node.x) <= 9) {
            continue;
        }

        if (flashed.at(node.y).at(node.x)) {
            continue;
        }

        flashed.at(node.y).at(node.x) = true;

        process_check_directions(process, grid, node);
    }
}

std::pair<std::queue<Pos>, Flashed> increment_and_flash_grid(Grid& grid) {
    std::queue<Pos> process{};
    Flashed flashed(grid.size(), std::vector<bool>(grid.at(0).size(), false));
    for (std::int64_t row{0}; row < static_cast<int64_t>(grid.size()); row++) {
        for (std::int64_t col{0}; col < static_cast<int64_t>(grid.size()); col++) {
            grid.at(row).at(col)++;
            if (grid.at(row).at(col) <= 9) {
                continue;
            }

            if (flashed.at(row).at(col)) {
                continue;
            }

            flashed.at(row).at(col) = true;

            Pos flash{col, row};
            process_check_directions(process, grid, flash);
        }
    }

    return {process, flashed};
}

int64_t solve_1(std::vector<std::string> inp, std::size_t steps) {
    Grid grid = parse(inp);

    int64_t count{0};
    for (std::size_t step{0}; step < steps; step++) {
        auto [process, flashed] = increment_and_flash_grid(grid);

        process_queue(process, grid, flashed);

        reset_flashed(grid);

        count += count_flashed(flashed);
    }
    return count;
}

int64_t solve_2(std::vector<std::string> inp, std::size_t steps) {
    Grid grid = parse(inp);

    int64_t count{0};
    for (std::size_t step{0}; step < steps; step++) {
        auto [process, flashed] = increment_and_flash_grid(grid);

        process_queue(process, grid, flashed);

        reset_flashed(grid);

        count += count_flashed(flashed);

        if (all_zero(grid)) {
            return step + 1;
        }
    }
    return 0;
}

void samples() {
    auto sample1 = aoc::utils::read_input("day11-sample-1.input");
    assert(solve_1(sample1, 1) == 9);
    assert(solve_1(sample1, 2) == 9);

    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, 1) == 0);
    assert(solve_1(sample, 2) == 35);
    assert(solve_1(sample, 3) == 35 + 45);
    assert(solve_1(sample, 4) == 35 + 45 + 16);
    assert(solve_1(sample, 5) == 35 + 45 + 16 + 8);
    assert(solve_1(sample, 6) == 35 + 45 + 16 + 8 + 1);
    assert(solve_1(sample, 7) == 35 + 45 + 16 + 8 + 1 + 7);
    assert(solve_1(sample, 8) == 35 + 45 + 16 + 8 + 1 + 7 + 24);
    assert(solve_1(sample, 9) == 35 + 45 + 16 + 8 + 1 + 7 + 24 + 39);
    assert(solve_1(sample, 10) == 35 + 45 + 16 + 8 + 1 + 7 + 24 + 39 + 29);
    assert(solve_1(sample, 100) == 1656);
    assert(solve_2(sample, 195) == 195);
}

};  // namespace aoc::y2021::d11

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2021::d11::solve_1(inp, 100);
        assert(part1 == 1793);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2021::d11::solve_2(inp, 1000);
        assert(part2 == 247);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2021::d11::samples, solve_1_wrapper, solve_2_wrapper, input);
}
