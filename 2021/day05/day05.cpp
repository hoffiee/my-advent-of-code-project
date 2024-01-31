/**
 * https://adventofcode.com/2021/day/5
 *
 * cat 2021/day05/day05.input | tr "," " " | awk '{print $1"\n"$2"\n"$4"\n"$5}'
 *
 * gives that a grid of 1000x1000 should be sufficient
 */
#include AOC_HEADER

#include <icecream.hpp>
#include <sstream>

struct Grid {
    int grid[1000][1000];
    int x_min = 1000;
    int y_min = 1000;
    int x_max = 0;
    int y_max = 0;

    void draw(int x, int y);
    void print();
    int count_overlaps();
};

void Grid::draw(int x, int y) {
    x_min = std::min({x_min, x});
    y_min = std::min({y_min, y});
    x_max = std::max({x_max, x});
    y_max = std::max({y_max, y});
    grid[y][x]++;
}

void Grid::print() {
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            if (grid[y][x] > 0) {
                std::cout << grid[y][x];
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Grid::count_overlaps() {
    int count = 0;
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            if (grid[y][x] > 1) {
                count++;
            }
        }
    }
    return count;
}

int solve_1(std::vector<std::string> inp) {
    Grid grid;

    for (auto line: inp) {
        IC(line);
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;

        std::stringstream ss(line);
        char delim = ' ';
        std::string pointer = "";
        ss >> x1 >> delim >> y1 >> pointer >> x2 >> delim >> y2;

        if (x1 == x2) {
            for (int y = std::min({y1, y2}); y <= std::max({y1, y2}); y++) {
                grid.draw(x1, y);
            }
        }
        else if (y1 == y2) {
            for (int x = std::min({x1, x2}); x <= std::max({x1, x2}); x++) {
                grid.draw(x, y1);
            }
        }
    }
    grid.print();
    return grid.count_overlaps();
}

int solve_2(std::vector<std::string> inp) {
    Grid grid;

    for (auto line: inp) {
        IC(line);
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;

        std::stringstream ss(line);
        char delim = ' ';
        std::string pointer = "";
        ss >> x1 >> delim >> y1 >> pointer >> x2 >> delim >> y2;

        if (x1 == x2) {
            for (int y = std::min({y1, y2}); y <= std::max({y1, y2}); y++) {
                grid.draw(x1, y);
            }
        }
        else if (y1 == y2) {
            for (int x = std::min({x1, x2}); x <= std::max({x1, x2}); x++) {
                grid.draw(x, y1);
            }
        }
        else if (std::abs(x2 - x1) == std::abs(y2 - y1)) {
            int k = (y2 - y1)/(x2 - x1);
            int m = y1 - k*x1;
            IC(x1, y1, x2, y2, k, m);
            std::cout << k << " " << m << std::endl;
            for (int x = std::min({x1, x2}); x <= std::max({x1, x2}); x++) {
                grid.draw(x, k*x + m);
            }
        }
    }
    return grid.count_overlaps();
}
