/**
 * https://adventofcode.com/2023/day/11
 *
 * hyperfine initial -> ~65, after some changes I got it down to around 32 ms
 */
#include AOC_HEADER

#include <omp.h>

#include <icecream.hpp>

static std::vector<std::tuple<int, int>> get_positions(std::vector<std::string>& inp) {
    std::vector<std::tuple<int, int>> positions;
    for (size_t row = 0; row < inp.size(); row++) {
        for (size_t col = 0; col < inp.at(row).size(); col++) {
            if (inp[row][col] == '#') {
                positions.emplace_back(std::make_pair(col, row));
            }
        }
    }
    return positions;
}

static int sum_of_galaxy_distances(std::vector<std::tuple<int, int>> positions) {
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < positions.size(); i++) {
        for (size_t j = i + 1; j < positions.size(); j++) {
            auto manhattan_distance = [](auto& p1, auto& p2) {
                auto& [x1, y1] = p1;
                auto& [x2, y2] = p2;
                return std::abs(x2 - x1) + std::abs(y2 - y1);
            };
            sum += manhattan_distance(positions[i], positions[j]);
        }
    }
    return sum;
}

static void expand_map(std::vector<std::string>& map) {
    // extend rows
    for (size_t row = 0; row < map.size(); row++) {
        if (std::none_of(map.at(row).begin(), map.at(row).end(), [](auto& ch) { return ch == '#'; })) {
            map.insert(map.begin() + row, std::string(map.at(row).size(), '.'));
            row++;
        }
    }

    for (size_t col = 0; col < map.at(0).size(); col++) {
        bool extend = true;
        for (size_t row = 0; row < map.size(); row++) {
            if (map.at(row).at(col) == '#') {
                extend = false;
                break;
            }
        }

        if (extend) {
            for (size_t row = 0; row < map.size(); row++) {
                map.at(row).insert(map.at(row).begin() + col, '.');
            }
            col++;
        }
    }
}

int64_t internal::solve_factor(std::vector<std::string> inp, int factor) {
    /**
     * neat, consider
     *
     * S = sum of distances
     * Sn = sum of distances without extra rows/columns
     * Se = sum of extra rows/columns impacting the distance from one extra step
     *
     * S = Sn + Se,
     *
     * if we take a factor into account
     *
     * => S(n) = Sn + (n-1)*Se
     *
     * where n is the amount of steps we replace the original with, -1 comes
     * from the fact that the original step is already accounted for in Sn.
     *
     * This allows us to setup:
     *
     * S(1) = Sn + 0*Se = Sn
     * S(2) = Sn + Se
     *
     * S(2) - S(1) = Sn + Se - Sn
     * S(2) - S(1) = Se
     *
     * and then we can calculate any S(n) from S(1), S(2).
     */
    int64_t sum_nominal = sum_of_galaxy_distances(get_positions(inp));
    int64_t sum_2 = solve_1(inp);

    auto sum_extra = sum_2 - sum_nominal;
    return sum_nominal + sum_extra * (factor - 1);
}

int solve_1(std::vector<std::string> inp) {
    expand_map(inp);
    auto positions = get_positions(inp);
    return sum_of_galaxy_distances(positions);
}

int64_t solve_2(std::vector<std::string> inp) { return internal::solve_factor(inp, 1000000); }
