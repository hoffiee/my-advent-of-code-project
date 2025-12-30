/**
 * https://adventofcode.com/2016/day/8
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

struct Pixels {
    std::vector<std::vector<bool>> pixels_;

    Pixels(int64_t width, int64_t height) : pixels_(height, std::vector<bool>(width, false)) {}

    void add(int64_t width, int64_t height) {
        assert(0 <= width && width < static_cast<int64_t>(pixels_[0].size()));
        assert(0 <= height && height < static_cast<int64_t>(pixels_.size()));
        for (int64_t w{0}; w < width; w++) {
            for (int64_t h{0}; h < height; h++) {
                pixels_[h][w] = true;
            }
        }
    }

    void rotate_column(int64_t col_idx, int64_t steps) {
        assert(steps > 0);
        // Make copy, then overwrite original
        int64_t n = pixels_.size();
        steps = steps % n;

        std::vector<bool> col(n, false);

        for (int64_t i{0}; i < n; i++) {
            col[i] = pixels_[i][col_idx];
        }

        std::rotate(col.begin(), col.begin() + n - steps, col.end());

        for (int64_t i{0}; i < n; i++) {
            pixels_[i][col_idx] = col[i];
        }
    }

    void rotate_row(size_t row_idx, int64_t steps) {
        assert(steps > 0);
        int64_t n = pixels_[row_idx].size();
        steps = steps % n;
        auto& row = pixels_[row_idx];
        std::rotate(row.begin(), row.begin() + n - steps, row.end());
    }

    int64_t count_pixels() const {
        int64_t sum{0};
        for (auto const& row : pixels_) {
            for (auto const& pixel : row) {
                sum += static_cast<int64_t>(pixel);
            }
        }
        return sum;
    }

    void print() {
        for (auto const& line : pixels_) {
            for (auto const& row : line) {
                std::cout << (row ? "#" : " ");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int64_t solve(std::vector<std::string> const& inp, int64_t width = 50, int64_t height = 6) {
    Pixels pixels(width, height);

    for (auto const& line : inp) {
        if (line.starts_with("rect")) {
            auto numbers = aoc::string::numbers_from_string(line);
            assert(numbers.size() == 2);
            pixels.add(numbers[0], numbers[1]);
            continue;
        }
        if (line.starts_with("rotate")) {
            auto words = aoc::string::split(line, ' ');
            auto numbers = aoc::string::numbers_from_string(line);

            switch (words[1][0]) {
                case 'c': {
                    pixels.rotate_column(numbers[0], numbers[1]);
                    break;
                }
                case 'r': {
                    pixels.rotate_row(numbers[0], numbers[1]);
                    break;
                }
                default:
                    assert(false);
            }
            continue;
        }
        assert(false);
    }
    pixels.print();
    return pixels.count_pixels();
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve(sample, 7, 3) == 6);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve(inp);
        assert(res == 123);
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve(inp);
        // Same answer as first part, check output in terminal
        assert(res == 123);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
