/**
 * https://adventofcode.com/2023/day/17
 *
 * My first ever implementation of Dijkstras, yay!
 *
 * Holy moly this is ugly at the moment
 *
 * Resources:
 *  Graphs: Dijkstra's algorithm: https://youtu.be/09_LlHjoEiY?si=AukSVeCqkwerjHWO&t=6198
 *  Graphs on grids: https://youtu.be/09_LlHjoEiY?si=cJefFleWLxIKINJf&t=2442
 *
 *  - Not going too great, let's skip using std::complex and go with Node & pair
 *  for grids instead?
 *
 *  - rethink method for picking neighbours, is that a valid approach?
 *
 * Attempts:
 * p1: 975  -- runtests fails with this approach
 * p1: 979  -- too high
 * p1: 984  -- too high
 */
#include AOC_HEADER

#include <string_utils.h>

#include <icecream.hpp>
#include <complex>
#include <climits>
#include <queue>
#include <unordered_map>

struct Node {
    int _x;
    int _y;
    int _steps;
    int _weight;
    bool _vertical;

    Node(int x, int y, int weight, int steps, bool vertical):
        _x(x), _y(y), _steps(steps), _weight(weight), _vertical(vertical) {};

    Node() {};

    bool operator==(Node const& rhs) const {
        return this->_x == rhs._x && this->_y == rhs._y && this->_steps == rhs._steps && this->_vertical == rhs._vertical;
    }
};

std::ostream& operator<<(std::ostream& os, const Node& obj) {
    os << "[" << obj._x << "," << obj._y << "," << obj._weight << "," << obj._steps << "," << obj._vertical << "]";
    return os;
}

struct customGreater {
    bool operator()(const Node& lhs, const Node& rhs) {
        return lhs._weight > rhs._weight;
    };
};

struct NodeHasher {
    std::size_t operator()(const Node& a) const {
        std::size_t h1 = std::hash<int>{}(a._x);
        std::size_t h2 = std::hash<int>{}(a._y);
        std::size_t h3 = std::hash<int>{}(a._steps);
        std::size_t h4 = std::hash<bool>{}(a._vertical);
        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 4);
    }
};

bool compare_xy_nodes(Node const& lhs, Node const& rhs) {
    // This ignores all fields except for x,y
    return lhs._x == rhs._x && lhs._y == rhs._y;
}

std::vector<Node> neighbours(std::vector<std::string>& inp, Node& u) {
    std::vector<Node> out;

    // TODO I'm not sure this sets the values correctly, investigate a bit,
    // somehow we aren't limiting when steps are in a proper direction...
    if (u._vertical) {
        // we came vertically into our current node, do we accept to move vertically again?
        if (u._steps < 3) {
            if (0 < u._y) {
                out.emplace_back(Node(u._x, u._y-1, inp.at(u._y-1).at(u._x)-'0', u._steps + 1, u._vertical));
            }
            if (static_cast<size_t>(u._y) < inp.size() - 1) {
                out.emplace_back(Node(u._x, u._y+1, inp.at(u._y+1).at(u._x)-'0', u._steps + 1, u._vertical));
            }
        }

        // We can always turn left or right (if within map boundaries)
        if (0 < u._x) {
            out.emplace_back(Node(u._x-1, u._y, inp.at(u._y).at(u._x - 1)-'0', 0, !u._vertical));
        }

        if (static_cast<size_t>(u._x) < inp.front().size() - 1) {
            out.emplace_back(Node(u._x+1, u._y, inp.at(u._y).at(u._x + 1)-'0', 0, !u._vertical));
        }
    }
    else {
        // Continue straight?
        if (u._steps < 3) {
            if (0 < u._x) {
                out.emplace_back(Node(u._x-1, u._y, inp.at(u._y).at(u._x-1)-'0', u._steps+1, u._vertical));
            }
            if (static_cast<size_t>(u._x) < inp.size() - 1) {
                out.emplace_back(Node(u._x+1, u._y, inp.at(u._y).at(u._x+1)-'0', u._steps+1, u._vertical));
            }
        }

        // add up/down
        if (0 < u._y) {
            out.emplace_back(Node(u._x, u._y-1, inp.at(u._y-1).at(u._x)-'0', 0, !u._vertical));
        }
        if (static_cast<size_t>(u._y) < inp.size() - 1) {
            out.emplace_back(Node(u._x, u._y+1, inp.at(u._y+1).at(u._x)-'0', 0, !u._vertical));
        }
    }
    IC(out);
    return out;
}

__attribute__((unused))
void print_inp(std::vector<std::string>& inp) {
    for (auto& row: inp) {
        for (auto ch: row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

__attribute__((unused))
void draw_grid(std::vector<std::string> inp, std::unordered_map<Node, Node, NodeHasher>& prev, Node dst) {
    auto it = dst;
    while (!compare_xy_nodes(it, Node(0,0,0,0,false))) {
        if (it._x - prev[it]._x < 0) {
            inp.at(it._y).at(it._x) = '<';
        }
        else if (it._x - prev[it]._x > 0) {
            inp.at(it._y).at(it._x) = '>';
        }
        else if (it._y - prev[it]._y < 0) {
            inp.at(it._y).at(it._x) = '^';
        }
        else if (it._y - prev[it]._y > 0) {
            inp.at(it._y).at(it._x) = 'v';
        }
        else {
            inp.at(it._y).at(it._x) = '*';
        }
        it = prev[it];
    }
    print_inp(inp);
}

int solve_1(std::vector<std::string> inp) {
    icecream::ic.line_wrap_width(120);
    IC(inp);

    Node dst(static_cast<int>(inp.front().size() - 1),static_cast<int>(inp.size() - 1), 0, 0, false);

    // https://en.wikipedia.org/wiki/Dijkstra's_algorithm#Using_a_priority_queue
    // Leave empty for now, use with [] to create with default false when checking
    std::unordered_map<Node, int, NodeHasher> dist;
    std::unordered_map<Node, bool, NodeHasher> visited;
    std::unordered_map<Node, Node, NodeHasher> prev;

    // TODO: Make it more space efficient and have one queue for each dimension?
    std::priority_queue<Node, std::vector<Node>, customGreater> Q;

    for (int y = 0; y < static_cast<int>(inp.size()); y++) {
        for (int x = 0; x < static_cast<int>(inp.front().size()); x++) {
            for (int steps = 0; steps <= 3; steps++) {
                for (int vertical = 0; vertical <= 1; vertical++) {
                    Node cand(x, y, 999999, steps, vertical);
                    dist[cand] = 999999;
                    visited[cand] = false;
                    Q.push(cand);
                }
            }
        }
    }


    Node srcv(0,0,0,0,false);
    dist[srcv] = 0;
    Q.push(srcv);

    Node srch(0,0,0,0,true);
    dist[srch] = 0;
    Q.push(srch);


    while (!Q.empty()) {
        auto u = Q.top();
        if (compare_xy_nodes(u, dst)) {
            break;
        }
        Q.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        IC(u);
        for (auto v: neighbours(inp, u)) {
            // TODO: Skip already visited nodes?
            if (visited[v]) {
                continue;
            }
            int alt = u._weight + v._weight;
            if (alt < dist[v]) {
                IC(u, v, dist[v], alt, alt < dist[v]);
                dist[v] = alt;
                // v._weight = alt;

                prev[Node(v._x, v._y, v._weight, v._steps, v._vertical)] = u;
                Q.push(Node(v._x, v._y, alt, v._steps, v._vertical));
            }
        }
    }
    // IC(dist);
    // print_map(inp, dist);
    // print_map(inp, prev);

    int out = 999999;
    for (int steps = 0; steps <= 3; steps++) {
        for (int vertical = 0; vertical <= 1; vertical++) {
            auto cand = Node(dst._x, dst._y, 0, steps, static_cast<bool>(vertical));
            int cand_cost = dist[cand];
            IC(cand, cand_cost);
            if (cand_cost < out) {
                dst = cand;
                out = cand_cost;
            }
        }
    }
    draw_grid(inp, prev, dst);
    return out;
}

int solve_2(std::vector<std::string> inp) {
    // IC(inp);
    return 0;
}
