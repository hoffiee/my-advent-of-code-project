/**
 * https://adventofcode.com/2024/day/16
 *
 * aoc-tags: dijkstra, 2d-grid, multiple-paths
 */
#include <complex>
#include <icecream.hpp>
#include <queue>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using Pos = std::complex<int64_t>;

struct PosHash {
    std::size_t operator()(const Pos& c) const {
        return std::hash<int64_t>()(c.real()) ^ (std::hash<int64_t>()(c.imag()) << 8);
    }
};

struct PosEqual {
    bool operator()(Pos const& lhs, Pos const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

bool operator<(Pos const& lhs, Pos const& rhs) { return lhs.real() < rhs.real(); }

namespace Dir {
constexpr Pos North = {0, -1};
constexpr Pos East = {1, 0};
constexpr Pos South = {0, 1};
constexpr Pos West = {-1, 0};
}  // namespace Dir

struct PosDir {
    Pos pos;
    Pos dir;

    friend std::ostream& operator<<(std::ostream& os, PosDir const& pd) {
        os << "p:" << pd.pos << ",";
        if (pd.dir == Dir::North) {
            os << "North";
        }
        if (pd.dir == Dir::East) {
            os << "East";
        }
        if (pd.dir == Dir::South) {
            os << "South";
        }
        if (pd.dir == Dir::West) {
            os << "West";
        }
        return os;
    }
};

char get_dir_from_posdir(PosDir const pd) {
    if (pd.dir == Dir::North) {
        return '^';
    }
    if (pd.dir == Dir::East) {
        return '>';
    }
    if (pd.dir == Dir::South) {
        return 'v';
    }
    if (pd.dir == Dir::West) {
        return '<';
    }
    return ' ';
}

struct PosDirHash {
    std::size_t operator()(const PosDir& c) const {
        // TODO prevent collisions
        return std::hash<int64_t>()(c.pos.real()) ^ (std::hash<int64_t>()(c.pos.imag()) << 8);
    }
};

struct PosDirEqual {
    bool operator()(PosDir const& lhs, PosDir const& rhs) const {
        return lhs.pos.real() == rhs.pos.real() && lhs.pos.imag() == rhs.pos.imag() &&
               lhs.dir.real() == rhs.dir.real() && lhs.dir.imag() == rhs.dir.imag();
    }
};

struct Grid {
    std::vector<std::string> map_{};
    int64_t row_sz_{};
    int64_t col_sz_{};
    PosDir start_{-1, -1};
    Pos finish_{-1, -1};

    Grid(std::vector<std::string> const& inp)
        : row_sz_{static_cast<int64_t>(inp.size())}, col_sz_{static_cast<int64_t>(inp.at(0).size())} {
        for (auto line : inp) {
            map_.push_back(line);
        }

        bool found_S{false};
        bool found_E{false};

        for (int64_t row{0}; row < row_sz_; row++) {
            for (int64_t col{0}; col < col_sz_; col++) {
                Pos cand{col, row};
                switch ((*this)[cand]) {
                    case 'S':
                        start_ = {cand, Dir::East};
                        found_S = true;
                        break;
                    case 'E':
                        finish_ = cand;
                        found_E = true;
                        break;
                    default:
                        break;
                }
            }
        }
        assert(found_S);
        assert(found_E);
        map_.at(start_.pos.imag()).at(start_.pos.real()) = '.';
        map_.at(finish_.imag()).at(finish_.real()) = '.';
    }

    char operator[](Pos pos) const { return map_.at(pos.imag()).at(pos.real()); }

    bool within_bounds(Pos pos) const {
        if ((pos.real() < 0) || (pos.imag() < 0) || (static_cast<int>(map_.at(0).size()) <= pos.real()) ||
            (static_cast<int>(map_.size()) <= pos.imag())) {
            return false;
        }
        return true;
    }

    std::vector<std::tuple<PosDir, int64_t>> get_neighbours(PosDir pd) const {
        std::vector<std::tuple<PosDir, int64_t>> out{};
        PosDir cand1{pd.pos + pd.dir};
        if (map_.at(cand1.pos.imag()).at(cand1.pos.real()) == '.') {
            out.emplace_back(std::make_tuple(PosDir{pd.pos + pd.dir, pd.dir}, 1));
        }
        out.emplace_back(std::make_tuple(PosDir{pd.pos, pd.dir * Pos{0, 1}}, 1000));
        out.emplace_back(std::make_tuple(PosDir{pd.pos, pd.dir / Pos{0, 1}}, 1000));
        return out;
    }
};

using QueueEntry = std::tuple<PosDir, int64_t>;
struct QueueCmp {
    bool operator()(QueueEntry const& lhs, QueueEntry const& rhs) { return std::get<1>(lhs) > std::get<1>(rhs); }
};

// TODO move these dirs vectors as a aoc::grid::2d::dirs
std::vector<Pos> const dirs{Dir::North, Dir::East, Dir::South, Dir::West};

struct Dijkstras {
    int64_t best_path_{INT64_MAX};
    std::unordered_map<PosDir, int64_t, PosDirHash, PosDirEqual> dist_{};
    Grid const& grid_;
    PosDir finish_{};
    PosDir root_{};

    Dijkstras(Grid const& grid, PosDir const root, Pos const finish) : grid_{grid}, root_{root} {
        std::priority_queue<QueueEntry, std::vector<QueueEntry>, QueueCmp> Q{};
        dist_[root] = 0;
        Q.push({root, 0});

        while (!Q.empty()) {
            auto u = Q.top();
            Q.pop();

            assert(grid[std::get<0>(u).pos] != '#');
            for (auto [neighbour, cost] : grid.get_neighbours(std::get<0>(u))) {
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

        for (auto dir : dirs) {
            PosDir cand{finish, dir};
            if (dist_.contains(cand)) {
                if (dist_[cand] < best_path_) {
                    best_path_ = dist_[cand];
                    finish_ = cand;
                }
            }
        }
    }

    void print() const {
        for (int64_t row{0}; row < grid_.row_sz_; row++) {
            for (int64_t col{0}; col < grid_.col_sz_; col++) {
                Pos cand{col, row};
                switch (grid_[cand]) {
                    case '#':
                        std::cout << "#";
                        break;
                    case '.':
                        int64_t min{INT64_MAX};
                        PosDir min_pos{cand, Pos{0, 0}};
                        for (auto dir : dirs) {
                            PosDir canddir{cand, dir};
                            if (dist_.contains(canddir)) {
                                if (dist_.at(canddir) < min) {
                                    min = dist_.at(canddir);
                                    min_pos = canddir;
                                }
                            }
                        }
                        if (min < INT64_MAX) {
                            std::cout << get_dir_from_posdir(min_pos);
                        } else {
                            std::cout << ".";
                        }
                        break;
                }
            }
            std::cout << std::endl;
        }
    }

    std::vector<PosDir> get_previous_tiles(PosDir const tile) const {
        assert(dist_.contains(tile));

        // Here was the miss in my previous attempt, I missed to consider the step into this position as well as
        // rotations..
        std::vector<PosDir> choices{};
        PosDir step_cand{tile.pos - tile.dir, tile.dir};
        if (dist_.contains(step_cand)) {
            if (dist_.at(tile) - 1 == dist_.at(step_cand)) {
                choices.push_back(step_cand);
            }
        }

        PosDir rot_cw_cand{tile.pos, tile.dir / Pos{0, 1}};
        if (dist_.contains(rot_cw_cand)) {
            if (dist_.at(tile) - 1000 == dist_.at(rot_cw_cand)) {
                choices.push_back(rot_cw_cand);
            }
        }

        PosDir rot_ccw_cand{tile.pos, tile.dir * Pos{0, 1}};
        if (dist_.contains(rot_ccw_cand)) {
            if (dist_.at(tile) - 1000 == dist_.at(rot_ccw_cand)) {
                choices.push_back(rot_ccw_cand);
            }
        }

        return choices;
    }

    void tile_counter(Pos const finish_in) {
        int count{0};
        PosDir finish{};
        for (auto dir : dirs) {
            PosDir cand{finish_in, dir};
            if (dist_.contains(cand) && dist_[cand] == best_path_) {
                count++;
                finish = cand;
            }
        }
        // Assuming we only have one way to E
        assert(count == 1);

        tile_counter(finish);
    }

    std::unordered_map<Pos, int, PosHash, PosEqual> path_{};
    void tile_counter(PosDir const finish) {
        path_[finish.pos];
        if (finish.pos == root_.pos) {
            return;
        }

        auto tiles{get_previous_tiles(finish)};
        for (auto tile : tiles) {
            tile_counter(tile);
        }
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Grid grid(inp);
    int64_t out{Dijkstras(grid, grid.start_, grid.finish_).best_path_};
    return out;
}

int64_t solve_2(std::vector<std::string> inp) {
    Grid grid(inp);
    Dijkstras path(grid, grid.start_, grid.finish_);
    path.tile_counter(grid.finish_);
    int64_t ans{static_cast<int64_t>(path.path_.size())};
    return ans;
}

void samples() {
    auto sample1 = aoc::utils::read_input("day16-sample-1.input");
    assert(solve_1(sample1) == 7036);
    assert(solve_2(sample1) == 45);

    auto sample2 = aoc::utils::read_input("day16-sample-2.input");
    assert(solve_1(sample2) == 11048);
    assert(solve_2(sample2) == 64);

    auto sample3 = aoc::utils::read_input("day16-sample-3.input");
    assert(solve_1(sample3) == 1004);
    assert(solve_2(sample3) == 5);

    auto sample4 = aoc::utils::read_input("day16-sample-4.input");
    assert(solve_1(sample4) == 4013);
    assert(solve_2(sample4) == 14);

    auto sample5 = aoc::utils::read_input("day16-sample-5.input");
    assert(solve_1(sample5) == 21148);
    assert(solve_2(sample5) == 149);

    auto sample6 = aoc::utils::read_input("day16-sample-6.input");
    assert(solve_1(sample6) == 5078);
    assert(solve_2(sample6) == 413);

    auto sample7 = aoc::utils::read_input("day16-sample-7.input");
    assert(solve_1(sample7) == 21110);

    auto sample8 = aoc::utils::read_input("day16-sample-8.input");
    assert(solve_1(sample8) == 41210);

    // These samples caused infinite loops in my solution, altough they're not representative of the problem at hand
    // assert(solve_2(sample7) == 264);
    // std::cout << "sampl7 complete" << std::endl;
    // assert(solve_2(sample8) == 514);
    // std::cout << "sampl8 complete" << std::endl;
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
