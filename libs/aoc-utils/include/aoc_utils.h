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

std::vector<std::string> read_input(std::string const& filename);

};  // namespace utils

namespace vector {

// TODO Split vector at entry, example input vectors with a "" separator.
// TODO cartesian product

};

namespace print {
// TODO Print different representations of numbers, octals hex, binary etc
};

namespace string {

// TODO numbers from string (templated type)
// TODO Words from string
// TODO filter characters/words?
std::string join(std::vector<std::string> const& vec, std::string const delim = "");

// TODO this variant too, either delim can be multiple chars such as ,:-, or words? for example cow
std::vector<std::string> split(std::string str, char delim = ',');

};  // namespace string

namespace math {
// TODO number of digits in number (templated)
// TODO: Setup templates?
// int64_t gcd(int64_t a, int64_t b);
// Test this one
int64_t lcm(std::vector<int64_t> vec);

/// Handles negative numbers
int64_t mod(int64_t a, int64_t b);

/// Based on
/// https://en.wikipedia.org/wiki/Newton_polynomial
template <typename T, int64_t degree>
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
                T num = divided_diff_table[i + 1][j - 1] - divided_diff_table[i][j - 1];
                T den = xvec_.at(i + j) - xvec_.at(i);
                divided_diff_table[i][j] = num / den;
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
            for (std::int64_t j{0}; j <= (k - 1); j++) {
                prod *= (x - xvec_.at(j));
            }
            val += divided_diff_table[0][k] * prod;
        }
        return val;
    }
};

};  // namespace math

namespace grid2d {

struct Pos {
    int64_t x{};
    int64_t y{};

    Pos& operator+=(Pos const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Pos const& p) {
        os << "(" << p.x << "," << p.y << ")" << std::endl;
        return os;
    }

    bool operator==(Pos const& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(Pos const& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    struct Hash {
        size_t operator()(Pos const& pos) const {
            size_t hx = std::hash<int64_t>()(pos.x);
            size_t hy = std::hash<int64_t>()(pos.y) << 8;
            return hx ^ hy;
        }
    };
};

// `inline` to avoid linker errors due to multiple definitions over multiple
// translation units
inline Pos operator+(Pos const& lhs, Pos const& rhs) { return Pos{lhs.x + rhs.x, lhs.y + rhs.y}; }
inline Pos operator-(Pos const& lhs, Pos const& rhs) { return Pos{lhs.x - rhs.x, lhs.y - rhs.y}; }
inline Pos operator*(int64_t const val, Pos const& rhs) { return Pos{val*rhs.x, val*rhs.y}; }

};



};  // namespace aoc

#endif
