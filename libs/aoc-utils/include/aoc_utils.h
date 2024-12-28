#ifndef AOC_UTILS_H_
#define AOC_UTILS_H_

#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>


namespace aoc {

namespace vector {
};


namespace print {
};

namespace string {

std::string join(std::vector<std::string> const& vec, std::string const delim="");

std::vector<std::string> split(std::string str, char delim=',');

};

namespace math {

int64_t lcm(std::vector<int64_t> vec);

};

namespace graph { };

namespace grid2d {
};

namespace puzzle {

};

}; // aoc

#endif
