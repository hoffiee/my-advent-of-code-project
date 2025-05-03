/**
 * https://adventofcode.com/2023/day/16
 */
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d16 {

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

namespace Dir {
constexpr Pos Up = {0, -1};
constexpr Pos Right = {1, 0};
constexpr Pos Down = {0, 1};
constexpr Pos Left = {-1, 0};
}  // namespace Dir

std::vector<Pos> const dirs{Dir::Up, Dir::Right, Dir::Down, Dir::Left};

using Grid = std::vector<std::vector<char>>;

void print(Grid const& grid) {
    for (size_t r{1}; r < grid.size() - 1u; r++) {
        for (size_t c{1}; c < grid.front().size() - 1u; c++) {
            if (grid[r][c] == '0') {
                std::cout << ' ';
                continue;
            }
            std::cout << grid[r][c];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Grid create_grid(std::vector<std::string> const& inp) {
    Grid grid(inp.size() + 2, std::vector<char>(inp.front().size() + 2, '*'));
    for (size_t r{0}; r < inp.size(); r++) {
        for (size_t c{0}; c < inp.front().size(); c++) {
            switch (inp[r][c]) {
                case '.':
                case '/':
                case '\\':
                case '|':
                case '-': {
                    grid[r + 1][c + 1] = inp[r][c];
                    break;
                }
                default: {
                    assert(false);
                    break;
                }
            }
        }
    }
    return grid;
}

struct PosDir {
    Pos pos;
    Pos dir;
};

struct PosDirHash {
    std::size_t operator()(const PosDir& c) const {
        return std::hash<int64_t>()(c.pos.real()) ^ (std::hash<int64_t>()(c.pos.imag()) << 8);
    }
};

struct PosDirEqual {
    bool operator()(PosDir const& lhs, PosDir const& rhs) const {
        return lhs.pos.real() == rhs.pos.real() && lhs.pos.imag() == rhs.pos.imag() &&
               lhs.dir.real() == rhs.dir.real() && lhs.dir.imag() == rhs.dir.imag();
    }
};

std::unordered_map<PosDir, bool, PosDirHash, PosDirEqual> loop_detection{};

struct Laser {
    Pos position{};
    Pos direction{};

    Laser(Grid const& grid, Grid& visited, Pos const pos, Pos const dir) : position{pos}, direction{dir} {
        while (true) {
            // IC(position, direction, grid[position.imag()][position.real()]);
            if (grid[position.imag()][position.real()] == '*') {
                return;
            }

            if (loop_detection.contains(PosDir{position, direction})) {
                // Ok so we've been here before, we're finito!
                return;
            }

            loop_detection[PosDir{position, direction}] = true;

            visited[position.imag()][position.real()]++;
            switch (grid[position.imag()][position.real()]) {
                case ('*'): {
                    assert(false);
                    // reach the edge, this laser is dead
                    return;
                }
                case ('.'): {
                    position += direction;
                    break;
                }
                case ('/'): {
                    if (direction == Dir::Up) {
                        position += Dir::Right;
                        direction = Dir::Right;
                    } else if (direction == Dir::Right) {
                        position += Dir::Up;
                        direction = Dir::Up;
                    } else if (direction == Dir::Down) {
                        position += Dir::Left;
                        direction = Dir::Left;
                    } else if (direction == Dir::Left) {
                        position += Dir::Down;
                        direction = Dir::Down;
                    } else {
                        assert(false);
                    }
                    break;
                }
                case ('\\'): {
                    if (direction == Dir::Up) {
                        position += Dir::Left;
                        direction = Dir::Left;
                    } else if (direction == Dir::Right) {
                        position += Dir::Down;
                        direction = Dir::Down;
                    } else if (direction == Dir::Down) {
                        position += Dir::Right;
                        direction = Dir::Right;
                    } else if (direction == Dir::Left) {
                        position += Dir::Up;
                        direction = Dir::Up;
                    } else {
                        assert(false);
                    }
                    break;
                }
                case ('|'): {
                    if (direction == Dir::Left || direction == Dir::Right) {
                        Laser(grid, visited, position + Dir::Up, Dir::Up);
                        Laser(grid, visited, position + Dir::Down, Dir::Down);
                        return;
                    }
                    position += direction;
                    break;
                }
                case ('-'): {
                    if (direction == Dir::Up || direction == Dir::Down) {
                        Laser(grid, visited, position + Dir::Left, Dir::Left);
                        Laser(grid, visited, position + Dir::Right, Dir::Right);
                        return;
                    }
                    position += direction;
                    break;
                }
                default: {
                    assert(false);
                    break;
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Laser const& l) {
        os << l.position.real() << "|" << l.position.imag();
        os << "->" << l.direction.real() << "|" << l.direction.imag();
        return os;
    }
};

int64_t solver(Grid const& grid, PosDir start) {
    Grid visited(grid.size(), std::vector<char>(grid.front().size(), '0'));
    loop_detection.clear();
    Laser(grid, visited, start.pos, start.dir);
    int64_t count{0};
    for (size_t r{1}; r < visited.size() - 1u; r++) {
        for (size_t c{1}; c < visited.front().size() - 1u; c++) {
            if (visited[r][c] != '0') {
                count++;
            }
        }
    }
    return count;
}

int64_t solve_1(std::vector<std::string> inp) {
    auto grid = create_grid(inp);
    return solver(grid, PosDir{Pos{1, 1}, Dir::Right});
}

int64_t solve_2(std::vector<std::string> inp) {
    auto grid = create_grid(inp);
    int64_t max_tiles{0};

    Pos rb_corner{static_cast<int64_t>(grid.front().size() - 2u), static_cast<int64_t>(grid.size() - 2u)};
    for (int64_t c{1}; c < static_cast<int64_t>(grid.front().size()) - 1; c++) {
        max_tiles = std::max(max_tiles, solver(grid, PosDir{Pos{c, 1}, Dir::Down}));
        max_tiles = std::max(max_tiles, solver(grid, PosDir{Pos{c, rb_corner.imag()}, Dir::Up}));
    }

    for (int64_t r{1}; r < static_cast<int64_t>(grid.size()) - 1; r++) {
        max_tiles = std::max(max_tiles, solver(grid, PosDir{Pos{1, r}, Dir::Right}));
        max_tiles = std::max(max_tiles, solver(grid, PosDir{Pos{rb_corner.real(), r}, Dir::Left}));
    }

    return max_tiles;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 46);
    assert(solve_2(sample) == 51);
}

};  // namespace aoc::y2023::d16

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2023::d16::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2023::d16::solve_2(inp);
        assert(part2 > 7542);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2023::d16::samples, solve_1_wrapper, solve_2_wrapper, input);
}
