/**
 * https://adventofcode.com/2023/day/8
 */
#include AOC_HEADER

#include <aoc_utils.h>
#include <omp.h>

#include <icecream.hpp>
#include <unordered_map>

struct Node {
    std::string id;
    std::vector<std::string> neighbours;

    Node(std::string inp);
    void print();
};

Node::Node(std::string inp) {
    inp.erase(std::remove_if(inp.begin(), inp.end(),
                             [](auto ch) {
                                 const std::string to_remove = "(),";
                                 return to_remove.find(ch) != std::string::npos;
                             }),
              inp.end());

    std::string tmp;
    std::stringstream ss(inp);
    ss >> id;

    auto ignore = [&] {
        while (ss && !std::isalnum(ss.peek())) {
            ss.ignore();
        }
    };
    ignore();
    ss >> tmp;
    neighbours.emplace_back(tmp);
    ignore();
    ss >> tmp;
    neighbours.emplace_back(tmp);
}

std::vector<int> parse_input(std::vector<std::string> inp) {
    std::vector<int> instructions;
    for (auto instruction : inp.at(0)) {
        switch (instruction) {
            case 'L':
                instructions.push_back(0);
                break;
            case 'R':
                instructions.push_back(1);
                break;
            default:
                throw std::logic_error("shouldn't happen? wrong in input");
                break;
        }
    }
    return instructions;
}

struct Graph {
    std::unordered_map<std::string, Node> map;

    Graph(std::vector<std::string> inp);
    std::vector<std::string> get_nodes(std::function<bool(std::string)> condition);
};

Graph::Graph(std::vector<std::string> inp) {
    for (auto line : inp) {
        std::stringstream ss(line);
        std::string id;
        ss >> id;
        map.emplace(id, Node(line));
    }
}

std::vector<std::string> Graph::get_nodes(std::function<bool(std::string)> condition) {
    std::vector<std::string> nodes;
    for (auto& [key, node] : map) {
        if (condition(key)) {
            nodes.emplace_back(key);
        }
    }
    return nodes;
}

static int steps_to_target(std::unordered_map<std::string, Node>& map, std::vector<int>& instructions,
                           std::string start, std::function<bool(std::string)> condition) {
    int count = 0;
    for (size_t i = 0; condition(start); i = (i + 1) % instructions.size()) {
        start = map.at(start).neighbours.at(instructions.at(i));
        count++;
    }
    return count;
}

int solve_1(std::vector<std::string> inp) {
    auto instructions = parse_input(inp);

    Graph graph(std::vector<std::string>(inp.begin() + 2, inp.end()));

    auto condition = [](std::string str) { return str != "ZZZ"; };
    return steps_to_target(graph.map, instructions, "AAA", condition);
}

int64_t solve_2(std::vector<std::string> inp) {
    auto instructions = parse_input(inp);

    Graph graph(std::vector<std::string>(inp.begin() + 2, inp.end()));

    auto current_nodes = graph.get_nodes([](std::string str) { return str.back() == 'A'; });

    // Method: find out steps from each start, then calculate the lowest common multiple
    std::vector<int64_t> steps(current_nodes.size(), 0);
    auto condition = [](std::string str) { return str.back() != 'Z'; };
#pragma omp parallel for
    for (size_t i = 0; i < steps.size(); i++) {
        steps.at(i) = steps_to_target(graph.map, instructions, current_nodes.at(i), condition);
    }
    int64_t count = aoc::math::lcm(steps);
    return count;
}
