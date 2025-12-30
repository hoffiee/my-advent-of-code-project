/**
 * https://adventofcode.com/2021/day/12
 */
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2021::d12 {

struct Graph {
    std::unordered_map<std::string, std::vector<std::string>> edges{};
    std::unordered_map<std::string, bool> small_cave{};
    std::unordered_map<std::string, int64_t> visited{};
    bool extra_small_cave{true};

    Graph(std::vector<std::string> const& inp) {
        for (auto const& line : inp) {
            auto nodes = aoc::string::split(line, '-');
            assert(nodes.size() == 2u);

            // Setup so that all nodes are undirected except for start and end,
            // they should only have outgoing/incoming connections
            // respectively.
            if (nodes.at(0) != "end" && nodes.at(1) != "start") {
                edges[nodes.at(0)].push_back(nodes.at(1));
            }
            if (nodes.at(1) != "end" && nodes.at(0) != "start") {
                edges[nodes.at(1)].push_back(nodes.at(0));
            }

            for (auto const& node : nodes) {
                small_cave[node] = std::islower(node.at(0));
            }
        }
    }

    std::vector<std::string> const& neighbours(std::string const& node) const { return edges.at(node); }
};

int64_t dig(Graph graph, std::string next) {
    if (next == "end") {
        return 1;
    }

    bool const end_node{next == "start" || next == "end"};
    bool const extra_step{graph.extra_small_cave && !end_node};
    bool const visited_small_cave{graph.small_cave[next] && graph.visited[next] > 0};

    if (!extra_step && visited_small_cave) {
        return 0;
    }

    if (extra_step && visited_small_cave) {
        graph.extra_small_cave = false;
    }

    graph.visited[next]++;

    int64_t count{0};
    for (auto const& node : graph.neighbours(next)) {
        count += dig(graph, node);
    }
    return count;
}

int64_t solve_1(std::vector<std::string> inp) {
    Graph graph{inp};
    graph.extra_small_cave = false;
    int64_t count{dig(graph, "start")};
    return count;
}

int64_t solve_2(std::vector<std::string> inp) {
    Graph graph{inp};
    int64_t count{dig(graph, "start")};
    return count;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 10);
    assert(solve_2(sample) == 36);

    auto sample1 = aoc::utils::read_input("day12-sample-1.input");
    assert(solve_1(sample1) == 19);
    assert(solve_2(sample1) == 103);

    auto sample2 = aoc::utils::read_input("day12-sample-2.input");
    assert(solve_1(sample2) == 226);
    assert(solve_2(sample2) == 3509);
}

};  // namespace aoc::y2021::d12

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = aoc::y2021::d12::solve_1(inp);
        assert(res == 4885);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = aoc::y2021::d12::solve_2(inp);
        assert(res == 117095);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2021::d12::samples, solve_1_wrapper, solve_2_wrapper, input);
}
