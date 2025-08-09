/**
 * https://adventofcode.com/2019/day/12
 *
 */
#include <algorithm>
#include <array>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "math_utils.h"
#include "string_utils.h"

namespace aoc::y2019::d12 {

using Vec = std::array<int64_t, 3u>;

std::ostream& operator<<(std::ostream& os, Vec const& v) {
    os << '<';
    int width = 3;
    for (std::size_t i = 0; i < v.size(); ++i) {
        os << std::setw(width) << v[i];
        if (i + 1 < v.size()) os << ", ";
    }
    os << '>';
    return os;
}

inline Vec operator+(const Vec& a, const Vec& b) {
    Vec res;
    for (std::size_t i = 0; i < 3; ++i) {
        res[i] = a[i] + b[i];
    }
    return res;
}

int64_t sum_abs(Vec const& vec) {
    int64_t sum{0};
    for (auto const& v : vec) {
        sum += std::abs(v);
    }
    return sum;
}

struct Moon {
    Vec x_{};
    Vec dx_{};
    Moon(int64_t x, int64_t y, int64_t z) : x_{x, y, z} {}
    Moon(std::vector<int64_t> nums) : Moon(nums.at(0), nums.at(1), nums.at(2)) {}

    void update_dx(Moon const& other) {
        assert(other.dx_.size() == dx_.size());
        for (std::size_t dim{0}; dim < dx_.size(); dim++) {
            dx_.at(dim) += std::clamp(other.x_.at(dim) - x_.at(dim), static_cast<int64_t>(-1), static_cast<int64_t>(1));
        }
    }

    void update_x() { x_ = x_ + dx_; }

    int64_t potential_energy() const { return sum_abs(x_); }

    int64_t kinetic_energy() const { return sum_abs(dx_); }

    int64_t total_energy() const { return potential_energy() * kinetic_energy(); }

    friend std::ostream& operator<<(std::ostream& os, Moon const& m) {
        os << "pos=" << m.x_;
        os << ", vel=" << m.dx_;
        return os;
    };
};

std::vector<Moon> parse_input(std::vector<std::string> const& inp) {
    std::vector<Moon> moons{};
    for (auto const& line : inp) {
        auto const parsed = string_utils::numbers_from_string(line);
        assert(parsed.size() == 3);
        moons.emplace_back(Moon{parsed});
    }
    return moons;
}

void moons_step(std::vector<Moon>& moons) {
    for (std::size_t i{0}; i < moons.size(); i++) {
        for (std::size_t j{0}; j < moons.size(); j++) {
            if (i == j) {
                continue;
            }
            moons.at(i).update_dx(moons.at(j));
        }
    }
    for (std::size_t i{0}; i < moons.size(); i++) {
        moons.at(i).update_x();
    }
}

bool state_check_in_dimension(std::vector<Moon> const& lhs, std::vector<Moon> const& rhs, int64_t dim) {
    assert(lhs.size() == rhs.size());

    for (std::size_t i{0}; i < lhs.size(); i++) {
        if (lhs.at(i).x_.at(dim) != rhs.at(i).x_.at(dim)) {
            return false;
        }
        if (lhs.at(i).dx_.at(dim) != rhs.at(i).dx_.at(dim)) {
            return false;
        }
    }
    return true;
}

int64_t solve_1(std::vector<std::string> inp, int64_t steps) {
    auto moons = parse_input(inp);

    for (int64_t step{0}; step < steps; step++) {
        moons_step(moons);
    }

    int64_t system_total_energy{0};
    for (auto const& moon : moons) {
        system_total_energy += moon.total_energy();
    }
    return system_total_energy;
}

int64_t solve_2(std::vector<std::string> inp) {
    /// As each dimension is independent (see update function for moon). We run
    /// until we find periodicity in each dimension, and then find the largest
    /// common multiple for those,
    ///
    /// Initially I assumed that the periodicity wasn't at the init state, but
    /// turns out it was so could simplify a lot...
    auto moons = parse_input(inp);

    auto const init_state = moons;

    std::vector<int64_t> periodicity(3u, 0);
    int64_t periodicity_dimensions_found{0};
    for (int64_t step{0}; step < 1'000'000; step++) {
        moons_step(moons);

        // Look for periodicity in each dimension.
        for (std::size_t dim{0}; dim < periodicity.size(); dim++) {
            if (periodicity.at(dim) > 0) {
                continue;
            }

            if (state_check_in_dimension(init_state, moons, dim)) {
                periodicity.at(dim) = step + 1;
                periodicity_dimensions_found++;
            }
        }

        if (periodicity_dimensions_found >= 3) {
            break;
        }
    }

    assert(periodicity_dimensions_found >= 3);
    return math_utils::lcm(periodicity);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample, 10) == 179);
    assert(solve_2(sample) == 2772);

    auto sample1 = aoc::utils::read_input("day12-sample-1.input");
    assert(solve_1(sample1, 100) == 1940);
    assert(solve_2(sample1) == 4686774924);
}

};  // namespace aoc::y2019::d12

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d12::solve_1(inp, 1000);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d12::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d12::samples, solve_1_wrapper, solve_2_wrapper, input);
}
