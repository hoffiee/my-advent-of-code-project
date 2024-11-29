#include AOC_HEADER

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

enum Direction : int { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

std::tuple<int, int, int, int> solve(std::string input) {
    int x = 0;
    int y = 0;
    int x_hq = 0;
    int y_hq = 0;
    bool found_hq = false;
    Direction dir = NORTH;

    std::unordered_map<std::pair<int, int>, int, pair_hash> path{{{x, y}, 1}};

    std::stringstream ss(input);
    std::string command;
    while (ss >> command) {
        std::stringstream command_ss(command);
        char rotate;
        int dist;

        command_ss >> rotate;
        command_ss >> dist;

        auto mod = [](int a, int b) { return (a % b + b) % b; };

        switch (rotate) {
            case 'R':
                dir = static_cast<Direction>(mod(dir + 1, 4));
                break;
            case 'L':
                dir = static_cast<Direction>(mod(dir - 1, 4));
                break;
            default:
                throw std::invalid_argument("Input not correct");
        }

        for (int i = 0; i < dist; ++i) {
            switch (dir) {
                case NORTH:
                    y += 1;
                    break;
                case EAST:
                    x += 1;
                    break;
                case SOUTH:
                    y -= 1;
                    break;
                case WEST:
                    x -= 1;
                    break;
                default:
                    throw std::logic_error("rethink this");
            }

            if (!found_hq && path.contains({x, y})) {
                x_hq = x;
                y_hq = y;
                found_hq = true;
            }
            path[{x, y}]++;
        }
    }
    return {x, y, std::abs(x) + std::abs(y), std::abs(x_hq) + std::abs(y_hq)};
}
