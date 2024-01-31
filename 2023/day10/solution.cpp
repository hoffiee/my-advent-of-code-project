/**
 * https://adventofcode.com/2023/day/10
 *
 * p2: 27 - fel
 * p2: 29 - fel
 * p2: 52 typ - fel
 * p2: 31 - fel
 * p2: 1561 - fel
 * p2: 153 - fel
 * p2: 154  - to try out (only count . and don't include S)
 * p2: 1547 - fel
 */
#include AOC_HEADER

#include <icecream.hpp>
#include <omp.h>

#include <iostream>
#include <algorithm>

std::vector<std::vector<bool>> internal::possible_paths(std::vector<std::string>& map, ssize_t xs, ssize_t ys) {
    std::vector<std::vector<bool>> paths(3, std::vector<bool>(3, false));
    IC(map, xs, ys);

    // see possible connections from middle
    switch (map[ys][xs]) {
        case '|':
            paths[0][1] = true;
            paths[2][1] = true;
            break;
        case '-':
            paths[1][0] = true;
            paths[1][2] = true;
            break;
        case 'L':
            paths[0][1] = true;
            paths[1][2] = true;
            break;
        case 'J':
            paths[0][1] = true;
            paths[1][0] = true;
            break;
        case '7':
            paths[2][1] = true;
            paths[1][0] = true;
            break;
        case 'F':
            paths[2][1] = true;
            paths[1][2] = true;
            break;
        case '.': break;
        case 'S':
            paths[1][0] = true;
            paths[1][2] = true;
            paths[0][1] = true;
            paths[2][1] = true;
            break;
        default:
            throw std::domain_error("unknown input!");
            break;
    }
    return paths;
}

std::vector<std::vector<bool>> internal::possible_directions(std::vector<std::string> map, ssize_t xs, ssize_t ys) {
    auto paths = possible_paths(map, xs, ys);

    IC(paths);
    // See if the connecting piece connects with the middle
#pragma omp parallel for
    for (ssize_t yi = 0; yi < 3; yi++) {
        for (ssize_t xi = 0; xi < 3; xi++) {
            ssize_t y = ys + yi - 1;
            ssize_t x = xs + xi - 1;

            if (!paths[yi][xi]) {
                continue;
            }

            ssize_t dy = yi - 1;
            ssize_t dx = xi - 1;
            switch (map[y][x]) {
                case '|':
                    // are we aligned with x?
                    paths[yi][xi] = dx == 0;
                    break;
                case '-':
                    // are we aligned with y?
                    paths[yi][xi] = dy == 0;
                    break;
                case 'L':
                    // north, east
                    paths[yi][xi] = (dx == 0 && dy == 1) || (dx == -1 && dy == 0);
                    break;
                case 'J':
                    // north, west
                    paths[yi][xi] = (dx == 0 && dy == 1) || (dx == 1 && dy == 0);
                    break;
                case '7':
                    // spathsh, west
                    paths[yi][xi] = (dx == 0 && dy == -1) || (dx == 1 && dy == 0);
                    break;
                case 'F':
                    // spathsh, east
                    paths[yi][xi] = (dx == 0 && dy == -1) || (dx == -1 && dy == 0);
                    break;
                case 'S':
                    paths[yi][xi] = true;
                    break;
                case '.':
                    paths[yi][xi] = false;
                    break;
                default:
                    throw std::domain_error("Shouldn't end up here?");
            }

        }
    }

    return paths;
}

template<typename T>
static void print_map(std::vector<std::vector<T>>& map) {
    for (auto& row: map) {
        for (auto ch: row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

static void add_border_to_map(std::vector<std::string>& map) {
    // Avoid handling edges of map...
    for (auto& row: map) {
        row.insert(row.begin(), '.');
        row.push_back('.');
    }
    map.insert(map.begin(), std::string(map.at(0).size(), '.'));
    map.emplace_back(std::string(map.at(0).size(), '.'));
}

__attribute__((unused))
static void print_current_position(std::vector<std::string>& map, std::vector<std::vector<bool>>& possible_paths,
        ssize_t xs, ssize_t ys) {
    // Print possible directions
    for (ssize_t yi = -1; yi <= 1; yi++) {
        for (ssize_t xi = -1; xi <= 1; xi++) {
            size_t x = xs + xi;
            size_t y = ys + yi;
            if (map[y][x] == '.') {
                std::cout << ' ';
                continue;
            }
            if (map[y][x] == 'S') {
                // https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
                printf("\x1B[32m%c\033[0m", map[y][x]);
                continue;
            }

            if (possible_paths[yi + 1][xi + 1]) {
                printf("\x1B[32m%c\033[0m", map[y][x]);
                continue;
            }
            printf("\x1B[31m%c\033[0m", map[y][x]);
            continue;
        }
        std::cout << std::endl;
    }
}

static std::tuple<ssize_t, ssize_t> find_start(std::vector<std::string> map) {
    for (size_t yc = 1; yc < map.size() - 1; yc++) {
        for (size_t xc = 1; xc < map.at(yc).size() - 1; xc++) {
            if (map[yc][xc] == 'S') {
                return {xc, yc};
            }
        }
    }
}

int solve_1(std::vector<std::string> inp) {
    icecream::ic.disable();
    add_border_to_map(inp);

    auto [xs, ys] = find_start(inp);

    auto x = xs;
    auto y = ys;

    // Take first available path in every step that we haven't visited
    std::vector<std::vector<int>> count(inp.size(), std::vector(inp.at(0).size(), 0));
    count[ys][xs] = 1;
    int step_count = 1;
    bool moved = true;
    while (moved) {
        auto possible_paths = internal::possible_directions(inp, x, y);

        moved = false;
        for (ssize_t yi = 0; yi < 3 && !moved; yi++) {
            for (ssize_t xi = 0; xi < 3 && !moved; xi++) {
                ssize_t xc = x + xi - 1;
                ssize_t yc = y + yi - 1;
                if (possible_paths[yi][xi] && count[yc][xc] == 0) {
                    step_count++;
                    count[yc][xc] = step_count;
                    y = yc;
                    x = xc;
                    moved = true;
                }
            }
        }
    }

    return static_cast<int>(step_count / 2);
}

static void mark_enclosed(std::vector<std::vector<int>>& enclosed, std::vector<std::vector<int>>& map, ssize_t xs, ssize_t ys) {
    bool north_bound = false;
    for (ssize_t y = ys; y >= 0; y--) {
        if (map[y][xs] > 0) {
            north_bound = true;
            break;
        }
    }
    bool east_bound = false;
    for (ssize_t x = xs; x < static_cast<ssize_t>(map.at(ys).size()); x++) {
        if (map[ys][x] > 0) {
            east_bound = true;
            break;
        }
    }
    bool west_bound = false;
    for (ssize_t x = xs; x >= 0; x--) {
        if (map[ys][x] > 0) {
            west_bound = true;
            break;
        }
    }
    bool south_bound = false;
    for (ssize_t y = ys; y < static_cast<ssize_t>(map.size()); y++) {
        if (map[y][xs] > 0) {
            south_bound = true;
            break;
        }
    }
    if (north_bound && east_bound && south_bound && west_bound) {
        enclosed[ys][xs] = 8;
    }
}

// static void remove_adjacent(std::vector<std::vector<int>>& enclosed) {
//     // Such a lazy way, I should reconsider my approach..
//     bool modified = true;
//     while (modified) {
//         modified = false;
//         for (ssize_t y = 1; y < static_cast<ssize_t>(enclosed.size()) - 1; y++) {
//             for (ssize_t x = 1; x < static_cast<ssize_t>(enclosed.at(y).size()) - 1; x++) {
//                 if (enclosed[y][x] != 8) {
//                     continue;
//                 }
// 
//                 if (enclosed[y-1][x] == 0
//                     || enclosed[y + 1][x] == 0
//                     || enclosed[y][x - 1] == 0
//                     || enclosed[y][x + 1] == 0) {
//                     enclosed[y][x] = 0;
//                     modified = true;
//                 }
//             }
//         }
//     }
// }
//
//
static bool enter_leave_premise(char inp) {
    switch (inp) {
        case '|':
        case 'F':
        case 'J':
        case '7':
        case 'L':
        // case 'S':
            return true;
        default:
            return false;
    }
}

int solve_2(std::vector<std::string> inp) {
    add_border_to_map(inp);

    auto [xs, ys] = find_start(inp);
    IC(xs, ys);

    auto x = xs;
    auto y = ys;

    // Take first available path in every step that we haven't visited
    std::vector<std::vector<int>> count(inp.size(), std::vector(inp.at(0).size(), 0));
    count[ys][xs] = 1;
    int step_count = 1;
    bool moved = true;
    while (moved) {
        auto possible_paths = internal::possible_directions(inp, x, y);

        moved = false;
        for (ssize_t yi = 0; yi < 3 && !moved; yi++) {
            for (ssize_t xi = 0; xi < 3 && !moved; xi++) {
                ssize_t xc = x + xi - 1;
                ssize_t yc = y + yi - 1;
                if (possible_paths[yi][xi] && count[yc][xc] == 0) {
                    step_count++;
                    count[yc][xc] = step_count;
                    y = yc;
                    x = xc;
                    moved = true;
                }
            }
        }
    }
    // IC(count);

    std::vector<std::vector<int>> enclosed(count.size(), std::vector<int>(count.at(0).size(), 0));
#pragma omp parallel for
    for (ssize_t y = 1; y < static_cast<ssize_t>(count.size()) - 1; y++) {
        for (ssize_t x = 1; x < static_cast<ssize_t>(count.at(y).size()) - 1; x++) {
            if (inp[y][x] == '.') {
                mark_enclosed(enclosed, count, x, y);
            }
            if (count[y][x] > 0) {
                enclosed[y][x] = 1;
            }
        }
    }
    // IC(enclosed);

    int sum = 0;

    // print_map(count);
    for (ssize_t y = 1; y < static_cast<ssize_t>(count.size()) - 1; y++) {
        bool inside = false;
        for (ssize_t x = 1; x < static_cast<ssize_t>(count.at(y).size()) - 1; x++) {
            if (count[y][x] > 0 && enter_leave_premise(inp[y][x])) {
                inside = !inside;
                IC(inside, x,y, count[y][x], inp[x][y]);
                continue;
            }

            // if (inside && inp[y][x] == '.') {
            if (inside && count[y][x] == 0) {
                IC(x,y, count[y][x], inp[x][y]);
                sum++;
            }
        }
    }

    // remove_adjacent(enclosed);

    // print_map(enclosed);

    // int sum = 0;
    // for (auto& row: enclosed) {
    //     for (auto elem: row) {
    //         if (elem == 8) {
    //             sum++;
    //         }
    //     }
    // }

    return sum;
}
