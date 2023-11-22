#include AOC_HEADER

#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

/* TODO Make grid an class/struct and make it oop instead */
namespace {
using Grid = std::vector<std::vector<int>>;
using Modifier = std::function<void(Grid& grid, char action, int row, int col)>;
}  // namespace

struct Point {
    int x;
    int y;
    friend std::istream& operator>>(std::istream& is, Point& point) { return is >> point.x >> point.y; }
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << point.x << ":" << point.y;
        return os;
    }
};

static void modifier_1(Grid& grid, char action, int row, int col) {
    switch (action) {
        case 'p':
            grid.at(row).at(col) = 1;
            break;
        case 'n':
            grid.at(row).at(col) = 0;
            break;
        case 't':
            grid.at(row).at(col) = (grid.at(row).at(col) >= 1) ? 0 : 1;
            break;
    }
}

static void modifier_2(Grid& grid, char action, int row, int col) {
    switch (action) {
        case 'p':
            ++grid.at(row).at(col);
            break;
        case 'n':
            grid.at(row).at(col) = std::max(0, grid.at(row).at(col) - 1);
            break;
        case 't':
            grid.at(row).at(col) += 2;
            break;
    }
}

static void grid_set_in_range(Grid& grid, Modifier modifier, char action, Point& a, Point& b) {
    for (int row = a.y; row <= b.y; ++row) {
        for (int col = a.x; col <= b.x; ++col) {
            modifier(grid, action, row, col);
        }
    }
}

static void apply_instructions_to_grid(Grid& grid, std::vector<std::string>& instructions, Modifier modifier) {
    for (auto& cmd : instructions) {
        std::stringstream ss(cmd);
        char action;
        Point a;
        Point b;
        ss >> action >> a >> b;
        grid_set_in_range(grid, modifier, action, a, b);
    }
}

std::pair<int, int> solve(std::vector<std::string>& instructions) {
    Grid grid_1(1000, std::vector(1000, 0));
    Grid grid_2(1000, std::vector(1000, 0));

    apply_instructions_to_grid(grid_1, instructions, modifier_1);
    apply_instructions_to_grid(grid_2, instructions, modifier_2);

    int count_lights_on = 0;
    int sum_brightness = 0;
    for (size_t row = 0; row < grid_1.size(); ++row) {
        for (size_t col = 0; col < grid_1.at(row).size(); ++col) {
            if (grid_1.at(row).at(col) > 0) {
                ++count_lights_on;
            }
            sum_brightness += grid_2.at(row).at(col);
        }
    }

    return {count_lights_on, sum_brightness};
}
