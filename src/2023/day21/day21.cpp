/**
 * https://adventofcode.com/2023/day/21
 */

#include <icecream.hpp>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d21 {

struct Pos {
    int64_t x{};
    int64_t y{};

    Pos& operator+(Pos const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Pos const& p) {
        os << "(" << p.x << "," << p.y << ")" << std::endl;
        return os;
    }

    bool operator==(Pos const& other) const { return x == other.x && y == other.y; }

    bool operator<(Pos const& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    struct Hash {
        size_t operator()(Pos const& pos) const {
            size_t hx = std::hash<int64_t>()(pos.x);
            size_t hy = std::hash<int64_t>()(pos.y) << 8;
            return hx ^ hy;
        }
    };
};

Pos operator+(Pos const& lhs, Pos const& rhs) { return Pos{lhs.x + rhs.x, lhs.y + rhs.y}; }

struct Grid {
    std::int64_t const x_sz_{};
    std::int64_t const y_sz_{};
    Pos start_{};
    std::vector<std::string> map_{};

    Grid(std::vector<std::string> const& inp)
        : x_sz_{static_cast<std::int64_t>(inp.at(0).size())}, y_sz_{static_cast<std::int64_t>(inp.size())}, map_{inp} {
        bool found_start{find_start_position()};
        assert(found_start);
    }

    char& operator[](Pos const& pos) { return map_.at(pos.y).at(pos.x); }
    char const& operator[](Pos const& pos) const { return map_.at(pos.y).at(pos.x); }

    bool find_start_position() {
        for (std::int64_t y{0u}; y < y_sz_; y++) {
            for (std::int64_t x{0u}; x < x_sz_; x++) {
                Pos cand{x, y};
                if (this->operator[](cand) == 'S') {
                    start_ = Pos{x, y};
                    this->operator[](cand) = '.';
                    return true;
                }
            }
        }
        return false;
    }

    bool contains(Pos const pos) const {
        if (pos.x < 0 || x_sz_ <= pos.x) {
            return false;
        }
        if (pos.y < 0 || y_sz_ <= pos.y) {
            return false;
        }
        return true;
    }

    std::vector<Pos> neighbours(Pos const pos) const {
        std::vector<Pos> out{};
        std::vector<Pos> const dirs{
            Pos{1, 0},
            Pos{-1, 0},
            Pos{0, 1},
            Pos{0, -1},
        };
        for (auto const& dir : dirs) {
            auto cand = pos + dir;
            if (contains(cand)) {
                if (this->operator[](cand) == '.') {
                    out.push_back(cand);
                }
            }
        }
        return out;
    };

    friend std::ostream& operator<<(std::ostream& os, Grid const& g) {
        for (auto const& line : g.map_) {
            for (auto const& ch : line) {
                os << ch;
            }
            os << std::endl;
        }
        return os;
    }
};

struct State {
    Pos const pos{};
    int64_t const steps{};

    bool operator==(State const& other) const { return pos == other.pos && steps == other.steps; }
};

struct Grid2 : public Grid {
    Grid2(std::vector<std::string> const& inp) : Grid{inp} {}

    char& operator[](Pos const& pos) { return map_.at(aoc::math::mod(pos.y, y_sz_)).at(aoc::math::mod(pos.x, x_sz_)); }

    char const& operator[](Pos const& pos) const {
        auto y = aoc::math::mod(pos.y, y_sz_);
        auto x = aoc::math::mod(pos.x, x_sz_);
        return map_.at(y).at(x);
    }

    bool contains(Pos const pos) const { return true; }

    std::vector<Pos> neighbours(Pos const pos) const {
        std::vector<Pos> out{};
        std::vector<Pos> const dirs{
            Pos{1, 0},
            Pos{-1, 0},
            Pos{0, 1},
            Pos{0, -1},
        };
        for (auto const& dir : dirs) {
            auto cand = pos + dir;
            if (this->operator[](cand) == '.') {
                out.push_back(cand);
            }
        }
        return out;
    };
};

template <typename T>
int64_t possible_tiles(T const& grid, int64_t const steps) {
    std::queue<State> queue{};
    queue.push(State{grid.start_, steps});
    std::unordered_set<Pos, Pos::Hash> visited{};
    std::unordered_set<Pos, Pos::Hash> end{};

    while (!queue.empty()) {
        auto const step = queue.front();
        queue.pop();

        if (step.steps % 2 == 0) {
            end.insert(step.pos);
        }

        if (step.steps == 0) {
            continue;
        }

        auto const possible_steps = grid.neighbours(step.pos);
        for (auto const& possible_step : possible_steps) {
            if (visited.contains(possible_step)) {
                continue;
            }

            visited.insert(possible_step);
            State cand{possible_step, step.steps - 1};
            queue.push(cand);
        }
    }

    int64_t count{static_cast<int64_t>(end.size())};
    return count;
}

int64_t solve_1(std::vector<std::string> inp, int64_t const steps) {
    IC_CONFIG.disable();
    Grid grid(inp);

    int64_t count{possible_tiles(grid, steps)};
    return count;
}

int64_t solve_2(std::vector<std::string> inp, int64_t const steps) {
    IC_CONFIG.enable();
    Grid2 grid(inp);
    assert(inp.at(0).size() == inp.size());

    // sample input, make sure the possible_grid works as expected for sample
    // input
    if (steps <= 1000) {
        return possible_tiles(grid, steps);
    }

    // My solution didn't scale well with `steps`. I did some attempts with
    // caching varying aspects but didn't really get far. I started to look
    // into the input and noticed some patterns. After a while I started
    // looking into how others had solved this, and found that one of the
    // insights is that the input behaves as a quadratic function over 131k+65
    // for k=0,1,2,.. whereas the requested steps exists for an integer k
    //
    // So the approach is to calculate for a few k and then extrapolate for the
    // amount of steps.
    int64_t nr_of_samples{3};
    std::vector<double> xvec{};
    std::vector<double> yvec{};
    xvec.reserve(nr_of_samples);
    yvec.reserve(nr_of_samples);
    for (int64_t i{0}; i < nr_of_samples; i++) {
        double step{131 * static_cast<double>(i) + 65};
        xvec.push_back(step);
        yvec.push_back(static_cast<double>(possible_tiles(grid, step)));
    }

    aoc::math::PolynomialInterpolation<double, 3u> inter(xvec, yvec);
    auto interp_res = static_cast<int64_t>(inter.interpolate(steps));

    return static_cast<int64_t>(interp_res);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    auto ans = solve_1(sample, 6);
    assert(ans == 16);
    ans = solve_2(sample, 6);
    assert(ans == 16);
    ans = solve_2(sample, 10);
    assert(ans == 50);
    ans = solve_2(sample, 50);
    assert(ans == 1594);
    ans = solve_2(sample, 100);
    assert(ans == 6536);
    ans = solve_2(sample, 500);
    assert(ans == 167004);
    ans = solve_2(sample, 1000);
    assert(ans == 668697);
}

};  // namespace aoc::y2023::d21

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2023::d21::solve_1(inp, 64);
        assert(part1 == 3751);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2023::d21::solve_2(inp, 26501365);
        assert(part2 == 619407349431167);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2023::d21::samples, solve_1_wrapper, solve_2_wrapper, input);
}
