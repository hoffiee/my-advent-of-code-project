#ifndef LIB_2016_DAY03_H_
#define LIB_2016_DAY03_H_

#include <string>
#include <vector>

namespace {
using Triangles = std::vector<std::vector<int>>;
}

Triangles parse_data(std::vector<std::string>& triangles);
Triangles transpose_triangles(Triangles& triangles);
std::pair<int, int> solve(std::vector<std::string>& input);

#endif
