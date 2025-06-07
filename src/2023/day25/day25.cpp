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
 * https://en.wikipedia.org/wiki/Karger%27s_algorithm
 * https://en.wikipedia.org/wiki/Graph_partition
 * https://people.eecs.berkeley.edu/~demmel/cs267/lecture20/lecture20.html
 * https://patterns.eecs.berkeley.edu/?page_id=571#Partitioning_Algorithms
 */
#include <Eigen/Dense>
#include <cassert>
#include <icecream.hpp>
#include <random>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

namespace aoc::y2023::d25 {

int64_t solve_1(std::vector<std::string> inp) {
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

int64_t solve_2(std::vector<std::string> inp) { return 0; }

void tests() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 54);
}

}  // namespace aoc::y2023::d25

using namespace aoc::y2023::d25;
int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, tests, solve_1_wrapper, solve_2_wrapper, input);
}
