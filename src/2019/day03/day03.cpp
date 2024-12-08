/**
 * This solution is way to slow, look into what takes time with perf
 */
#include AOC_HEADER

#include <icecream.hpp>
#include <sstream>
#include <unordered_map>

// Could be an idea to switch to a hashmap or something to avoid always
// allocating this amount of memory...
#define GRID_SIZE (1 << 15)
constexpr int grid_offset = GRID_SIZE / 2;

__attribute__((unused)) static void print_grid(std::vector<std::vector<char>> grid) {
    for (auto row : grid) {
        for (auto col : row) {
            std::cout << col;
        }
        std::cout << std::endl;
    }
}

int solve_1(std::vector<std::string>& paths) {
    IC_CONFIG.disable();

    std::vector<std::vector<char>> grid(GRID_SIZE, std::vector<char>(GRID_SIZE, '.'));

    int min_distance = GRID_SIZE * 2;
    bool first_wire = true;
    for (auto path : paths) {
        // IC(path);
        std::string command;
        std::stringstream ss(path);

        int xpos = 0;
        int ypos = 0;
        grid.at(ypos + grid_offset).at(xpos + grid_offset) = 'O';
        while (getline(ss, command, ',')) {
            char dir = command.at(0);
            int length = std::stoi(command.substr(1, command.size()));
            // IC(command, dir, length);

            for (int step = 0; step < length; step++) {
                // Maps direction to grid, directions match  // IC printout...
                const std::unordered_map<char, std::pair<int, int>> directions = {
                    {'R', {0, 1}},
                    {'U', {-1, 0}},
                    {'L', {0, -1}},
                    {'D', {1, 0}},
                };

                ypos += directions.at(dir).first;
                xpos += directions.at(dir).second;
                //  // IC(xpos, ypos);

                if (!first_wire && grid.at(ypos + grid_offset).at(xpos + grid_offset) == '1') {
                    // IC(xpos, ypos);
                    grid.at(ypos + grid_offset).at(xpos + grid_offset) = 'X';

                    int distance = std::abs(xpos) + std::abs(ypos);
                    if (distance <= min_distance) {
                        min_distance = distance;
                    }
                } else {
                    grid.at(ypos + grid_offset).at(xpos + grid_offset) = first_wire ? '1' : 2;
                }
            }
        }
        first_wire = false;
    }

    // print_grid(grid);
    return min_distance;
}

/**
 * I'm probably gonna have to rethink my approach bit here, probably better to
 * keep a map of each wires path, draw the first wire, then when drawing the
 * second wire we lookup whether it crosses the first one, and calculate the
 * score for that intersection
 *
 * TODO:
 * Can I use a unordered map with a int pair as key?
 * https://stackoverflow.com/questions/4870437/pairint-int-pair-as-key-of-unordered-map-issue
 *
 * Yes, but this is slow, can I do a map(x, map(y, length)) instead to reduce
 * lookup times?
 */
typedef std::pair<int, int> pos_t;

struct pos_hash {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

int solve_2(std::vector<std::string>& paths) {
    // IC_CONFIG.disable();

    std::unordered_map<std::pair<int, int>, int, pos_hash> wire_1;

    wire_1[std::make_pair(0, 0)] = 0;

    // IC(paths.at(0));
    std::string command;
    std::stringstream ss(paths.at(0));

    int xpos = 0;
    int ypos = 0;
    int count = 1;
    while (getline(ss, command, ',')) {
        char dir = command.at(0);
        int length = std::stoi(command.substr(1, command.size()));
        // IC(command, dir, length, count);

        for (int step = 0; step < length; step++) {
            const std::unordered_map<char, std::pair<int, int>> directions = {
                {'R', {0, 1}},
                {'U', {-1, 0}},
                {'L', {0, -1}},
                {'D', {1, 0}},
            };
            ypos += directions.at(dir).first;
            xpos += directions.at(dir).second;
            wire_1[std::make_pair(xpos, ypos)] = count++;
        }
    }
    // IC(wire_1);

    int min_steps = INT32_MAX;
    std::unordered_map<std::pair<int, int>, int, pos_hash> wire_2;
    xpos = 0;
    ypos = 0;
    count = 1;
    std::stringstream ss2(paths.at(1));
    while (getline(ss2, command, ',')) {
        char dir = command.at(0);
        int length = std::stoi(command.substr(1, command.size()));
        // IC(command, dir, length, count);

        for (int step = 0; step < length; step++) {
            const std::unordered_map<char, std::pair<int, int>> directions = {
                {'R', {0, 1}},
                {'U', {-1, 0}},
                {'L', {0, -1}},
                {'D', {1, 0}},
            };
            ypos += directions.at(dir).first;
            xpos += directions.at(dir).second;
            auto pos = std::make_pair(xpos, ypos);

            wire_2[pos] = count++;

            if (wire_1.count(pos) > 0) {
                // intersection!
                int steps = wire_1.at(pos) + wire_2.at(pos);
                if (steps < min_steps) {
                    min_steps = steps;
                }
            }
        }
    }
    // IC(wire_1);

    return min_steps;
}
