/**
 * https://adventofcode.com/2018/day/10
 *
 * Ah, mostly reusing 2024 day 14.
 */
#include <algorithm>
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "lodepng.h"

using Pos = std::complex<int64_t>;

struct Points {
    Pos pos_{};
    Pos vel_{};

    Points(std::string const& desc) {
        auto numbers = aoc::string::numbers_from_string(desc.c_str());
        assert(numbers.size() == 4);
        pos_ = Pos{numbers[0], numbers[1]};
        vel_ = Pos{numbers[2], numbers[3]};
    }

    void step(int64_t steps) { pos_ += vel_ * steps; }

    friend std::ostream& operator<<(std::ostream& os, Points const& r) {
        os << r.pos_ << ", " << r.vel_;
        return os;
    }
};

void save_image(std::vector<Points> const& points, int64_t step) {
    // find boundaries
    int64_t xmin{INT64_MAX};
    int64_t ymin{INT64_MAX};
    int64_t xmax{INT64_MIN};
    int64_t ymax{INT64_MIN};
    for (auto const& point : points) {
        xmin = std::min(xmin, point.pos_.real());
        ymin = std::min(ymin, point.pos_.imag());
        xmax = std::max(xmax, point.pos_.real());
        ymax = std::max(ymax, point.pos_.imag());
    }

    int64_t width = xmax - xmin + 1;
    int64_t height = ymax - ymin + 1;

    // If the image is too large we skip it
    if (width * height >= 50000) {
        return;
    }

    std::vector<unsigned char> image(width * height * 4, 0);
    for (auto const& point : points) {
        auto x = point.pos_.real() - xmin;
        auto y = point.pos_.imag() - ymin;
        image[4 * width * y + 4 * x + 0] = 255;
        image[4 * width * y + 4 * x + 1] = 255;
        image[4 * width * y + 4 * x + 2] = 255;
        image[4 * width * y + 4 * x + 3] = 255;
    }
    std::string filename = "frame_" + std::to_string(step) + ".png";
    auto error = lodepng_encode32_file(filename.c_str(), image.data(), width, height);
    assert(error == 0);
}

double covariance(std::vector<Points> const& points) {
    Pos sum{std::accumulate(points.cbegin(), points.cend(), Pos{0, 0}, [](Pos acc, Points r) { return acc + r.pos_; })};

    std::complex<double> mean{static_cast<double>(sum.real()) / static_cast<double>(points.size()),
                              static_cast<double>(sum.imag()) / static_cast<double>(points.size())};

    std::complex<double> squared_diff_sum{std::accumulate(
        points.cbegin(), points.cend(), std::complex<double>{0, 0}, [mean](std::complex<double> acc, Points const& r) {
            double base_x{static_cast<double>(r.pos_.real()) - mean.real()};
            double base_y{static_cast<double>(r.pos_.imag()) - mean.imag()};
            return std::complex<double>{acc.real() + std::pow(base_x, 2), acc.imag() + std::pow(base_y, 2)};
        })};
    squared_diff_sum /= static_cast<double>(points.size());
    return squared_diff_sum.real() * squared_diff_sum.imag();
}

int64_t solve(std::vector<std::string> const& inp) {
    std::vector<Points> points{};
    for (auto const& line : inp) {
        Points point(line);
        points.emplace_back(point);
    }

    double lowest_cost{std::numeric_limits<double>::infinity()};
    int64_t lowest_step{0};
    for (int64_t i{1}; i < 20000; i++) {
        for (auto& point : points) {
            point.step(1);
        }
        double candidate{covariance(points)};
        if (candidate < lowest_cost) {
            lowest_cost = candidate;
            lowest_step = i;
            save_image(points, i);
        }
    }
    return lowest_step;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve(sample) == 3);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve(inp);
        // Checking part 2, check produced images to find the answer
        assert(res == 10659);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve(inp);
        assert(res == 10659);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
