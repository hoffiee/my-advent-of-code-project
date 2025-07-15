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

namespace utils {

std::vector<std::string> read_input(std::string filename);

};  // namespace utils

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

/// Based on
/// https://en.wikipedia.org/wiki/Newton_polynomial
template<typename T, int64_t degree>
struct PolynomialInterpolation {
    std::vector<T> xvec_{};
    std::vector<T> yvec_{};
    std::array<std::array<T, degree>, degree> divided_diff_table{0};

    PolynomialInterpolation(std::vector<T> const& xvec, std::vector<T> const& yvec) : xvec_{xvec}, yvec_{yvec} {
        assert(xvec_.size() == yvec_.size());
        assert(xvec_.size() == degree);

        for (std::size_t i{0}; i < degree; i++) {
            divided_diff_table[i][0] = yvec_.at(i);
        }

        for (std::size_t j{1}; j < degree; j++) {
            for (std::size_t i{0}; i < (degree - j); i++) {
                T num = divided_diff_table[i+1][j-1] - divided_diff_table[i][j-1];
                T den = xvec_.at(i+j) - xvec_.at(i);
                divided_diff_table[i][j] = num/den;
            }
        }
    }

    void add_point(T x, T y) {
        xvec_.push_back(x);
        yvec_.push_back(y);
    }

    T interpolate(T x) {
        T val{0};
        for (std::int64_t k{0}; k < degree; k++) {
            T prod{1};
            for (std::int64_t j{0}; j <= (k-1); j++) {
                prod *= (x - xvec_.at(j));
            }
            val += divided_diff_table[0][k]*prod;
        }
        return val;
    }
};

namespace graph { };

namespace grid2d {
};

namespace puzzle {

};

}; // aoc

#endif
