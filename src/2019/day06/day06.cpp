/**
 * https://adventofcode.com/2019/day/6
 *
 * Note that we rely on operator [] for unordered_map operations, this is
 * because we want it to create an element and instantiate it to 0 if we
 * haven't seen it before.
 */
#include AOC_HEADER

#include <icecream.hpp>
#include <queue>
#include <regex>
#include <unordered_map>

struct Node {
    std::vector<std::string> nodes;
    int score = 0;
};

static std::unordered_map<std::string, Node> orbit_create_graph_bidirectional(std::vector<std::string> input) {
    std::unordered_map<std::string, Node> orbits;
    for (auto vertice : input) {
        std::regex re("\\)");
        std::sregex_token_iterator first{vertice.begin(), vertice.end(), re, -1};
        std::sregex_token_iterator last;
        std::vector<std::string> tokens{first, last};
        IC(tokens);

        orbits[tokens.at(0)].nodes.push_back(tokens.at(1));
        orbits[tokens.at(1)].nodes.push_back(tokens.at(0));
    }
    return orbits;
}

static void orbit_breath_first_search(std::unordered_map<std::string, Node>& orbits, std::string start,
                                      std::string goal) {
    // https://en.wikipedia.org/wiki/Breadth-first_search#Pseudocode
    if (start.empty()) {
        throw std::invalid_argument("Starting point for search is required.");
    }
    IC(start, goal);

    std::queue<std::string> Q;
    std::unordered_map<std::string, bool> node_explored;

    Q.push(start);
    node_explored[start] = true;
    orbits[start].score = 0;

    while (!Q.empty()) {
        auto v = Q.front();
        Q.pop();
        IC(v, orbits[v].nodes);

        if (!goal.empty() && v == goal) {
            return;
        }
        for (auto w : orbits[v].nodes) {
            if (!node_explored[w]) {
                node_explored[w] = true;
                Q.push(w);
                orbits[w].score = orbits[v].score + 1;
            }
        }
    }
}

int solve_1(std::vector<std::string> inp) {
    IC_CONFIG.disable();

    auto orbits = orbit_create_graph_bidirectional(inp);
    orbit_breath_first_search(orbits, "COM", "");

    int count = 0;
    for (auto node : orbits) {
        IC(node.first, node.second.score, node.second.nodes);
        count += node.second.score;
    }
    return count;
}

int solve_2(std::vector<std::string> inp) {
    IC_CONFIG.disable();
    IC(inp);

    auto orbits = orbit_create_graph_bidirectional(inp);
    orbit_breath_first_search(orbits, "YOU", "SAN");

    for (auto node : orbits) {
        IC(node.first, node.second.score, node.second.nodes);
    }

    return orbits["SAN"].score - 2;
}
