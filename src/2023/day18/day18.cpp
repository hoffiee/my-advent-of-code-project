/**
 * https://adventofcode.com/2023/day/18
 *
 * aoc_tags: shoelace formula, picks theorem, polygon perimeter
 */
#include <cassert>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d18 {

struct Point2d {
    int64_t x_{};
    int64_t y_{};

    friend std::ostream& operator<<(std::ostream& os, Point2d p) {
        os << "(" << p.x_ << "," << p.y_ << ")";
        return os;
    }

    friend bool operator==(Point2d const& p1, Point2d const& p2) { return p1.x_ == p2.x_ && p1.y_ == p2.y_; }
};

int64_t shoelace_formula(std::vector<Point2d> const& coordinates) {
    // https://en.wikipedia.org/wiki/Shoelace_formula
    assert(coordinates.front() == coordinates.back());
    int64_t area{0};
    size_t n{coordinates.size()};

    for (size_t i{0}; i < n; i++) {
        size_t j = (i + 1) % n;
        area += coordinates[i].x_ * coordinates[j].y_;
        area -= coordinates[j].x_ * coordinates[i].y_;
    }
    return area / 2;
}

int64_t polygon_perimeter(std::vector<Point2d> const& coordinates) {
    size_t n{coordinates.size()};
    assert(coordinates.front() == coordinates.back());
    int64_t sum{0};
    for (size_t i{0}; i < n; i++) {
        size_t j{(i + 1) % n};
        sum += std::abs(coordinates.at(j).x_ - coordinates.at(i).x_);
        sum += std::abs(coordinates.at(j).y_ - coordinates.at(i).y_);
    }
    return sum;
}

int64_t picks_theorem(std::vector<Point2d> const& coordinates, int64_t A) {
    // https://en.wikipedia.org/wiki/Pick%27s_theorem
    assert(coordinates.front() == coordinates.back());

    int64_t perimeters_points{polygon_perimeter(coordinates)};
    int64_t interior_points{A - perimeters_points / 2 + 1};
    return interior_points + perimeters_points;
}

int64_t solve_1(std::vector<std::string> inp) {
    Point2d point{};
    std::vector<Point2d> coordinates{point};

    for (auto const& instr : inp) {
        auto const tmp = aoc::string::split(instr, ' ');
        auto const distance = std::stoi(tmp.at(1));
        switch (instr.at(0)) {
            case 'U': {
                point.y_ -= distance;
                break;
            }
            case 'R': {
                point.x_ += distance;
                break;
            }
            case 'D': {
                point.y_ += distance;
                break;
            }
            case 'L': {
                point.x_ -= distance;
                break;
            }
            default: {
                assert(false);
            }
        }
        coordinates.push_back(point);
    }
    assert(coordinates.front() == coordinates.back());

    auto const area = shoelace_formula(coordinates);
    auto const points = picks_theorem(coordinates, area);
    return points;
}

int64_t solve_2(std::vector<std::string> inp) {
    Point2d point{};
    std::vector<Point2d> coordinates{point};

    for (auto const& instr : inp) {
        auto const tmp = aoc::string::split(instr, ' ');
        assert(tmp.size() == 3);

        std::string const hex_digit(tmp.at(2));
        std::string const distance_hex(hex_digit.cbegin() + 2, hex_digit.cend() - 2);
        int64_t const distance{std::stoi(distance_hex, nullptr, 16)};
        char const dir{hex_digit.at(hex_digit.size() - 2)};

        switch (dir) {
            case '0': {
                point.x_ += distance;
                break;
            }
            case '1': {
                point.y_ += distance;
                break;
            }
            case '2': {
                point.x_ -= distance;
                break;
            }
            case '3': {
                point.y_ -= distance;
                break;
            }
            default: {
                assert(false);
            }
        }
        coordinates.push_back(point);
    }

    assert(coordinates.front() == coordinates.back());

    auto const area = shoelace_formula(coordinates);
    auto const points = picks_theorem(coordinates, area);
    return points;
}

void tests() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 62);
    assert(solve_2(sample) == 952408144115);
}

}  // namespace aoc::y2023::d18

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2023::d18::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2023::d18::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2023::d18::tests, solve_1_wrapper, solve_2_wrapper, input);
}
