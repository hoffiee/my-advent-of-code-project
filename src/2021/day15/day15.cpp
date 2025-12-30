/**
 * https://adventofcode.com/2021/day/15
 */
#include <icecream.hpp>
#include <queue>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2021::d15 {

using Pos = aoc::grid2d::Pos;
using Edge = std::pair<Pos, int64_t>;

struct Graph {
    int64_t sz_x_{0};
    int64_t sz_y_{0};
    int64_t multiple_{1};
    std::vector<std::vector<int64_t>> grid_{};

    Graph(std::vector<std::string> const& inp, int64_t const multiple)
        : sz_x_{static_cast<int64_t>(inp.at(0).size())}, sz_y_{static_cast<int64_t>(inp.size())}, multiple_{multiple} {
        grid_ = std::vector<std::vector<int64_t>>(sz_y_, std::vector<int64_t>(sz_x_, 0));
        for (size_t i{0u}; i < inp.size(); i++) {
            for (size_t j{0u}; j < inp.at(0).size(); j++) {
                grid_.at(i).at(j) = inp.at(i).at(j) - '0';
            }
        }
    }

    bool valid(Pos const pos) const {
        if (pos.x < 0 || multiple_ * sz_x_ <= pos.x) {
            return false;
        }
        if (pos.y < 0 || multiple_ * sz_y_ <= pos.y) {
            return false;
        }
        return true;
    };

    int64_t operator[](Pos const pos) const {
        assert(valid(pos));

        int64_t y_inc{pos.y / sz_y_};
        int64_t x_inc{pos.x / sz_x_};

        int64_t unwrapped{grid_.at(pos.y % sz_y_).at(pos.x % sz_x_) + y_inc + x_inc};
        int64_t wrapped = (unwrapped - 1) % (9 - 1 + 1) + 1;
        return wrapped;
    }

    std::vector<Edge> neighbours(Pos const pos) const {
        std::vector<Edge> out{};
        std::vector<Pos> const directions{
            Pos{-1, 0},
            Pos{1, 0},
            Pos{0, -1},
            Pos{0, 1},
        };

        for (auto const& dir : directions) {
            Pos cand{pos + dir};
            if (!valid(cand)) {
                continue;
            }

            out.push_back(Edge{cand, (*this)[cand]});
        }

        return out;
    };

    std::vector<Edge> vertices() const {
        std::vector<Edge> out{};
        for (int64_t i{0}; i < multiple_ * sz_y_; i++) {
            for (int64_t j{0}; j < multiple_ * sz_x_; j++) {
                Pos pos{j, i};
                out.emplace_back(Edge{pos, (*this)[pos]});
            }
        }
        return out;
    }
};

struct Dijkstra {
    Graph const& graph_;
    std::unordered_map<Pos, int64_t, Pos::Hash> dist_{};

    struct QueueCmp {
        bool operator()(Edge const& lhs, Edge const& rhs) { return std::get<1>(lhs) > std::get<1>(rhs); }
    };

    Dijkstra(Graph const& graph) : graph_{graph} {}

    int64_t solve(Pos const source, Pos const target) {
        std::priority_queue<Edge, std::vector<Edge>, QueueCmp> queue{};

        dist_[source] = 0;
        queue.push(Edge{source, 0});
        for (auto const& v : graph_.vertices()) {
            if (std::get<0>(v) == source) {
                continue;
            }
            dist_[std::get<0>(v)] = INT64_MAX;
            queue.push(Edge{std::get<0>(v), INT64_MAX});
        }

        while (!queue.empty()) {
            auto const u = queue.top();
            queue.pop();

            for (auto const& v : graph_.neighbours(std::get<0>(u))) {
                int64_t alt{std::get<1>(v) + dist_[std::get<0>(u)]};
                if (alt < dist_[std::get<0>(v)]) {
                    dist_[std::get<0>(v)] = alt;
                    queue.push(Edge{std::get<0>(v), alt});
                }

                if (std::get<0>(u) == target) {
                    return dist_[target];
                }
            }
        }
        return dist_.at(target);
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Graph graph(inp, 1);
    Dijkstra solver{graph};
    Pos const target{
        graph.sz_x_ - 1,
        graph.sz_y_ - 1,
    };
    int64_t res{solver.solve(Pos{0, 0}, target)};
    return res;
}

int64_t solve_2(std::vector<std::string> inp) {
    Graph graph(inp, 5);
    Dijkstra solver{graph};
    Pos const target{
        5 * graph.sz_x_ - 1,
        5 * graph.sz_y_ - 1,
    };
    int64_t res{solver.solve(Pos{0, 0}, target)};
    return res;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 40);
    assert(solve_2(sample) == 315);
}

};  // namespace aoc::y2021::d15

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = aoc::y2021::d15::solve_1(inp);
        assert(res == 687);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = aoc::y2021::d15::solve_2(inp);
        assert(res == 2957);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2021::d15::samples, solve_1_wrapper, solve_2_wrapper, input);
}
