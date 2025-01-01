/**
 * https://adventofcode.com/2024/day/14
 */
#include <algorithm>
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "lodepng.h"
#include "string_utils.h"

using Pos = std::complex<int64_t>;

struct Robot {
    Pos p_{};
    Pos v_{};
    std::complex<int64_t> grid_sz_{};
    Pos ignore_{};

    Robot(std::string const& desc, std::complex<int> grid_sz)
        : grid_sz_{grid_sz}, ignore_{grid_sz_.real() / 2, grid_sz_.imag() / 2} {
        auto numbers = string_utils::numbers_from_string(desc.c_str());
        assert(numbers.size() == 4);
        p_ = Pos{numbers[0], numbers[1]};
        v_ = Pos{numbers[2], numbers[3]};
    }

    void step(int64_t steps) {
        p_ += v_ * steps;
        p_ = wrap(p_, grid_sz_);
    }

    friend std::ostream& operator<<(std::ostream& os, Robot const& r) {
        os << r.p_ << ", " << r.v_;
        return os;
    }

    static Pos wrap(Pos p, Pos range) {
        return {(p.real() % range.real() + range.real()) % range.real(),
                (p.imag() % range.imag() + range.imag()) % range.imag()};
    }

    int64_t get_quadrant() const {
        // The ones on the borders are ignored, so they get quadrant 0
        if (p_.real() < ignore_.real() && p_.imag() < ignore_.imag()) {
            return 1;
        }
        if (p_.real() > ignore_.real() && p_.imag() < ignore_.imag()) {
            return 2;
        }
        if (p_.real() < ignore_.real() && p_.imag() > ignore_.imag()) {
            return 3;
        }
        if (p_.real() > ignore_.real() && p_.imag() > ignore_.imag()) {
            return 4;
        }
        return 0;
    }
};

void save_image(std::vector<Robot> const& robots, int64_t step, std::complex<int> grid_sz) {
    int64_t width = grid_sz.real();
    int64_t height = grid_sz.imag();

    std::vector<unsigned char> image(width * height * 4, 0);
    for (auto const& robot : robots) {
        auto x = robot.p_.real();
        auto y = robot.p_.imag();
        image[4 * width * y + 4 * x + 0] = 255;
        image[4 * width * y + 4 * x + 1] = 255;
        image[4 * width * y + 4 * x + 2] = 255;
        image[4 * width * y + 4 * x + 3] = 255;
    }
    std::string filename = "frame_" + std::to_string(step) + ".png";
    auto error = lodepng_encode32_file(filename.c_str(), image.data(), width, height);
    assert(error == 0);
}

int64_t solve_1(std::vector<std::string> inp, std::complex<int> grid_sz) {
    std::vector<int64_t> robot_quadrant_count(5, 0);
    for (auto const& line : inp) {
        Robot robot(line, grid_sz);
        robot.step(100);
        int64_t quadrant{robot.get_quadrant()};
        robot_quadrant_count[quadrant]++;
    }
    // Exclude the ones on the quadrant borders
    return std::accumulate(std::next(robot_quadrant_count.cbegin()), robot_quadrant_count.cend(),
                           static_cast<int64_t>(1), std::multiplies<int64_t>());
}

double covariance(std::vector<Robot> const& robots) {
    Pos sum{std::accumulate(robots.cbegin(), robots.cend(), Pos{0, 0}, [](Pos acc, Robot r) { return acc + r.p_; })};

    std::complex<double> mean{static_cast<double>(sum.real()) / static_cast<double>(robots.size()),
                              static_cast<double>(sum.imag()) / static_cast<double>(robots.size())};

    std::complex<double> squared_diff_sum{std::accumulate(
        robots.cbegin(), robots.cend(), std::complex<double>{0, 0}, [mean](std::complex<double> acc, Robot const& r) {
            double base_x{static_cast<double>(r.p_.real()) - mean.real()};
            double base_y{static_cast<double>(r.p_.imag()) - mean.imag()};
            return std::complex<double>{acc.real() + std::pow(base_x, 2), acc.imag() + std::pow(base_y, 2)};
        })};
    squared_diff_sum /= static_cast<double>(robots.size());
    return squared_diff_sum.real() * squared_diff_sum.imag();
}

int64_t solve_2(std::vector<std::string> inp, std::complex<int> grid_sz) {
    std::vector<Robot> robots{};
    for (auto const& line : inp) {
        Robot robot(line, grid_sz);
        robots.emplace_back(robot);
    }

    double lowest_cost{std::numeric_limits<double>::infinity()};
    int64_t lowest_step{0};
    for (int64_t i{1}; i < 20000; i++) {
        for (auto& robot : robots) {
            robot.step(1);
        }
        double candidate{covariance(robots)};
        if (candidate < lowest_cost) {
            lowest_cost = candidate;
            lowest_step = i;
            save_image(robots, i, grid_sz);
        }
    }
    return lowest_step;
}

void samples() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, {11, 7}) == 12);
}

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp, {101, 103}) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp, {101, 103}) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
