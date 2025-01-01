/**
 * https://adventofcode.com/2024/day/13
 *
 * Set it up as a system of linear equations
 *
 * A = [xa, ya;
 *      xb, yb]     -- step in x,y for A and B button press
 * x = [A, B]'      -- number of button presses for A/B
 * b = [xp, yp]'    -- coordinates to the prize
 *
 * Solve
 * A.x = b
 * => x = Ainv.b
 *
 * with 2x2
 * Ainv = 1/det(A)[ yb, -ya;
 *                 -xb,  xa]
 *                ^--------^
 *                  := Ai
 *
 * with
 * det(A) = xa*yb - ya*xb
 *
 * So calculate
 * Ai.b = [yb*xp - ya*yp;
 *         -xb*xp + xa*yp]
 *
 * Do an integer division betwen Ai.b and det and check if we have a remainder,
 * if we do it was a integer step and then we account for that one
 */
#include <cmath>
#include <cstdint>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "string_utils.h"

struct Target {
    int64_t a_{};
    int64_t b_{};
    int64_t c_{};
    int64_t d_{};
    int64_t x_{};
    int64_t y_{};
    int64_t det_{};

    Target(std::string const& inp) {
        auto numbers = string_utils::numbers_from_string(inp);
        assert(numbers.size() == 6);

        a_ = numbers[0];
        b_ = numbers[2];
        c_ = numbers[1];
        d_ = numbers[3];
        x_ = numbers[4];
        y_ = numbers[5];
        det_ = a_ * d_ - c_ * b_;
    }

    int64_t solve() {
        auto res_a = std::div(d_ * x_ - b_ * y_, det_);
        auto res_b = std::div(-c_ * x_ + a_ * y_, det_);

        if ((res_a.rem == 0) && (res_b.rem == 0)) {
            return res_a.quot * 3 + res_b.quot;
        }
        return 0;
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    int64_t sum{0};
    for (size_t i{0}; i < inp.size(); i += 4) {
        Target t(inp[i] + inp[i + 1] + inp[i + 2]);
        sum += t.solve();
    }
    return sum;
}

int64_t solve_2(std::vector<std::string> inp) {
    int64_t sum{0};
    for (size_t i{0}; i < inp.size(); i += 4) {
        Target t(inp[i] + inp[i + 1] + inp[i + 2]);
        t.x_ += 10000000000000;
        t.y_ += 10000000000000;
        sum += t.solve();
    }
    return sum;
}

void samples() {
    auto sample1 = string_utils::read_input("day13-sample-1.input");
    assert(solve_1(sample1) == 280);

    auto sample2 = string_utils::read_input("day13-sample-2.input");
    assert(solve_1(sample2) == 480);
}

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
