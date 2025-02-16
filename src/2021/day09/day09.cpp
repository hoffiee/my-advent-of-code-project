/**
 * https://adventofcode.com/2021/day/9
 */
#include <cstdint>
#include <icecream.hpp>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

using Pos = std::pair<size_t, size_t>;
using Grid = std::vector<std::vector<int>>;

Grid create_grid(std::vector<std::string> const& inp) {
    Grid grid(inp.size() + 2, std::vector<int>(inp.front().size() + 2, 9));
    for (size_t row{0}; row < inp.size(); row++) {
        for (size_t col{0}; col < inp.at(row).size(); col++) {
            grid[row + 1][col + 1] = inp.at(row).at(col) - '0';
        }
    }
    return grid;
}

std::vector<Pos> get_low_points(Grid const& grid) {
    std::vector<Pos> out{};
    for (size_t row{1}; row < grid.size() - 1; row++) {
        for (size_t col{1}; col < grid.at(row).size() - 1; col++) {
            auto cand = grid.at(row).at(col);
            if (cand < grid.at(row - 1).at(col) && cand < grid.at(row + 1).at(col) && cand < grid.at(row).at(col - 1) &&
                cand < grid.at(row).at(col + 1)) {
                out.push_back(std::make_pair(row, col));
            }
        }
    }
    return out;
}

int64_t solve_1(std::vector<std::string> inp) {
    auto grid = create_grid(inp);
    auto low_points = get_low_points(grid);
    int64_t count{0};
    for (auto const& point : low_points) {
        count += 1 + grid.at(std::get<0>(point)).at(std::get<1>(point));
    }
    return count;
}

std::vector<Pos> get_neighbours(Grid const& grid, Pos curr) {
    std::vector<Pos> out{};
    std::vector<Pos> candidates{
        Pos{std::get<0>(curr) + 1u, std::get<1>(curr)}, Pos{std::get<0>(curr) - 1u, std::get<1>(curr)},
        Pos{std::get<0>(curr), std::get<1>(curr) + 1u}, Pos{std::get<0>(curr), std::get<1>(curr) - 1u}};
    for (auto const& cand : candidates) {
        if (grid.at(std::get<0>(cand)).at(std::get<1>(cand)) == 9) {
            continue;
        }
        out.push_back(cand);
    }
    return out;
}

// Iterative: https://en.wikipedia.org/wiki/Depth-first_search
int64_t DFS(Grid const& G, Pos root) {
    std::vector<std::vector<bool>> visited(G.size(), std::vector<bool>(G.front().size(), false));
    int64_t count{0};
    std::stack<Pos> S{};
    S.push(root);
    while (!S.empty()) {
        Pos v = S.top();
        S.pop();
        if (!visited[std::get<0>(v)][std::get<1>(v)]) {
            visited[std::get<0>(v)][std::get<1>(v)] = true;
            count++;
            auto neighbours = get_neighbours(G, v);
            for (auto const& w : neighbours) {
                if (!visited[std::get<0>(w)][std::get<1>(w)]) {
                    S.push(w);
                }
            }
        }
    }
    return count;
}

int64_t solve_2(std::vector<std::string> inp) {
    auto grid = create_grid(inp);
    auto low_points = get_low_points(grid);
    std::vector<int64_t> basin_sizes(4u, 0);
    std::priority_queue<int, std::vector<int>, std::greater<int>> top_sizes{};
    for (auto const& point : low_points) {
        get_neighbours(grid, point);
        basin_sizes.back() = DFS(grid, point);
        std::partial_sort(basin_sizes.begin(), basin_sizes.begin() + 3, basin_sizes.end(), std::greater<int64_t>());
    }
    return basin_sizes.at(0) * basin_sizes.at(1) * basin_sizes.at(2);
}

void checks() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 15);
    assert(solve_2(sample) == 1134);
}

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, checks, solve_1_wrapper, solve_2_wrapper, input);
}
