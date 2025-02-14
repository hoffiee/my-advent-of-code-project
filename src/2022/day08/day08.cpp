#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Tree {
    int _height;
    bool _visible;
    int _scenic_score = 1;
    Tree(int height, bool visible) : _height(height), _visible(visible) {}
};

namespace {
using Grid = std::vector<std::vector<Tree>>;
}

[[maybe_unused]] static void print(Grid& grid) {
    for (auto row : grid) {
        for (auto col : row) {
            std::cout << col._visible << "|" << col._scenic_score << " ";
        }
        std::cout << std::endl;
    }
}

static int set_if_visible(Tree& tree, int max) {
    if (tree._height > max) {
        tree._visible = true;
        max = tree._height;
    }
    return max;
}

static void count_scenic_score(Grid& grid, ssize_t row, ssize_t col) {
    int height = grid.at(row).at(col)._height;

    /* up */
    {
        int count = 0;
        for (ssize_t r = row - 1; r >= 0; --r) {
            ++count;
            if (grid.at(r).at(col)._height >= height) {
                break;
            }
        }
        grid.at(row).at(col)._scenic_score *= count;
    }

    /* down */
    {
        int count = 0;
        for (ssize_t r = row + 1; r < static_cast<ssize_t>(grid.size()); ++r) {
            ++count;
            if (grid.at(r).at(col)._height >= height) {
                break;
            }
        }
        grid.at(row).at(col)._scenic_score *= count;
    }

    /* left */
    {
        int count = 0;
        for (ssize_t c = col - 1; c >= 0; --c) {
            ++count;
            if (grid.at(row).at(c)._height >= height) {
                break;
            }
        }
        grid.at(row).at(col)._scenic_score *= count;
    }

    /* right */
    {
        int count = 0;
        for (ssize_t c = col + 1; c < static_cast<ssize_t>(grid.at(row).size()); ++c) {
            ++count;
            if (grid.at(row).at(c)._height >= height) {
                break;
            }
        }
        grid.at(row).at(col)._scenic_score *= count;
    }
}

Grid preprocess(std::vector<std::string> input) {
    Grid grid;
    for (size_t i = 0; i < input.size(); ++i) {
        std::vector<Tree> row;
        grid.push_back(std::move(row));
        for (auto height : input.at(i)) {
            grid.back().emplace_back(height - '0', false);
        }
    }
    return grid;
}

int64_t solve_1(std::vector<std::string> input) {
    auto grid = preprocess(input);
    /* left to right */
    for (size_t row = 1; row < grid.size() - 1; ++row) {
        int max = grid.at(row).front()._height;
        for (size_t col = 1; col < grid.front().size() - 1; ++col) {
            max = set_if_visible(grid.at(row).at(col), max);
        }
    }

    /* right to left */
    for (size_t row = 1; row < grid.size() - 1; ++row) {
        int max = grid.at(row).back()._height;
        for (size_t col = grid.front().size() - 2; col > 0; --col) {
            max = set_if_visible(grid.at(row).at(col), max);
        }
    }

    /* top to bottom */
    for (size_t col = 1; col < grid.front().size() - 1; ++col) {
        int max = grid.front().at(col)._height;
        for (size_t row = 1; row < grid.size() - 1; ++row) {
            max = set_if_visible(grid.at(row).at(col), max);
        }
    }

    /* bottom to top */
    for (size_t col = 1; col < grid.front().size() - 1; ++col) {
        int max = grid.back().at(col)._height;
        for (size_t row = grid.size() - 2; row > 0; --row) {
            max = set_if_visible(grid.at(row).at(col), max);
        }
    }

    int sum = std::accumulate(grid.cbegin(), grid.cend(), 0, [](int row_sum, const std::vector<Tree>& col) {
        return std::accumulate(col.begin(), col.end(), row_sum,
                               [](int acc2, const Tree& tree) { return acc2 + static_cast<int>(tree._visible); });
    });

    return 2 * grid.size() + 2 * grid.front().size() - 4 + sum;
}

int64_t solve_2(std::vector<std::string> input) {
    auto grid = preprocess(input);
    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid.at(row).size(); ++col) {
            count_scenic_score(grid, row, col);
        }
    }

    int max = 0;
    for (auto& row : grid) {
        for (auto& col : row) {
            if (col._scenic_score > max) {
                max = col._scenic_score;
            }
        }
    }
    return max;
}
