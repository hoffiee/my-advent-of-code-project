/**
 * https://adventofcode.com/2024/day/23
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

using Graph = std::unordered_map<std::string, std::vector<std::string>>;
using Edges = std::vector<std::tuple<std::string, std::string>>;

std::tuple<Graph, Edges> construct_graph(std::vector<std::string> const& inp) {
    Graph graph{};
    Edges edges{};

    for (auto line : inp) {
        auto nodes = aoc::string::split(line, '-');
        assert(nodes.size() == 2);
        graph[nodes[0]].push_back(nodes[1]);
        graph[nodes[1]].push_back(nodes[0]);
        edges.push_back(std::make_tuple(nodes[0], nodes[1]));
    }
    return {graph, edges};
}

int64_t solve_1(std::vector<std::string> inp) {
    auto [graph, edges] = construct_graph(inp);

    std::unordered_map<std::string, int64_t> clusters{};
    for (auto [v, w] : edges) {
        std::unordered_map<std::string, int64_t> connected_to{};
        for (auto k : graph[v]) {
            connected_to[k]++;
        }
        for (auto k : graph[w]) {
            connected_to[k]++;
        }
        for (auto [k, count] : connected_to) {
            if (count < 2) {
                continue;
            }
            if (v.front() == 't' || w.front() == 't' || k.front() == 't') {
                // avoid counting same clusters multiple times by storing a unique key for each group
                std::vector<std::string> keys{v, w, k};
                std::sort(keys.begin(), keys.end());
                std::string keystr{};
                for (auto key : keys) {
                    keystr += key;
                }
                if (!clusters.contains(keystr)) {
                    clusters[keystr];
                }
            }
        }
    }
    int64_t ans{static_cast<int64_t>(clusters.size())};
    return ans;
}

std::string solve_2(std::vector<std::string> inp) {
    auto [graph, edges] = construct_graph(inp);

    // Find clusters of size >= 3
    std::unordered_map<std::string, int64_t> connected_to_2{};
    for (auto [v, w] : edges) {
        std::unordered_map<std::string, int64_t> connected_to{};
        for (auto k : graph[v]) {
            connected_to[k]++;
        }
        for (auto k : graph[w]) {
            connected_to[k]++;
        }
        for (auto [k, count] : connected_to) {
            if (count < 2) {
                continue;
            }
            connected_to_2[k] += count;
        }
    }

    // Find size of largest cluster
    std::unordered_map<int64_t, std::vector<std::string>> clusters{};
    int64_t max{0};
    for (auto [node, count] : connected_to_2) {
        clusters[count].push_back(node);
        if (count > max) {
            max = count;
        }
    }

    // Count computers that are connected to the most connected computers
    std::unordered_map<std::string, int64_t> connected_score{};
    auto const& search = clusters[max];
    max = 0;
    for (auto node : search) {
        int count{0};
        for (auto v : graph[node]) {
            if (std::find(search.begin(), search.end(), v) != search.end()) {
                count++;
            }
        }
        connected_score[node] += count;
        if (count > max) {
            max = count;
        }
    }

    std::vector<std::string> lan{};
    for (auto [node, count] : connected_score) {
        if (count == max) {
            lan.push_back(node);
        }
    }
    std::sort(lan.begin(), lan.end());

    auto out = aoc::string::join(lan, ",");
    return out;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 7);
    assert(solve_2(sample) == "co,de,ka,ta");
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
