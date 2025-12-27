/**
 * https://adventofcode.com/2023/day/25
 *
 * aoc_tags: minimum cut graph
 *
 * Seems bridge finding, kargers algorithm is a common approach, I went with a
 * spectral bisection by generating the laplacian matrix and inspecting the
 * eigenvector of the second smallest eigenvalue, the sign indicated what side
 * of the a node would be part of.
 *
 * It does however not look good in benchmarking. So I'd like to benchmark this
 * against a Kargers algorithm instead. Alternatively look into if we can set
 * up the problem differently so that eigen is faster. I suspect that we don't
 * have a dense matrix?
 *
 * Going with Karger didn't really satisfy me either, it's nondeterministic so
 * it's not always hitting home..
 *
 * https://en.wikipedia.org/wiki/Karger%27s_algorithm
 * https://en.wikipedia.org/wiki/Graph_partition
 * https://people.eecs.berkeley.edu/~demmel/cs267/lecture20/lecture20.html
 * https://patterns.eecs.berkeley.edu/?page_id=571#Partitioning_Algorithms
 * https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 */
#include <Eigen/Dense>
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <random>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d25 {

__attribute__((unused)) int64_t spectral_bisection(std::vector<std::string> inp) {
    // create a str -> id map
    std::unordered_map<std::string, std::size_t> node_to_id{};
    std::size_t id{0u};
    for (auto const& line : inp) {
        auto splits = aoc::string::split(line, ' ');
        assert(splits.size() > 1u);
        auto const stripped_name = std::string(splits.at(0).cbegin(), splits.at(0).cend() - 1u);
        if (!node_to_id.contains(stripped_name)) {
            node_to_id[stripped_name] = id++;
        }
        for (std::size_t i{1u}; i < splits.size(); i++) {
            if (!node_to_id.contains(splits.at(i))) {
                node_to_id[splits.at(i)] = id++;
            }
        }
    }

    std::size_t nr_of_nodes{node_to_id.size()};
    // IC(node_to_id, nr_of_nodes);

    Eigen::MatrixXd adjacency_matrix(nr_of_nodes, nr_of_nodes);
    adjacency_matrix.setZero();

    for (auto const& line : inp) {
        auto splits = aoc::string::split(line, ' ');
        assert(splits.size() > 1u);

        auto const node = std::string(splits.at(0).cbegin(), splits.at(0).cend() - 1u);
        auto const node_id = node_to_id.at(node);

        for (std::size_t i{1u}; i < splits.size(); i++) {
            auto const adjacent_id = node_to_id.at(splits.at(i));
            adjacency_matrix(node_id, adjacent_id) += 1.0;
            adjacency_matrix(adjacent_id, node_id) += 1.0;
        }
    }
    // std::cout << adjacency_matrix << std::endl << std::endl;

    Eigen::MatrixXd degree_matrix(nr_of_nodes, nr_of_nodes);
    degree_matrix.setZero();
    for (std::size_t i{0}; i < nr_of_nodes; i++) {
        degree_matrix(i, i) = adjacency_matrix.row(i).sum();
    }
    // std::cout << degree_matrix << std::endl << std::endl;

    auto laplacian = degree_matrix - adjacency_matrix;
    // std::cout << laplacian << std::endl << std::endl;

    Eigen::EigenSolver<Eigen::MatrixXd> solver(laplacian);
    auto const eigvals = solver.eigenvalues();
    auto const eigvecs = solver.eigenvectors();

    // std::cout << "Eigenvals:\n" << eigvals << std::endl;
    // std::cout << "Eigenvecs:\n" << eigvecs << std::endl;
    std::vector<std::pair<double, int>> eig_pairs(nr_of_nodes, std::make_pair(0.0, 0));
    for (std::size_t i{0}; i < nr_of_nodes; i++) {
        eig_pairs.at(i) = std::make_pair(eigvals[i].real(), i);
    }
    std::sort(eig_pairs.begin(), eig_pairs.end());

    auto second_smallest_idx = eig_pairs[1].second;

    // std::cout << "second smallest eigenvector\n" << eigvecs.col(second_smallest_idx) << std::endl << std::endl;

    auto const second_smallest_eigenvector = eigvecs.col(second_smallest_idx);
    int64_t positive{0};
    int64_t negative{0};
    for (auto const& it : second_smallest_eigenvector) {
        if (it.real() < 0.0) {
            negative++;
        } else {
            positive++;
        }
    }

    return negative * positive;
}

struct Edge {
    int32_t node_1_{};
    int32_t node_2_{};
    bool operator==(Edge const& other) const {
        return ((node_1_ == other.node_1_ && node_2_ == other.node_2_) ||
                (node_1_ == other.node_2_ && node_2_ == other.node_1_));
    }

    friend std::ostream& operator<<(std::ostream& os, Edge const& e) {
        os << e.node_1_ << " <-> " << e.node_2_;
        return os;
    }
};

struct Edges {
    std::vector<Edge> edges_{};

    void addEdge(int32_t const& node_1, int32_t const& node_2) {
        Edge cand_edge{node_1, node_2};
        if (std::find(edges_.cbegin(), edges_.cend(), cand_edge) != edges_.cend()) {
            return;
        }
        edges_.push_back(cand_edge);
    }

    void removeEdge(Edge const& edge) {
        auto it = std::find(edges_.begin(), edges_.end(), edge);

        if (it == edges_.end()) {
            std::cout << "Edge " << edge << " doesn't exist!" << std::endl;
            return;
        }
        edges_.erase(it);
    }

    Edge pickEdge() const {
        std::random_device rd{};
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, edges_.size() - 1u);
        return edges_.at(dist(gen));
    }
};

struct Graph {
    Edges edges_{};
    std::unordered_map<int32_t, std::unordered_map<int32_t, bool>> graph_{};
    std::unordered_map<int32_t, int32_t> value_{};
    int32_t max_id_{0};

    std::size_t size() const { return graph_.size(); }

    void addEdge(int32_t const& node_1, int32_t const& node_2) {
        max_id_ = std::max({max_id_, node_1, node_2});
        edges_.addEdge(node_1, node_2);
        graph_[node_1][node_2] = true;
        graph_[node_2][node_1] = true;
    }

    void removeEdge(Edge const& edge) {
        edges_.removeEdge(edge);
        graph_.at(edge.node_1_).erase(edge.node_2_);
        graph_.at(edge.node_2_).erase(edge.node_1_);
    }

    Edge pickEdge() const { return edges_.pickEdge(); };

    void contractNodes(Edge const& edge) {
        auto const new_node = max_id_ + 1;
        value_[new_node] = value_[edge.node_1_] + value_[edge.node_2_];

        // iterate through connecting nodes
        std::vector<Edge> edges_to_remove{edge};
        for (auto const [node, _] : graph_.at(edge.node_1_)) {
            if (node == edge.node_2_) {
                continue;
            }
            edges_to_remove.push_back(Edge{edge.node_1_, node});
            addEdge(new_node, node);
        }
        for (auto const [node, _] : graph_.at(edge.node_2_)) {
            if (node == edge.node_1_) {
                continue;
            }
            edges_to_remove.push_back(Edge{edge.node_2_, node});
            addEdge(new_node, node);
        }

        for (auto const& edge_to_remove : edges_to_remove) {
            removeEdge(edge_to_remove);
        }

        // Now it should be safe to remove the nodes
        graph_.erase(edge.node_1_);
        graph_.erase(edge.node_2_);
    }
};

__attribute__((unused)) int64_t kargers_algorithm(std::vector<std::string> inp) {
    Graph graph{};

    std::unordered_map<std::string, int32_t> node_to_id{};
    std::int32_t id{0};
    for (auto const& line : inp) {
        auto splits = aoc::string::split(line, ' ');
        assert(splits.size() > 1u);
        auto const stripped_name = std::string(splits.at(0).cbegin(), splits.at(0).cend() - 1u);
        if (!node_to_id.contains(stripped_name)) {
            node_to_id[stripped_name] = id++;
        }
        auto const node_1_id = node_to_id[stripped_name];
        for (std::size_t i{1u}; i < splits.size(); i++) {
            if (!node_to_id.contains(splits.at(i))) {
                node_to_id[splits.at(i)] = id++;
            }
            auto const node_2_id = node_to_id[splits.at(i)];
            graph.addEdge(node_1_id, node_2_id);
            graph.value_[node_1_id] = 1;
            graph.value_[node_2_id] = 1;
        }
    }
    IC(graph.edges_.edges_);

    while (graph.size() > 2u) {
        auto const edge_to_remove = graph.pickEdge();
        IC(edge_to_remove);
        graph.contractNodes(edge_to_remove);
        IC(graph.value_);
    }

    int32_t prodsum{1};
    for (auto const& [a, b] : graph.graph_) {
        IC(a, graph.value_[a]);
        prodsum *= graph.value_[a];
    }

    IC(prodsum);
    return prodsum;
}

int64_t solve_1(std::vector<std::string> inp) { return spectral_bisection(inp); }

int64_t solve_2(std::vector<std::string> inp) { return 0; }

void tests() {
    Edge e1{10, 12};
    Edge e2{12, 10};
    assert(e1 == e2);

    Edges edges{};
    edges.addEdge(10, 12);
    edges.addEdge(12, 10);
    assert(edges.edges_.size() == 1u);

    /**  Test contract the edge 2-3
     *      1     2     3     4
     *      o --- o --- o --- o
     *      And expect the outcome
     *      1     5     3
     *      o --- o --- o
     */
    {
        Graph graph{};
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 4);

        assert(graph.graph_.size() == 4u);
        graph.contractNodes(Edge{2, 3});
        assert(graph.graph_.at(1).at(5));
        assert(graph.graph_.at(5).at(4));
        assert(graph.graph_.size() == 3u);
    }

    /** Test contract the single connection in the middle for the graph
     *      1    2     3      4
     *      o --- o --- o --- o
     *      o --´         `-- o
     *      5                 6
     *      And expect the outcome
     *      1     7     4
     *      o --- o --- o
     *      o --´   `-- o
     *      5           6
     */
    {
        Graph graph{};
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 4);
        graph.addEdge(5, 2);
        graph.addEdge(3, 6);

        assert(graph.graph_.size() == 6u);
        graph.contractNodes(Edge{2, 3});
        assert(graph.graph_.at(1).at(7));
        assert(graph.graph_.at(5).at(7));
        assert(graph.graph_.at(4).at(7));
        assert(graph.graph_.at(6).at(7));
        assert(graph.graph_.size() == 5u);
    }

    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 54);
}

}  // namespace aoc::y2023::d25

using namespace aoc::y2023::d25;
int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 543564);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp);
        assert(res == 0);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, tests, solve_1_wrapper, solve_2_wrapper, input);
}
