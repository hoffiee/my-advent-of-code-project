#include AOC_HEADER

#include <iostream>
#include <numeric>
#include <sstream>

static int count_possible_triangles(Triangles& triangles) {
    int possible_count = 0;
    for (auto sides : triangles) {
        int side_sum = std::accumulate(sides.cbegin(), sides.cend(), 0);
        int max_elem = *std::max_element(sides.cbegin(), sides.cend());
        if ((side_sum - max_elem) > max_elem) {
            possible_count++;
        }
    }
    return possible_count;
}

Triangles parse_data(std::vector<std::string>& input) {
    Triangles triangles;
    for (auto triangle : input) {
        std::stringstream ss(triangle);
        std::vector<int> sides(3, 0);
        ss >> sides.at(0) >> sides.at(1) >> sides.at(2);
        triangles.push_back(std::move(sides));
    }
    return triangles;
}

Triangles transpose_triangles(Triangles& triangles) {
    if (triangles.size() % 3 != 0) {
        return {};
    }
    Triangles triangles_vertical;
    for (size_t col = 0; col < 3; ++col) {
        for (size_t row = 0; row < triangles.size(); row += 3) {
            auto s1 = triangles.at(row).at(col);
            auto s2 = triangles.at(row + 1).at(col);
            auto s3 = triangles.at(row + 2).at(col);
            triangles_vertical.emplace_back(std::vector{s1, s2, s3});
        }
    }
    return triangles_vertical;
}

std::pair<int, int> solve(std::vector<std::string> input) {
    Triangles triangles = parse_data(input);
    auto triangles_transposed = transpose_triangles(triangles);

    int possible_count_1 = count_possible_triangles(triangles);
    int possible_count_2 = count_possible_triangles(triangles_transposed);

    return {possible_count_1, possible_count_2};
}
