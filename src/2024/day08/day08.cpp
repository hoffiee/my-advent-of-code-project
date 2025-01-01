/**
 * https://adventofcode.com/2024/day/8
 *
 * > While The Historians do their thing, you take a look at the familiar huge antenna. Much to your surprise, it seems
 * > to have been reconfigured to emit a signal that makes people 0.1% more likely to buy Easter Bunny brand Imitation
 * > Mediocre Chocolate as a Christmas gift! Unthinkable!
 */
#include <cmath>
#include <complex>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "string_utils.h"

struct Antennas {
    std::complex<int> size_{};
    std::vector<std::complex<int>> antennas_{};

    bool within_bounds(std::complex<int> pos) const {
        if (pos.real() < 0) {
            return false;
        }
        if (pos.imag() < 0) {
            return false;
        }
        if (size_.real() <= pos.real()) {
            return false;
        }
        if (size_.imag() <= pos.imag()) {
            return false;
        }
        return true;
    }

    void set_size(std::complex<int> size) { size_ = size; }

    void add_antenna(size_t row, size_t col) { antennas_.emplace_back(static_cast<int>(col), static_cast<int>(row)); }
};

struct AntennaGrid {
    std::complex<int> size_{};
    std::unordered_map<char, Antennas> antenna_grid_{};

    AntennaGrid(std::vector<std::string> const& inp)
        : size_{static_cast<int>(inp.at(0).size()), static_cast<int>(inp.size())} {
        for (size_t row{0}; row < inp.size(); row++) {
            for (size_t col{0}; col < inp.at(row).size(); col++) {
                auto pos = inp[row][col];
                if (pos != '.') {
                    antenna_grid_[pos].add_antenna(row, col);
                }
            }
        }
        for (auto& [freq, antennas] : antenna_grid_) {
            antennas.set_size(size_);
        }
    }

    struct Iterator {
        Iterator(std::unordered_map<char, Antennas>::iterator iterator) : it_(iterator) {}
        Iterator& operator++() {
            it_++;
            return *this;
        }
        bool operator!=(const Iterator& other) const { return it_ != other.it_; }
        Antennas& operator*() const { return it_->second; };

       private:
        std::unordered_map<char, Antennas>::iterator it_;
    };
    Iterator begin() { return Iterator(antenna_grid_.begin()); }
    Iterator end() { return Iterator(antenna_grid_.end()); }
};

struct ComplexHash {
    std::size_t operator()(const std::complex<int>& c) const {
        return std::hash<int>()(c.real()) ^ (std::hash<int>()(c.imag()) << 8);
    }
};

struct ComplexEqual {
    bool operator()(std::complex<int> const& lhs, std::complex<int> const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

using GeneratorOut = std::unordered_map<std::complex<int>, bool, ComplexHash, ComplexEqual>;
using GeneratorFcn = std::function<GeneratorOut(Antennas const&, size_t, size_t)>;

GeneratorOut generator1(Antennas const& antennas, size_t i, size_t j) {
    GeneratorOut candidates{};
    auto delta = antennas.antennas_[i] - antennas.antennas_[j];

    if (antennas.within_bounds(antennas.antennas_[i] + delta)) {
        candidates[antennas.antennas_[i] + delta];
    }
    if (antennas.within_bounds(antennas.antennas_[i] - delta)) {
        candidates[antennas.antennas_[i] - delta];
    }
    if (antennas.within_bounds(antennas.antennas_[j] + delta)) {
        candidates[antennas.antennas_[j] + delta];
    }
    if (antennas.within_bounds(antennas.antennas_[j] - delta)) {
        candidates[antennas.antennas_[j] - delta];
    }

    candidates.erase(candidates.find(antennas.antennas_[i]));
    candidates.erase(candidates.find(antennas.antennas_[j]));

    return candidates;
}

GeneratorOut generator2(Antennas const& antennas, size_t i, size_t j) {
    GeneratorOut candidates{};
    auto delta = antennas.antennas_[i] - antennas.antennas_[j];
    int k{0};
    while (antennas.within_bounds(antennas.antennas_[i] + k * delta)) {
        candidates[antennas.antennas_[i] + k * delta];
        k++;
    }

    k = 1;
    while (antennas.within_bounds(antennas.antennas_[i] - k * delta)) {
        candidates[antennas.antennas_[i] - k * delta];
        k++;
    }
    return candidates;
}

std::vector<std::complex<int>> find_antinodes(Antennas const& antennas, GeneratorFcn generator) {
    std::vector<std::complex<int>> antinodes{};
    for (size_t i{0}; i < antennas.antennas_.size(); i++) {
        for (size_t j{i + 1}; j < antennas.antennas_.size(); j++) {
            if (i == j) {
                continue;
            }
            auto candidates = generator(antennas, i, j);
            for (auto const& [pos, val] : candidates) {
                antinodes.emplace_back(pos);
            }
        }
    }
    return antinodes;
}

int64_t solver(std::vector<std::string> const& inp, GeneratorFcn generator) {
    AntennaGrid antenna_grid(inp);
    std::unordered_map<std::complex<int>, int, ComplexHash, ComplexEqual> antinodes{};
    for (auto const& antenna : antenna_grid) {
        auto candidate_antinotes = find_antinodes(antenna, generator);
        for (auto const& node : candidate_antinotes) {
            antinodes[node]++;
        }
    }
    return antinodes.size();
}

int64_t solve_1(std::vector<std::string> inp) { return solver(inp, generator1); }

int64_t solve_2(std::vector<std::string> inp) { return solver(inp, generator2); }

void samples() {
    auto sample1 = string_utils::read_input("day08-sample-1.input");
    assert(solve_1(sample1) == 2);

    auto sample2 = string_utils::read_input("day08-sample-2.input");
    assert(solve_1(sample2) == 4);

    auto sample3 = string_utils::read_input("day08-sample-3.input");
    assert(solve_1(sample3) == 14);

    auto sample4 = string_utils::read_input("day08-sample-4.input");
    assert(solve_2(sample4) == 9);
    assert(solve_2(sample3) == 34);
}

int main(int argc, char** argv) {
    auto input = string_utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
