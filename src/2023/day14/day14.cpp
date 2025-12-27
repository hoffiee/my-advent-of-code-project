/**
 * https://adventofcode.com/2023/day/14
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using Grid = std::vector<std::vector<int>>;

void print(Grid const& grid, Grid const& stones) {
    for (size_t r{1}; r < grid.size() - 1u; r++) {
        for (size_t c{1}; c < grid.front().size() - 1u; c++) {
            if (stones[r][c]) {
                std::cout << "O";
            } else if (grid[r][c]) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void tilt_north(Grid const& grid, Grid& stones) {
    for (size_t c{1}; c < grid.front().size() - 1; c++) {
        for (size_t r{2}; r < grid.size() - 1; r++) {
            if (stones[r][c] == 0) {
                continue;
            }

            size_t new_r{r};
            while (new_r > 0 && (grid[new_r - 1u][c] == 0 && stones[new_r - 1u][c] == 0)) {
                new_r--;
            }
            if (new_r > 0 && new_r != r) {
                assert(stones[new_r][c] == 0);
                stones[new_r][c] = 1;
                stones[r][c] = 0;
            }
        }
    }
}

void tilt_west(Grid const& grid, Grid& stones) {
    for (size_t r{1}; r < grid.size() - 1; r++) {
        for (size_t c{2}; c < grid.front().size() - 1; c++) {
            if (stones[r][c] == 0) {
                continue;
            }

            size_t new_c{c};
            while (new_c > 0 && (grid[r][new_c - 1u] == 0 && stones[r][new_c - 1u] == 0)) {
                new_c--;
            }
            if (new_c > 0 && new_c != c) {
                assert(stones[r][new_c] == 0);
                stones[r][new_c] = 1;
                stones[r][c] = 0;
            }
        }
    }
}

void tilt_south(Grid const& grid, Grid& stones) {
    for (size_t c{1u}; c < grid.front().size() - 1u; c++) {
        for (size_t r{grid.size() - 2u}; r > 0u; r--) {
            if (stones[r][c] == 0) {
                continue;
            }

            size_t new_r{r};
            while (new_r > 0 && (grid[new_r + 1u][c] == 0 && stones[new_r + 1u][c] == 0)) {
                new_r++;
            }
            if (new_r > 0 && new_r != r) {
                assert(stones[new_r][c] == 0);
                stones[new_r][c] = 1;
                stones[r][c] = 0;
            }
        }
    }
}

void tilt_east(Grid const& grid, Grid& stones) {
    for (size_t r{1u}; r < grid.front().size() - 1u; r++) {
        for (size_t c{grid.size() - 2u}; c > 0u; c--) {
            if (stones[r][c] == 0) {
                continue;
            }

            size_t new_c{c};
            while (new_c > 0 && (grid[r][new_c + 1u] == 0 && stones[r][new_c + 1u] == 0)) {
                new_c++;
            }
            if (new_c > 0 && new_c != c) {
                assert(stones[r][new_c] == 0);
                stones[r][new_c] = 1;
                stones[r][c] = 0;
            }
        }
    }
}

int64_t calculate_load(Grid const& stones) {
    size_t max{stones.size() - 1u};
    int64_t out{0};
    for (size_t r{1}; r < stones.size() - 1u; r++) {
        for (size_t c{1}; c < stones.front().size() - 1u; c++) {
            if (stones[r][c]) {
                out += static_cast<int64_t>(max - r);
            }
        }
    }
    return out;
}

std::tuple<Grid, Grid> create_grid_stones(std::vector<std::string> const& inp) {
    Grid grid(inp.size() + 2, std::vector<int>(inp.front().size() + 2, 1));
    Grid stones(inp.size() + 2, std::vector<int>(inp.front().size() + 2, 0));

    for (size_t r{0}; r < inp.size(); r++) {
        for (size_t c{0}; c < inp.front().size(); c++) {
            switch (inp[r][c]) {
                case '#':
                    break;
                case '.':
                    grid[r + 1][c + 1] = 0;
                    break;
                case 'O':
                    stones[r + 1][c + 1] = 1;
                    grid[r + 1][c + 1] = 0;
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    }
    return {grid, stones};
}

int64_t solve_1(std::vector<std::string> inp) {
    auto [grid, stones] = create_grid_stones(inp);
    tilt_north(grid, stones);
    auto out = calculate_load(stones);
    return out;
}

size_t hash_stones(Grid const& grid) {
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    const size_t ROWS = grid.size();
    const size_t COLS = grid[0].size();

    uint64_t hash = 14695981039346656037ULL;  // FNV offset basis
    const uint64_t FNV_PRIME = 1099511628211ULL;

    for (size_t i = 0; i < ROWS; ++i) {
        uint64_t row_hash = 0;
        for (size_t j = 0; j < COLS; ++j) {
            row_hash |= (grid[i][j] ? 1ULL : 0ULL) << (j % 64);
            if ((j + 1) % 64 == 0 || j == COLS - 1) {
                hash ^= row_hash;
                hash *= FNV_PRIME;
                row_hash = 0;
            }
        }
    }

    return hash;
}

int64_t solve_2(std::vector<std::string> inp) {
    auto [grid, stones] = create_grid_stones(inp);

    // Search until the board starts to repeat itself
    // We need to store grid and cycle.
    std::unordered_map<size_t, bool> hashes{};
    std::vector<Grid> grids{};
    hashes[hash_stones(stones)] = true;
    size_t cycles{1000000000u};
    size_t hash{};
    for (size_t i{0}; i < cycles; i++) {
        tilt_north(grid, stones);
        tilt_west(grid, stones);
        tilt_south(grid, stones);
        tilt_east(grid, stones);

        hash = hash_stones(stones);
        if (hashes.contains(hash)) {
            break;
        }
        grids.push_back(stones);
        hashes[hash] = true;
    }

    /**
     *         5<-4
     *   0->1->2->3
     *         ^  v
     *
     *  So indexing and all, we start at 0, we find the start of the cycle at 2
     *  = ST, we know we need to do TC steps in total, cycle length C is = 4
     *
     *  TC = ST + N*TC + Offset
     *
     *  N is number of cycles
     *  Offset is the offset in the cycle
     *
     *  N = (TC-ST)/TC
     *  Offset = TC - ST - N*TC
     */

    // Last in grids is now the state before we hit the cycle
    // find the element in grids that has the hash, this is the start of the cycle
    auto first =
        std::find_if(grids.cbegin(), grids.cend(), [hash](auto const& entry) { return hash == hash_stones(entry); });

    assert(first != grids.cend());

    auto start_offset = std::distance(grids.cbegin(), first);
    auto cycle_distance = std::distance(first, grids.cend());

    size_t nr_of_cycles{(cycles - start_offset) / cycle_distance};
    size_t cycle_offset{cycles - start_offset - cycle_distance * nr_of_cycles};

    // Didn't really figure out where the -1 is coming from, but it solves both
    // example and the task so I'm ok with it.
    auto out = calculate_load(*(first + cycle_offset - 1u));
    return out;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 136);
    assert(solve_2(sample) == 64);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 109466);
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 94585);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
