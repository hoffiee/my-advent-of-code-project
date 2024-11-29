#include AOC_HEADER

#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

static void move(int& x, int& y, char dir) {
    switch (dir) {
        case '^':
            ++y;
            break;
        case '>':
            ++x;
            break;
        case 'v':
            --y;
            break;
        case '<':
            --x;
            break;
    }
}

int solve(std::string input, bool split) {
    std::unordered_map<std::pair<int, int>, int, pair_hash> visited_houses{
        {std::make_pair(0, 0), 2}  // Starting points counts as visited as well
    };
    int x = 0;
    int y = 0;
    int x_robo = 0;
    int y_robo = 0;
    int santa = true;

    for (auto dir : input) {
        if (santa || !split) {
            santa = false;
            move(x, y, dir);
            visited_houses[std::make_pair(x, y)]++;
        } else {
            santa = true;
            move(x_robo, y_robo, dir);
            visited_houses[std::make_pair(x_robo, y_robo)]++;
        }
    }
    return static_cast<int>(visited_houses.size());
}
