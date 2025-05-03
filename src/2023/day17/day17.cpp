/**
 * https://adventofcode.com/2023/day/17
 *
 * aoc_tags: dijkstra, 2d-grid
 */
#include <cassert>
#include <complex>
#include <functional>
#include <icecream.hpp>
#include <queue>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

template <typename T>
struct Pos_t {
    std::complex<T> pos_;

    Pos_t() = default;
    constexpr Pos_t(T const x, T const y) : pos_{x, y} {}

    T x() const { return pos_.real(); }
    T y() const { return pos_.imag(); }

    bool operator==(Pos_t const& other) const { return pos_.real() == other.x() && pos_.imag() == other.y(); }

    Pos_t operator+(Pos_t const& other) const { return Pos_t{(*this).x() + other.x(), (*this).y() + other.y()}; }

    Pos_t operator*(T const scalar) const { return Pos_t{(*this).x() * scalar, (*this).y() * scalar}; }
    friend Pos_t operator*(T const scalar, Pos_t const& pos) { return pos * scalar; }
    friend Pos_t operator*(Pos_t const& lhs, Pos_t const& rhs) {
        auto tmp = lhs.pos_ * rhs.pos_;
        return Pos_t{tmp.real(), tmp.imag()};
    }
    friend Pos_t operator/(Pos_t const& lhs, Pos_t const& rhs) {
        auto tmp = lhs.pos_ / rhs.pos_;
        return Pos_t{tmp.real(), tmp.imag()};
    }

    friend std::ostream& operator<<(std::ostream& os, Pos_t<T> p) {
        os << "(" << p.x() << "," << p.y() << ")";
        return os;
    }
};

namespace std {
template <typename T>
struct hash<Pos_t<T>> {
    std::size_t operator()(const Pos_t<T>& obj) const {
        std::size_t h1 = std::hash<T>{}(obj.x());
        std::size_t h2 = std::hash<T>{}(obj.y());
        return h1 ^ (h2 << 8);
    }
};
}  // namespace std

template <typename T>
struct PosDir_t : public Pos_t<T> {
    Pos_t<T> dir_;
    PosDir_t() = default;
    PosDir_t(Pos_t<T> pos, Pos_t<T> dir) : Pos_t<T>{pos}, dir_{dir} {}
    T dx() const { return dir_.x(); }
    T dy() const { return dir_.y(); }

    friend std::ostream& operator<<(std::ostream& os, PosDir_t<T> p) {
        std::string dir{};
        if (p.dir_.x() > 0) {
            dir = ">";
        } else if (p.dir_.x() < 0) {
            dir = "<";
        } else if (p.dir_.y() > 0) {
            dir = "v";
        } else if (p.dir_.y() < 0) {
            dir = "^";
        }

        os << "(" << p.x() << "," << p.y() << "," << dir << ")";
        return os;
    }
};

namespace std {
template <typename T>
struct hash<PosDir_t<T>> {
    std::size_t operator()(const PosDir_t<T>& obj) const {
        size_t const h1 = std::hash<T>{}(obj.x());
        size_t const h2 = std::hash<T>{}(obj.y());
        size_t const h3 = std::hash<T>{}(obj.dx());
        size_t const h4 = std::hash<T>{}(obj.dy());
        size_t const hash_first{h1 ^ (h2 << 8)};
        size_t const hash_second{h3 ^ (h4 << 8)};
        return hash_first ^ (hash_second << 16);
        // return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};
}  // namespace std

template <typename T>
struct PosDirStep_t : public PosDir_t<T> {
    T steps_{};
    PosDirStep_t() = default;
    PosDirStep_t(Pos_t<T> pos, Pos_t<T> dir, T steps) : PosDir_t<T>{pos, dir}, steps_{steps} {}

    PosDirStep_t operator+(Pos_t<T> const& other) const {
        Pos_t<T> new_pos{(*this).x() + other.x(), (*this).y() + other.y()};
        return PosDirStep_t{new_pos, this->dir_, steps_};
    }

    friend std::ostream& operator<<(std::ostream& os, PosDirStep_t<T> p) {
        std::string dir{};
        if (p.dir_.x() > 0) {
            dir = ">";
        } else if (p.dir_.x() < 0) {
            dir = "<";
        } else if (p.dir_.y() > 0) {
            dir = "v";
        } else if (p.dir_.y() < 0) {
            dir = "^";
        }

        os << "(" << p.x() << "," << p.y() << "," << dir << "," << p.steps_ << ")";
        return os;
    }
};

namespace std {
template <typename T>
struct hash<PosDirStep_t<T>> {
    std::size_t operator()(const PosDirStep_t<T>& obj) const {
        size_t const h1 = std::hash<T>{}(obj.x());
        size_t const h2 = std::hash<T>{}(obj.y());
        size_t const h3 = std::hash<T>{}(obj.dx());
        size_t const h4 = std::hash<T>{}(obj.dy());
        size_t const h5 = std::hash<T>{}(obj.steps_);
        size_t const pos_hash{h1 ^ (h2 << 8)};
        size_t const dir_hash{h3 ^ (h4 << 8)};
        return pos_hash ^ (dir_hash << 16) ^ (h5 << 32);
    }
};
}  // namespace std

namespace aoc::y2023::d17 {

using Pos = Pos_t<int64_t>;
using PosDir = PosDir_t<int64_t>;
using PosDirStep = PosDirStep_t<int64_t>;

// TODO move these dirs vectors as a aoc::grid::2d::dirs
namespace Dir {
constexpr Pos Up = {0, -1};
constexpr Pos Right = {1, 0};
constexpr Pos Down = {0, 1};
constexpr Pos Left = {-1, 0};
constexpr Pos Rotate = {0, 1};
}  // namespace Dir
std::vector<Pos> const dirs{Dir::Up, Dir::Right, Dir::Down, Dir::Left};

struct Grid {
    int64_t const sz_x_;
    int64_t const sz_y_;
    std::vector<std::vector<int>> data_;

    Grid(std::vector<std::string> const& inp)
        : sz_x_{static_cast<int64_t>(inp.front().size() + 2u)},
          sz_y_{static_cast<int64_t>(inp.size() + 2u)},
          data_(sz_y_, std::vector<int>(sz_x_, 0)) {
        for (size_t row{0}; row < inp.size(); row++) {
            for (size_t col{0}; col < inp.front().size(); col++) {
                int tmp = inp[row][col] - '0';
                assert(tmp > 0);
                (*this)[row + 1][col + 1] = tmp;
            }
        }
    }

    // access by [], [][]
    std::vector<int>& operator[](size_t index) { return data_[index]; }
    const std::vector<int>& operator[](size_t index) const { return data_[index]; }
    int& operator()(size_t outer, size_t inner) { return data_[outer][inner]; }
    const int& operator()(size_t outer, size_t inner) const { return data_[outer][inner]; }

    // TODO Access by Pos etc
    int& operator[](Pos pos) { return data_[pos.y()][pos.x()]; }
    int const& operator[](Pos pos) const { return data_[pos.y()][pos.x()]; }
    int& operator[](PosDir pd) { return data_[pd.y()][pd.x()]; }
    int const& operator[](PosDir pd) const { return data_[pd.y()][pd.x()]; }

    bool contains(Pos pos) const {
        return ((0 < pos.x() && pos.x() < sz_x_ - 1) && (0 < pos.y() && pos.y() < sz_y_ - 1));
    }

    int cost(Pos pos) const {
        if ((*this)[pos] == 0) {
            return INT_MAX;
        }
        return (*this)[pos];
    }

    void print() const {
        for (size_t row{0}; row < data_.size(); row++) {
            for (size_t col{0}; col < data_.front().size(); col++) {
                std::cout << data_[row][col];
            }
            std::cout << std::endl;
        }
    }

    using NeighbourType = std::vector<std::tuple<PosDirStep, int>>;
    virtual NeighbourType neighbours(Pos pos) const {
        NeighbourType out{};
        for (auto const dir : dirs) {
            if ((*this)[pos + dir] > 0) {
                out.push_back({PosDirStep(pos + dir, dir, 1), cost(pos + dir)});
            }
        }
        return out;
    }

    virtual NeighbourType neighbours(PosDirStep pds) const {
        assert(0 <= pds.steps_ && pds.steps_ <= 3);

        NeighbourType out{};
        for (auto const dir : dirs) {
            PosDirStep cand(pds + dir, dir, 1);
            if (pds.dir_ == dir) {
                cand.steps_ = pds.steps_ + 1;
            }

            if ((pds.dir_ == Dir::Up && dir == Dir::Down) || (pds.dir_ == Dir::Down && dir == Dir::Up) ||
                (pds.dir_ == Dir::Left && dir == Dir::Right) || (pds.dir_ == Dir::Right && dir == Dir::Left)) {
                continue;
            }

            if (cand.steps_ > 3) {
                continue;
            }

            if ((*this)[cand] > 0) {
                out.push_back({cand, cost(cand)});
            }
        }
        return out;
    }
};

struct Grid2 : public Grid {
    Grid2(std::vector<std::string> const& inp) : Grid(inp) {}

    NeighbourType neighbours(Pos pos) const override {
        // In this case, we can only traverse 4 steps in each direction
        NeighbourType out{};
        for (auto const dir : dirs) {
            if (!contains(pos + 4 * dir)) {
                continue;
            }

            int64_t cand_cost{0};
            for (int64_t i{1}; i <= 4; i++) {
                cand_cost += cost(pos + i * dir);
            }

            if ((*this)[pos + dir] > 0) {
                out.push_back({PosDirStep(pos + 4 * dir, dir, 4), cand_cost});
            }
        }
        return out;
    }

    NeighbourType neighbours(PosDirStep pds) const override {
        // TODO Do a similar check for part 1
        if (pds.dir_ == Pos(0, 0)) {
            return neighbours(Pos(pds.x(), pds.y()));
        }

        assert(4 <= pds.steps_ && pds.steps_ <= 10);

        NeighbourType out{};

        // One step in the same direction
        if (pds.steps_ + 1 <= 10 && contains(pds + pds.dir_)) {
            PosDirStep cand(pds + pds.dir_, pds.dir_, pds.steps_ + 1);
            out.emplace_back(std::make_tuple(cand, cost(cand)));
        }

        // Test the 2 other directions
        for (auto new_dir : {Pos{pds.dir_ * Dir::Rotate}, Pos{pds.dir_ / Dir::Rotate}}) {
            PosDirStep cand(pds + 4 * new_dir, new_dir, 4);
            if (contains(cand)) {
                int64_t cand_cost{0};
                for (int64_t i{1}; i <= 4; i++) {
                    cand_cost += cost(pds + i * new_dir);
                }
                out.push_back(std::make_tuple(cand, cand_cost));
            }
        }
        return out;
    }
};

using QueueEntry = std::tuple<PosDirStep, int64_t>;
struct QueueCmp {
    bool operator()(QueueEntry const& lhs, QueueEntry const& rhs) { return std::get<1>(lhs) > std::get<1>(rhs); }
};

struct Dijkstra {
    int64_t best_path_{INT64_MAX};
    std::unordered_map<PosDirStep, int64_t> dist_{};
    PosDirStep finish_;

    Dijkstra(Grid const& grid, Pos const source_pos, Pos const target) {
        std::priority_queue<QueueEntry, std::vector<QueueEntry>, QueueCmp> Q{};
        PosDirStep source(source_pos, Pos{0, 0}, 0);
        dist_[source] = 0;
        Q.push({source, 0});

        while (!Q.empty()) {
            auto u = Q.top();
            Q.pop();

            for (auto [neighbour, cost] : grid.neighbours(std::get<0>(u))) {
                if (!dist_.contains(neighbour)) {
                    dist_[neighbour] = INT64_MAX;
                }
                int64_t alt{dist_[std::get<0>(u)] + cost};
                if (alt < dist_[neighbour]) {
                    dist_[neighbour] = alt;
                    Q.push({neighbour, alt});
                }
            }
        }

        bool found{true};
        for (auto dir : dirs) {
            for (int step{1}; step <= 10; step++) {
                PosDirStep cand{target, dir, step};
                if (dist_.contains(cand)) {
                    if (dist_[cand] < best_path_) {
                        best_path_ = dist_[cand];
                        finish_ = cand;
                        found = true;
                    }
                }
            }
        }

        assert(found);
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Pos start{1, 1};
    Pos goal(inp.front().size(), inp.size());

    Grid grid(inp);
    Dijkstra path(grid, start, goal);

    return path.best_path_;
}

int64_t solve_2(std::vector<std::string> inp) {
    Pos start{1, 1};
    Pos goal(inp.front().size(), inp.size());

    Grid2 grid(inp);
    Dijkstra path(grid, start, goal);

    return path.best_path_;
}

void tests() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 102);

    auto sample_1 = aoc::utils::read_input("day17-sample-1.input");
    assert(solve_2(sample_1) == 71);

    assert(solve_2(sample) == 94);
}

}  // namespace aoc::y2023::d17

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2023::d17::solve_1(inp);
        assert(part1 == 942);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2023::d17::solve_2(inp);
        assert(part2 == 1082);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2023::d17::tests, solve_1_wrapper, solve_2_wrapper, input);
}
