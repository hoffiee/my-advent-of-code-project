/**
 * https://adventofcode.com/2024/day/6
 */

#include <omp.h>

#include <complex>
#include <fstream>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

struct ComplexHash {
    std::size_t operator()(const std::complex<int>& c) const {
        return std::hash<int>()(c.real()) ^ (std::hash<int>()(c.imag()) << 8);
    }
};

struct ComplexEqual {
    bool operator()(std::complex<int> const& lhs, std::complex<int> const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

struct Position {
    std::complex<int> current_{};
    std::complex<int> direction_{};

    Position() = default;
    Position(int x, int y, char direction_in) : current_{x, y}, direction_{direction(direction_in)} {}

    Position(std::complex<int> pos, std::complex<int> direction_in) : current_{pos}, direction_{direction_in} {}

    void rotate() {
        auto rot = [](std::complex<int> const& inp) -> std::complex<int> {
            if (inp == std::complex<int>{-1, 0}) {
                return std::complex<int>{0, -1};
            }
            if (inp == std::complex<int>{0, -1}) {
                return std::complex<int>{1, 0};
            }
            if (inp == std::complex<int>{1, 0}) {
                return std::complex<int>{0, 1};
            }
            if (inp == std::complex<int>{0, 1}) {
                return std::complex<int>{-1, 0};
            }
            return std::complex<int>{0, 0};
        };
        direction_ = rot(direction_);
    };

    void step() { current_ += direction_; }

    Position next() const { return Position((current_ + direction_), direction_); }

    char direction() const {
        if (direction_ == std::complex<int>{-1, 0}) {
            return '<';
        }
        if (direction_ == std::complex<int>{0, -1}) {
            return '^';
        }
        if (direction_ == std::complex<int>{1, 0}) {
            return '>';
        }
        if (direction_ == std::complex<int>{0, 1}) {
            return 'v';
        }
        return ' ';
    }

    static std::complex<int> direction(char inp) {
        switch (inp) {
            case '<':
                return std::complex<int>{-1, 0};
            case '^':
                return std::complex<int>{0, -1};
            case '>':
                return std::complex<int>{1, 0};
            case 'v':
                return std::complex<int>{0, 1};
        }
        return {0, 0};
    };

    static Position find_start(std::vector<std::string> const& inp) {
        const std::string valid_directions{"<v^>"};
        bool search{true};
        Position start{};
        for (ssize_t row{0}; row < static_cast<ssize_t>(inp.size()) && search; row++) {
            for (ssize_t col{0}; col < static_cast<ssize_t>(inp.at(row).size()); col++) {
                if (valid_directions.find(inp.at(row).at(col)) != std::string::npos) {
                    start = Position(static_cast<int>(col), static_cast<int>(row), inp.at(row).at(col));
                    search = false;
                    break;
                }
            }
        }
        return start;
    }

    friend std::ostream& operator<<(std::ostream& stream, Position const& pos) {
        stream << "(" << pos.current_.real() << ", " << pos.current_.imag() << "), " << pos.direction();
        return stream;
    }
};

struct PositionHash {
    std::size_t operator()(Position const& p) const {
        return std::hash<int>()(p.current_.real()) ^ (std::hash<int>()(p.current_.imag()) << 8) ^
               (std::hash<int>()(p.direction_.real()) << 16) ^ (std::hash<int>()(p.direction_.imag()) << 32);
    }
};

struct PositionEqual {
    bool operator()(Position const& lhs, Position const& rhs) const {
        return lhs.current_.real() == rhs.current_.real() && lhs.current_.imag() == rhs.current_.imag() &&
               lhs.direction_.real() == rhs.direction_.real() && lhs.direction_.imag() == rhs.direction_.imag();
    }
};

struct Grid {
    std::unordered_map<std::complex<int>, bool, ComplexHash, ComplexEqual> obstacles_{};
    ssize_t row_sz_{};
    ssize_t col_sz_{};

    Grid(std::vector<std::string> const& inp)
        : row_sz_{static_cast<ssize_t>(inp.size())}, col_sz_{static_cast<ssize_t>(inp.at(0).size())} {
        for (ssize_t row{0}; row < row_sz_; row++) {
            for (ssize_t col{0}; col < col_sz_; col++) {
                if (inp.at(row).at(col) == '#') {
                    obstacles_[std::complex<int>(col, row)] = true;
                }
            }
        }
    }

    bool within_bounds(Position const& pos) const {
        if (!(0 <= pos.current_.real() && pos.current_.real() < col_sz_)) {
            return false;
        }
        if (!(0 <= pos.current_.imag() && pos.current_.imag() < row_sz_)) {
            return false;
        }
        return true;
    }

    bool path_available(Position const& pos) const { return !(obstacles_.contains(pos.current_)); }
};

using Path = std::unordered_map<std::complex<int>, bool, ComplexHash, ComplexEqual>;

std::tuple<bool, Path> check_infinite_loop(Grid grid, Position start, std::optional<std::complex<int>> new_obstacle) {
    Path path{};
    path[start.current_];
    std::unordered_map<Position, bool, PositionHash, PositionEqual> turns{};

    if (new_obstacle.has_value()) {
        // Add new object
        grid.obstacles_[new_obstacle.value()];
    }

    Position pos{start};
    bool infinite_loop{false};
    while (!infinite_loop) {
        if (!grid.within_bounds(pos.next())) {
            break;
        }

        if (turns.contains(pos)) {
            // revisiting a turn, loop
            infinite_loop = true;
            break;
        }

        // Rotate until free space, sanity check.
        int rotate_count{0};
        while (!grid.path_available(pos.next())) {
            if (rotate_count == 0) {
                turns[pos];
            }

            pos.rotate();
            assert(rotate_count++ < 3);
        }

        if (turns.contains(pos)) {
            assert(false);
        }

        pos.step();
        path[pos.current_];
    }

    return {infinite_loop, path};
}

int solve_1(std::vector<std::string> inp) {
    auto start = Position::find_start(inp);

    Grid g(inp);

    auto [infinite_loop, path] = check_infinite_loop(g, start, std::nullopt);
    assert(!infinite_loop);

    return path.size();
}

int solve_2(std::vector<std::string> inp) {
    Grid g(inp);
    auto start = Position::find_start(inp);

    auto [infinite_loop, path] = check_infinite_loop(g, start, std::nullopt);
    assert(!infinite_loop);

    path.erase(start.current_);

    // This was the only parallelization I was able to get working for random access iterators as unordered_maps are. I
    // tried for looping over bucket optimization which I didn't get to work..
    int sum{0};
#pragma omp parallel
    {
#pragma omp single
        {
            for (auto const& [pos, visit] : path) {
                static_cast<void>(visit);
#pragma omp task
                {
                    auto res = check_infinite_loop(g, start, pos);
                    int infinite = static_cast<int>(std::get<0>(res));

#pragma omp atomic
                    sum += infinite;
                }
            }
        }
    }

    return sum;
}

int main() {
    std::ifstream input_file;
    // input_file.open(AOC_SAMPLE_INPUT);
    input_file.open(AOC_INPUT);
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::vector<std::string> input;
    std::string line;
    while (getline(input_file, line)) {
        input.push_back(line);
    }

    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}