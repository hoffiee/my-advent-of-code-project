/**
 * https://adventofcode.com/2022/day/9
 *
 * Reconsider approach: Maybe it's better to simulate each step
 * [aoc] desktop :: ~/repo/advent-of-code ‹main*› % cat aoc-puzzle-inputs/2022/day09.input | awk 'BEGIN{s=0} {s+=$2}
 * END{print 10*s}' 113160
 *
 *  So my guess is that it shouldn't grow out of control
 */
#include <icecream.hpp>
#include <string>
#include <unordered_set>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

namespace aoc::y2022::d09 {

using Pos = aoc::grid2d::Pos;

// TODO: Move to utils as chebychev distance.
// Chebyshev distance between 2 points
// https://en.wikipedia.org/wiki/Chebyshev_distance
int64_t dist(Pos const p1, Pos const p2) { return std::max(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y)); }

std::unordered_map<char, Pos> const direction = {
    {'R', Pos{1, 0}},
    {'U', Pos{0, -1}},
    {'L', Pos{-1, 0}},
    {'D', Pos{0, 1}},
};

struct Node {
    int64_t count_{};
    Pos current_{};
    std::unique_ptr<Node> next_{};

    Node(int64_t const count) : count_{count} {
        if (count > 0) {
            next_ = std::make_unique<Node>(count - 1);
        }
    }

    // Only to be used by the head
    std::vector<Pos> move(char const dir, int64_t const steps) {
        std::vector<Pos> out{};
        // We can go back to my initial attempt and do the step in one go
        // instead of iterating step for step. We just need to handle the 2
        // cases where the tail has to follow more than one step, if it does we
        // can check for the closest candidate around the reference, if it just
        // have to move one step, we can do what we do now.
        for (int64_t i{0}; i < steps; i++) {
            current_ += direction.at(dir);
            if (next_) {
                auto const visited = next_->move(current_);
                out.insert(out.end(), visited.cbegin(), visited.cend());
            }
        }
        return out;
    }

    std::vector<Pos> move(Pos const ref) {
        if (dist(ref, current_) < 2) {
            return {};
        }

        // ok, so if it's on the same row or col, move within the row/col
        // If not, move diagonally towards head
        std::vector<Pos> directions{Pos{-1, 0}, Pos{1, 0}, Pos{0, -1}, Pos{0, 1}};
        if (ref.x != current_.x && ref.y != current_.y) {
            directions = {
                Pos{-1, -1},
                Pos{-1, 1},
                Pos{1, -1},
                Pos{1, 1},
            };
        }

        Pos closest{current_};
        int64_t closest_distance{INT64_MAX};
        for (auto const& dir : directions) {
            Pos const cand{current_ + dir};
            int64_t cand_distance{dist(ref, cand)};
            if (cand_distance < closest_distance) {
                closest = cand;
                closest_distance = cand_distance;
            }
        }

        current_ = closest;
        Pos diff{current_ - ref};

        if (next_) {
            return next_->move(current_);
        }

        std::vector<Pos> visited{};
        for (int64_t i{0}; i < closest_distance; i++) {
            visited.push_back(closest + i * diff);
        }

        if (next_) {
            return next_->move(current_);
        }
        return visited;
    }

    void print() const {
        std::vector<std::pair<Pos, char>> parts{
            {current_, 'H'},
        };
        next_->get_positions(parts);
        int64_t min_x{0};
        int64_t min_y{0};
        int64_t max_x{0};
        int64_t max_y{0};
        for (auto const& [pos, _] : parts) {
            if (pos.x < min_x) {
                min_x = pos.x;
            }
            if (pos.x > max_x) {
                max_x = pos.x;
            }
            if (pos.y < min_y) {
                min_y = pos.y;
            }
            if (pos.y > max_y) {
                max_y = pos.y;
            }
        }
        int64_t sz_y{std::max(5l, max_y - min_y + 1)};
        int64_t sz_x{std::max(5l, max_x - min_x + 1)};
        std::vector<std::vector<char>> grid(sz_y, std::vector<char>(sz_x, '.'));
        grid.at(0 - min_y).at(0 - min_x) = 's';
        for (auto it = parts.rbegin(); it != parts.rend(); it++) {
            auto const& [pos, ch] = *it;
            grid.at(pos.y - min_y).at(pos.x - min_x) = ch;
        }
        for (std::size_t y{0}; y < grid.size(); y++) {
            for (std::size_t x{0}; x < grid.at(0).size(); x++) {
                std::cout << grid.at(y).at(x);
            }
            std::cout << std::endl;
        }
    }

    void get_positions(std::vector<std::pair<Pos, char>>& parts) {
        parts.emplace_back(std::make_pair(current_, count_ + '0'));
        if (next_) {
            next_->get_positions(parts);
        }
        return;
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Node head(1);
    std::unordered_set<Pos, Pos::Hash> visited{Pos{0, 0}};
    for (auto const& line : inp) {
        auto const steps = string_utils::numbers_from_string(line);
        assert(steps.at(0) > 0);
        assert(steps.size() == 1u);

        auto const visits = head.move(line.at(0), steps.at(0));
        for (auto const vis : visits) {
            visited.insert(vis);
        }
    }
    return visited.size();
}

void print_visited(std::unordered_set<Pos, Pos::Hash> const& visited) {
    int64_t min_x{INT64_MAX};
    int64_t min_y{INT64_MAX};
    int64_t max_x{INT64_MIN};
    int64_t max_y{INT64_MIN};
    for (auto const& pos : visited) {
        if (pos.x < min_x) {
            min_x = pos.x;
        }
        if (pos.x > max_x) {
            max_x = pos.x;
        }
        if (pos.y < min_y) {
            min_y = pos.y;
        }
        if (pos.y > max_y) {
            max_y = pos.y;
        }
    }

    int64_t sz_y{max_y - min_y + 1};
    int64_t sz_x{max_x - min_x + 1};
    std::vector<std::vector<char>> grid(sz_y, std::vector<char>(sz_x, '.'));
    for (auto const& pos : visited) {
        grid.at(pos.y - min_y).at(pos.x - min_x) = '#';
    }
    for (std::size_t y{0}; y < grid.size(); y++) {
        for (std::size_t x{0}; x < grid.at(0).size(); x++) {
            std::cout << grid.at(y).at(x);
        }
        std::cout << std::endl;
    }
}

int64_t solve_2(std::vector<std::string> inp) {
    Node head(9);
    std::unordered_set<Pos, Pos::Hash> visited{Pos{0, 0}};
    for (auto const& line : inp) {
        auto const steps = string_utils::numbers_from_string(line);
        assert(steps.at(0) > 0);
        assert(steps.size() == 1u);

        auto const visits = head.move(line.at(0), steps.at(0));
        for (auto const vis : visits) {
            visited.insert(vis);
        }
    }
    return visited.size();
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(std::vector<std::string>{sample.cbegin(), sample.cbegin() + 1}) == 4);
    assert(solve_1(std::vector<std::string>{sample.cbegin(), sample.cbegin() + 2}) == 7);
    assert(solve_1(std::vector<std::string>{sample.cbegin(), sample.cbegin() + 3}) == 9);
    assert(solve_1(std::vector<std::string>{sample.cbegin(), sample.cbegin() + 4}) == 9);
    assert(solve_1(std::vector<std::string>{sample.cbegin(), sample.cbegin() + 5}) == 10);
    assert(solve_1(sample) == 13);
    assert(solve_2(sample) == 1);

    auto sample1 = aoc::utils::read_input("day09-sample-1.input");
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 1}) == 1);
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 2}) == 1);
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 3}) == 4);
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 4}) == 4);
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 5}) == 8);
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 6}) == 13);
    assert(solve_2(std::vector<std::string>{sample1.cbegin(), sample1.cbegin() + 7}) == 25);
    assert(solve_2(sample1) == 36);
}

};  // namespace aoc::y2022::d09

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2022::d09::solve_1(inp);
        assert(part1 == 5902);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2022::d09::solve_2(inp);
        assert(part2 == 2445);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2022::d09::samples, solve_1_wrapper, solve_2_wrapper, input);
}
