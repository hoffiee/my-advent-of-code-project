#include <chrono>
#include <fstream>
#include <iostream>

/* Solution includes */
#include <algorithm>
#include <cassert>
#include <climits>
#include <queue>
#include <string>
#include <vector>

namespace {
using std::queue;
using std::string;
using std::vector;
using height_map_t = vector<string>;
}  // namespace

struct position_t {
    int x;
    int y;
    int64_t steps;
    bool explored;
    position_t up() { return {x, y + 1}; };
    position_t right() { return {x + 1, y}; };
    position_t down() { return {x, y - 1}; };
    position_t left() { return {x - 1, y}; };
    friend std::ostream& operator<<(std::ostream& os, position_t& pos) {
        os << "(" << pos.x << "," << pos.y << ")";
        return os;
    }
    bool operator==(const position_t& p2) const {
        const position_t& p1 = *this;
        return p1.x == p2.x && p1.y == p2.y;
    }
};

static height_map_t read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    height_map_t hm;
    while (getline(input, line)) {
        hm.emplace_back(line);
    }
    return hm;
}

static vector<position_t> find_position_by_mark(height_map_t& map, char mark) {
    size_t row = 0;
    size_t col = 0;
    vector<position_t> out;
    for (row = 0; row < map.size(); ++row) {
        for (col = 0; col < map.at(row).size(); ++col) {
            if (map.at(row).at(col) == mark) {
                position_t new_pos = {static_cast<int>(col), static_cast<int>(row)};
                out.push_back(new_pos);
            }
        }
    }
    return out;
}

static vector<position_t> adjacent_edges(height_map_t& map, position_t pos) {
    vector<position_t> adjacent;

    adjacent.emplace_back(pos.up());
    adjacent.emplace_back(pos.right());
    adjacent.emplace_back(pos.down());
    adjacent.emplace_back(pos.left());

    int y_max = static_cast<int>(map.size());
    int x_max = static_cast<int>(map.at(y_max - 1).size());

    std::erase_if(adjacent,
                  [y_max, x_max](position_t p) { return p.x < 0 || x_max <= p.x || p.y < 0 || y_max <= p.y; });

    char current_val = map.at(pos.y).at(pos.x);
    std::erase_if(adjacent, [current_val, &map](position_t pos) {
        char val = map.at(pos.y).at(pos.x);
        return !(val <= current_val || val == current_val + 1);
    });

    return adjacent;
}

/**
 * We are looking for the shortest path available, so a breath-first search
 * should do it.
 *
 * https://en.wikipedia.org/wiki/Breadth-first_search
 */
static int bfs(height_map_t& map, position_t start, position_t end) {
    queue<position_t> Q;
    vector<vector<bool>> explored{map.size()};
    for (auto& it : explored) {
        it.resize(map.at(0).size());
    }
    explored.at(start.y).at(start.x) = true;
    Q.push(start);

    while (!Q.empty()) {
        auto v = Q.front();
        Q.pop();
        if (v == end) {
            return static_cast<int>(v.steps);
        }
        for (auto adjacent : adjacent_edges(map, v)) {
            if (!explored.at(adjacent.y).at(adjacent.x)) {
                explored.at(adjacent.y).at(adjacent.x) = true;
                adjacent.steps = v.steps + 1;
                Q.push(adjacent);
            }
        }
    }
    return INT_MAX;
}

static int solution_1(height_map_t map) {
    auto start = find_position_by_mark(map, 'S').at(0);
    auto end = find_position_by_mark(map, 'E').at(0);

    map.at(start.y).at(start.x) = 'a';
    map.at(end.y).at(end.x) = 'z';

    return bfs(map, start, end);
}

static int solution_2(height_map_t map) {
    {
        auto start = find_position_by_mark(map, 'S').at(0);
        map.at(start.y).at(start.x) = 'a';
    }

    auto starts = find_position_by_mark(map, 'a');
    auto end = find_position_by_mark(map, 'E').at(0);
    map.at(end.y).at(end.x) = 'z';

    vector<int> out;
    for (auto& start : starts) {
        out.push_back(bfs(map, start, end));
    }

    return *std::min_element(out.begin(), out.end());
}

static void test_position_and_directions() {
    /* test position and directions */
    position_t pos = {0, 0};
    pos = pos.left();
    assert(pos.x == -1);
    assert(pos.y == 0);

    pos = pos.down();
    assert(pos.x == -1);
    assert(pos.y == -1);

    pos = pos.right();
    assert(pos.x == 0);
    assert(pos.y == -1);

    pos = pos.up();
    assert(pos.x == 0);
    assert(pos.y == 0);
}

static void test_mark_finder() {
    /* test mark finder*/
    height_map_t map = {
        "Sabqponm", "abcryxxl", "accszExk", "acctuvwj", "abdefghi",
    };

    auto mark1 = find_position_by_mark(map, 'S').at(0);
    auto mark2 = find_position_by_mark(map, 'E').at(0);
    auto mark3 = find_position_by_mark(map, 'a');
    assert(mark1.x == 0);
    assert(mark1.y == 0);

    assert(mark2.x == 5);
    assert(mark2.y == 2);

    assert(mark3.at(0).x == 1);
    assert(mark3.at(0).y == 0);
}

static void test_struct_compare() {
    position_t mark1 = {2, 4};
    position_t mark2 = {2, 4};
    /* struct compare */
    assert(mark1 == mark2);

    mark2.x = 3;
    assert(!(mark1 == mark2));

    mark2.y = 1;
    assert(!(mark1 == mark2));
}

static void test_adjacent_edges() {
    height_map_t map = {
        "aabqponm", "abcryxxl", "accszzxk", "acctuvwj", "abdefghi",
    };

    {
        position_t pos = {3, 3};
        auto edges = adjacent_edges(map, pos);
        assert(edges.size() == 4);
        assert(edges.at(0).x == 3 && edges.at(0).y == 4);
        assert(edges.at(1).x == 4 && edges.at(1).y == 3);
        assert(edges.at(2).x == 3 && edges.at(2).y == 2);
        assert(edges.at(3).x == 2 && edges.at(3).y == 3);
    }

    {
        position_t pos = {0, 0};
        auto edges = adjacent_edges(map, pos);
        assert(edges.size() == 2);
        assert(edges.at(0).x == 0 && edges.at(0).y == 1);
        assert(edges.at(1).x == 1 && edges.at(1).y == 0);
    }

    {
        position_t pos = {7, 4};
        auto edges = adjacent_edges(map, pos);
        assert(edges.size() == 2);
        assert(edges.at(0).x == 7 && edges.at(0).y == 3);
        assert(edges.at(1).x == 6 && edges.at(1).y == 4);
    }
}

static void tests() {
    test_position_and_directions();
    test_mark_finder();
    test_struct_compare();
    test_adjacent_edges();
}

static void run_and_check_solutions(string task, int (*solution_1)(height_map_t), int expected_1,
                                    int (*solution_2)(height_map_t), int expected_2) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto input = read_and_parse_data(task);
    std::cout << task << std::endl;
    std::cout << "\ttask 1: " << solution_1(input) << " (" << expected_1 << ")" << std::endl;
    std::cout << "\ttask 2: " << solution_2(input) << " (" << expected_2 << ")" << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "execution time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns"
              << std::endl;
}

int main(void) {
    tests();
    run_and_check_solutions("day12-sample.input", solution_1, 31, solution_2, 29);
    run_and_check_solutions("day12.input", solution_1, 394, solution_2, 2421);
}
