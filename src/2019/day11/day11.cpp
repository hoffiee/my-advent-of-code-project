/**
 * https://adventofcode.com/2019/day/11
 */
#include <icecream.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "intcode_computer.h"
#include "string_utils.h"

namespace aoc::y2019::d11 {

using Pos = aoc::grid2d::Pos;

struct PosDir {
    Pos pos_{};
    Pos dir_{};

    PosDir(Pos pos) : pos_{pos}, dir_{Pos{0, 1}} {}
    PosDir(Pos pos, Pos dir) : pos_{pos}, dir_{dir} {}

    /// Rotate
    /// <= 0: Left
    /// >  0: Right
    Pos rotate(int rotdir) {
        if (rotdir > 0) {
            return rotate_right();
        }
        return rotate_left();
    }

    // Think about whether it's possible to do this in a neater way?
    Pos rotate_left() {
        if (dir_.x != 0) {
            dir_ = {0, dir_.x};
        } else if (dir_.y != 0) {
            dir_ = {-dir_.y, 0};
        } else {
            // unreachable, logic fault..
            assert(false);
        }
        return dir_;
    }
    Pos rotate_right() {
        if (dir_.x != 0) {
            dir_ = {0, -dir_.x};
        } else if (dir_.y != 0) {
            dir_ = {dir_.y, 0};
        } else {
            // unreachable, logic fault..
            assert(false);
        }
        return dir_;
    }

    Pos step() {
        pos_ += dir_;
        return pos_;
    }
};

using Grid = std::unordered_map<Pos, int, Pos::Hash>;
using Dim = std::array<int64_t, 4u>;

std::pair<Grid, Dim> paint(IntcodeComputer& comp, int const start_panel_color) {
    PosDir current_pos(Pos{0, 0});
    std::unordered_map<Pos, int, Pos::Hash> grid{{current_pos.pos_, start_panel_color}};

    int64_t min_x{INT64_MAX};
    int64_t min_y{INT64_MAX};
    int64_t max_x{INT64_MIN};
    int64_t max_y{INT64_MIN};
    bool terminated{false};
    while (true) {
        min_x = std::min(min_x, current_pos.pos_.x);
        min_y = std::min(min_y, current_pos.pos_.y);
        max_x = std::max(max_x, current_pos.pos_.x);
        max_y = std::max(max_y, current_pos.pos_.y);

        int input{grid[current_pos.pos_]};
        comp.set_input(input);
        if (comp.exec() != 0) {
            // is this the termination???
            terminated = true;
            break;
        }
        assert(comp.output_.size() == 2);
        auto const paint = comp.output_.at(0);
        auto const direction = comp.output_.at(1);
        comp.output_.clear();

        grid[current_pos.pos_] = paint;

        current_pos.rotate(direction);
        current_pos.step();
    }
    assert(terminated);

    return {grid, {min_x, min_y, max_x, max_y}};
}

int64_t solve_1(std::vector<std::string> inp) {
    assert(inp.size() == 1);

    auto program = string_utils::numbers_from_string(inp.at(0));
    IntcodeComputer comp{program};

    auto [grid, _] = paint(comp, 0);
    return grid.size();
}

int64_t solve_2(std::vector<std::string> inp) {
    assert(inp.size() == 1);

    auto program = string_utils::numbers_from_string(inp.at(0));
    IntcodeComputer comp{program};

    auto const [grid, dim] = paint(comp, 1);
    assert(dim.size() == 4);

    int64_t min_x{dim.at(0)};
    int64_t min_y{dim.at(1)};
    int64_t max_x{dim.at(2)};
    int64_t max_y{dim.at(3)};
    int64_t size_x{max_x - min_x + 1};
    int64_t size_y{max_y - min_y + 1};

    // Rotate y axis while printing
    for (int64_t y{size_y - 1}; 0 <= y; y--) {
        for (int64_t x{0}; x < size_x; x++) {
            Pos const cand{x + min_x, y + min_y};
            if (grid.contains(cand) && grid.at(cand) == 1) {
                std::cout << '#';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

    return grid.size();
}

void samples() {
    PosDir pos{Pos{0, 0}};
    assert((pos.step() == Pos{0, 1}));
    assert((pos.rotate(0) == Pos{-1, 0}));
    assert((pos.step() == Pos{-1, 1}));
    assert((pos.rotate(0) == Pos{0, -1}));
    assert((pos.step() == Pos{-1, 0}));
    assert((pos.rotate(0) == Pos{1, 0}));
    assert((pos.rotate(0) == Pos{0, 1}));
    assert((pos.rotate(1) == Pos{1, 0}));
    assert((pos.rotate(1) == Pos{0, -1}));
    assert((pos.rotate(1) == Pos{-1, 0}));
    assert((pos.rotate(1) == Pos{0, 1}));
}

};  // namespace aoc::y2019::d11

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d11::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d11::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d11::samples, solve_1_wrapper, solve_2_wrapper, input);
}
