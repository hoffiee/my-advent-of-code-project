/**
 * https://adventofcode.com/2021/day/13
 */
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2021::d13 {

using Point = aoc::grid2d::Pos;
using Fold = std::pair<char, int64_t>;
using Folds = std::vector<Fold>;
using Grid = std::unordered_map<Point, bool, Point::Hash>;

std::pair<Grid, Folds> parse(std::vector<std::string> const& inp) {
    Grid grid{};
    Folds folds{};

    bool parsing_points{true};
    for (auto const& line : inp) {
        if (line == "") {
            parsing_points = false;
            continue;
        }
        if (parsing_points) {
            auto points = aoc::string::numbers_from_string(line);
            assert(points.size() == 2u);
            assert(points.at(0) >= 0);
            assert(points.at(1) >= 0);

            grid[Point{points.at(0), points.at(1)}] = true;
        } else {
            auto tmp = aoc::string::split(line, '=');
            assert(tmp.size() == 2u);
            char dir{tmp.at(0).back()};
            int64_t line{std::stoi(tmp.at(1))};
            Fold fold = std::make_pair(dir, line);
            folds.push_back(fold);
        }
    }

    return {grid, folds};
}

void fold(Grid& grid, Fold const& current_fold) {
    std::vector<Point> points_to_move{};
    for (auto const& [point, valid] : grid) {
        if (!valid) {
            continue;
        }

        switch (std::get<0>(current_fold)) {
            case 'x': {
                if (point.x > std::get<1>(current_fold)) {
                    points_to_move.push_back(point);
                }
                break;
            }
            case 'y': {
                if (point.y > std::get<1>(current_fold)) {
                    points_to_move.push_back(point);
                }
                break;
            }
            default: {
                assert(false);
                break;
            }
        }
    }

    for (auto const& point : points_to_move) {
        switch (std::get<0>(current_fold)) {
            case 'x': {
                auto new_x = 2 * std::get<1>(current_fold) - point.x;
                Point np{new_x, point.y};
                grid[np] = true;
                grid.erase(point);
                break;
            }
            case 'y': {
                auto new_y = 2 * std::get<1>(current_fold) - point.y;
                Point np{point.x, new_y};
                grid[np] = true;
                grid.erase(point);
                break;
            }
            default: {
                assert(false);
                break;
            }
        }
    }
}

void fold(Grid& grid, Folds const& folds) {
    for (auto const& current_fold : folds) {
        fold(grid, current_fold);
    }
}

void print(Grid const& grid) {
    std::vector<Point> points_to_draw{};
    int64_t min_x{INT64_MAX};
    int64_t min_y{INT64_MAX};
    int64_t max_x{0};
    int64_t max_y{0};
    for (auto const& [point, _] : grid) {
        points_to_draw.push_back(point);
        min_x = std::min(min_x, point.x);
        min_y = std::min(min_y, point.y);
        max_x = std::max(max_x, point.x);
        max_y = std::max(max_y, point.y);
    }
    IC(min_x, min_y, max_x, max_y);
    assert(min_x == 0);
    assert(min_y == 0);
    std::vector<std::vector<char>> draw(max_y + 1, std::vector<char>(max_x + 1, ' '));

    for (auto const& point : points_to_draw) {
        draw.at(point.y).at(point.x) = '@';
    }

    for (auto const& line : draw) {
        for (auto const& col : line) {
            std::cout << col;
        }
        std::cout << std::endl;
    }
}

int64_t solve_1(std::vector<std::string> inp) {
    auto [grid, folds] = parse(inp);
    fold(grid, folds.at(0));
    return static_cast<int64_t>(grid.size());
}

int64_t solve_2(std::vector<std::string> inp) {
    auto [grid, folds] = parse(inp);
    fold(grid, folds);
    print(grid);
    return static_cast<int64_t>(grid.size());
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 17);
    assert(solve_2(sample) == 16);
}

};  // namespace aoc::y2021::d13

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2021::d13::solve_1(inp);
        assert(part1 == 592);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2021::d13::solve_2(inp);
        assert(part2 == 94);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2021::d13::samples, solve_1_wrapper, solve_2_wrapper, input);
}
