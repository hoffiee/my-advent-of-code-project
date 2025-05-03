/* TODO: This is broken now and needs to be fixed... */
#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

static const int height = 1000;
static const int width = 1000;

namespace {
using std::cout;
using std::endl;
using std::string;
using std::vector;
struct limit {
    int min;
    int max;
};
}  // namespace

struct map {
   public:
    vector<vector<char>> map = vector<vector<char>>(height, vector<char>(width, ' '));
    limit x_limits = {500, 500};
    limit y_limits = {0, 0};
    void update_limits(int x, int y);
    void print();
};

void map::update_limits(int x, int y) {
    if (x < x_limits.min) {
        x_limits.min = x;
    }
    if (x > x_limits.max) {
        x_limits.max = x;
    }
    if (y < y_limits.min) {
        y_limits.min = y;
    }
    if (y > y_limits.max) {
        y_limits.max = y;
    }
}

void map::print() {
    for (int y = 0; y < y_limits.max + 2; ++y) {
        for (int x = 400; x < 600; ++x) {
            cout << map.at(y).at(x);
        }
        cout << endl;
    }
}

struct sand {
   public:
    int x = 500;
    int y = 0;
    bool step(map&, bool consider_limits);
    bool inside_limits(limit x_limit, limit y_limit);
};

bool sand::step(map& m, bool consider_limits) {
    bool moved = false;
    int x_prev = x;
    if (m.map.at(y + 1).at(x) == ' ') {
        m.map.at(y + 1).at(x) = 'o';
        moved = true;
    } else if (m.map.at(y + 1).at(x - 1) == ' ') {
        m.map.at(y + 1).at(x - 1) = 'o';
        x -= 1;
        moved = true;

    } else if (m.map.at(y + 1).at(x + 1) == ' ') {
        m.map.at(y + 1).at(x + 1) = 'o';
        x += 1;
        moved = true;
    }
    if (moved) {
        m.map.at(y).at(x_prev) = ' ';
        y += 1;
    }
    return moved;
}

bool sand::inside_limits(limit x_limit, limit y_limit) {
    bool valid_position = false;
    if (x_limit.min <= x && x <= x_limit.max) {
        valid_position = true;
    }
    if (y_limit.min <= y && y <= y_limit.max) {
        valid_position &= true;
    }
    return valid_position;
}

map read_and_parse_data(std::vector<std::string> const& input) {
    map m{};
    for (auto const& line : input) {
        std::stringstream ss(line);
        int x = -1;
        int y = -1;
        int x_prev = -1;
        int y_prev = -1;
        char delim;
        while (ss >> x >> delim >> y) {
            /* parse vertical line */
            if (x == x_prev) {
                for (int i_y = std::min(y, y_prev); i_y < std::max(y, y_prev) + 1; ++i_y) {
                    m.map.at(i_y).at(x) = '#';
                }
            }
            /* parse horisontal line */
            else if (y == y_prev) {
                for (int i_x = std::min(x, x_prev); i_x < std::max(x, x_prev) + 1; ++i_x) {
                    m.map.at(y).at(i_x) = '#';
                }
            }
            m.update_limits(x, y);
            x_prev = x;
            y_prev = y;
            char ignore[2];
            ss >> ignore;
        }
    }
    m.map.at(0).at(500) = '+';
    return m;
}

int solve_1(map m) {
    int count = -1;
    bool continue_dropping = true;
    while (continue_dropping) {
        sand s;
        ++count;
        while (s.step(m, true)) {
            if (!s.inside_limits(m.x_limits, m.y_limits)) {
                continue_dropping = false;
                break;
            }
        }
    }
    return count;
}

int solve_2(map m) {
    m.y_limits.max += 2;
    for (int i = 0; i < width; ++i) {
        m.map.at(m.y_limits.max).at(i) = '#';
    }
    int count = 0;
    while (true) {
        sand s;
        ++count;
        while (s.step(m, false)) {
            /* Just step until it comes to a rest */
        }
        if (s.x == 500 && s.y == 0) {
            break;
        }
    }
    return count;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    auto tmp = read_and_parse_data(sample);
    assert(solve_1(tmp) == 24);
    assert(solve_2(tmp) == 93);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto tmp = read_and_parse_data(inp);
        auto part1 = solve_1(tmp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto tmp = read_and_parse_data(inp);
        auto part2 = solve_2(tmp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
