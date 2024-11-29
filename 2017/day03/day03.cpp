#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_ARRAY_SIZE 20

enum Dir : int {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3,
    MAX = 4,
};

__attribute__((unused)) static void print(std::vector<int> inp) {
    std::cout << "[";
    for (auto it : inp) {
        std::cout << it << ",\t";
    }
    std::cout << "]" << std::endl;
}

__attribute__((unused)) static void print(std::vector<std::vector<int>>& grid, int min, int max) {
    std::cout << std::endl;
    for (int y = min; y <= max; ++y) {
        for (int x = min; x <= max; ++x) {
            if (grid.at(y).at(x) == 0) {
                std::cout << "."
                          << "\t";
                continue;
            }
            std::cout << grid.at(y).at(x) << "\t";
        }
        std::cout << std::endl;
    }
}

static int surrounding_sum(std::vector<std::vector<int>>& grid, int x, int y) {
    int sum = 0;
    for (int row = y - 1; row <= y + 1; ++row) {
        for (int col = x - 1; col <= x + 1; ++col) {
            sum += grid.at(row).at(col);
        }
    }
    return sum;
}

static int solve_2(int input) {
    std::vector<std::vector<int>> grid(MAX_ARRAY_SIZE, std::vector<int>(MAX_ARRAY_SIZE, 0));
    int x = MAX_ARRAY_SIZE / 2 - 1;
    int y = MAX_ARRAY_SIZE / 2 - 1;
    int edge_count = 0;
    int step_count = 1;
    int dist = 2;
    Dir dir = Dir::UP;

    grid.at(y).at(x++) = 1;
    grid.at(y).at(x) = surrounding_sum(grid, x, y);

    while (grid.at(x).at(y) < input) {
        switch (dir) {
            case Dir::UP:
                --y;
                break;
            case Dir::LEFT:
                --x;
                break;
            case Dir::DOWN:
                ++y;
                break;
            case Dir::RIGHT:
                ++x;
                break;
            case Dir::MAX:
                break;
        }

        grid.at(y).at(x) = surrounding_sum(grid, x, y);
        if (grid.at(y).at(x) > input) {
            break;
        }

        if (++step_count >= dist) {
            dir = static_cast<Dir>((static_cast<int>(dir) + 1) % Dir::MAX);
            step_count = 0;
            if (++edge_count >= 4) {
                edge_count = 0;
                dist += 2;
                dir = Dir::UP;
                x++;
                y++;
            }
        }
    }
    print(grid, MAX_ARRAY_SIZE / 2 - 6, MAX_ARRAY_SIZE / 2 + 4);
    return grid.at(y).at(x);
}

std::pair<int, int> solve(int input) {
    if (input <= 1) {
        return {0, 0};
    }
    int n = 1;
    while (n * n < input) {
        n += 2;
    }
    auto dist_from_odd_corner = [&n](const int t) {
        int xpos = (n * n - t) % (n - 1);
        int xneg = std::max(static_cast<int>(0), xpos - n / 2);
        return xpos - 2 * xneg;
    };

    return {
        n - 1 - dist_from_odd_corner(input),
        solve_2(input),
    };
}
