/**
 * https://adventofcode.com/2024/day/21
 *
 * Ok, part 1 is completed. but I need to figure out a way to generate fewer paths for each step. Ideally it would be
 * great to avoid including solutions such as <v<v<v, as <<<vvv or vvv<<< is going to be better, figure out a way to
 * avoid them.
 *
 * In step 2 there were a lot of issues with growing memory. After a wile I tried to cause the sequences to chunk before
 * caching the sequences a bit but couldn't figure out a good way to chunk it as the output would vectors of strings the
 * way I had built it that point. Looked into some greedy alternatives and ways to filter away obvious longer sequences
 * but it only allowed for one or 2 more robots to be added. After a while found out about an approach by HyperNeutrino
 * where as instead of generating each sequence on every level, we recurse down to the bottom of each sequence to see
 * the optimal path and only check each step onwards, then pick the shortest length for each level. That solved the
 * memory issues as I no longer kept passing around growing strings... It took forever though to compute which applying
 * some memoization helped solve. Had to dig a lot for this one. Key take away from this was that a breath first search
 * as I did initially easily explodes when the depth becomes too large. Doing it a depth first search instead prevented
 * that.
 *
 * Another take away, I were at some points fooled by the memory usage of my program, turns out that running things
 * through ninja, it caches the output before it prints to the terminal, so I had momemnts where I thought my program
 * used a shitload of memory, in fact it when I ran it with ninja, running the binary for itself did not have the same
 * memory footprint...
 */
#include <algorithm>
#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <queue>
#include <regex>
#include <string>
#include <vector>

#include "string_utils.h"

// TODO Move to helper and create a template? feels like I can reduce it quite alot given the amount of grid problems
using Pos = std::complex<int64_t>;

struct PosHash {
    std::size_t operator()(const Pos& c) const {
        return std::hash<int64_t>()(c.real()) ^ (std::hash<int64_t>()(c.imag()) << 8);
    }
};

struct PosEqual {
    bool operator()(Pos const& lhs, Pos const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

namespace Dir {
constexpr Pos Up = {0, -1};
constexpr Pos Right = {1, 0};
constexpr Pos Down = {0, 1};
constexpr Pos Left = {-1, 0};
}  // namespace Dir

std::vector<Pos> const dirs{Dir::Up, Dir::Right, Dir::Down, Dir::Left};

// TODO move to utils
std::vector<std::string> cartesian_product(std::vector<std::string> const& vec1, std::vector<std::string> const& vec2) {
    if (vec1.size() == 0) {
        return vec2;
    }
    if (vec2.size() == 0) {
        return vec1;
    }

    std::vector<std::string> out{};
    out.reserve(vec1.size() * vec2.size());
    std::string res{};
    res.reserve(vec1.front().size() + vec2.front().size());
    for (auto const& it1 : vec1) {
        for (auto const& it2 : vec2) {
            res = "";
            res += it1;
            res += it2;
            out.push_back(it1 + it2);
        }
    }
    return out;
}

// Ahh, I shouldn't but have to learn a bit about this at some point so let's do some uneccesary stuff here.
struct Keypad {
    std::unordered_map<Pos, char, PosHash, PosEqual> const pos2char_{};
    std::unordered_map<char, Pos> char2pos_{};

    Keypad(std::unordered_map<Pos, char, PosHash, PosEqual> const& pos2char) : pos2char_{pos2char} {
        for (auto [pos, ch] : pos2char_) {
            char2pos_[ch] = pos;
        }
        assert(char2pos_.contains('A'));
    }

    virtual void print() {
        for (int64_t row{0}; row < 4; row++) {
            for (int64_t col{0}; col < 3; col++) {
                Pos p{col, row};
                if (!pos2char_.contains(p)) {
                    std::cout << "  ";
                    continue;
                }
                std::cout << pos2char_.at(p) << " ";
            }
            std::cout << std::endl;
        }
    }

    std::unordered_map<Pos, std::string, PosHash, PosEqual> dir2char_{
        {Dir::Up, "^"}, {Dir::Down, "v"}, {Dir::Left, "<"}, {Dir::Right, ">"}};

    std::vector<std::tuple<Pos, std::string>> get_neighbours(Pos const& pos) const {
        std::vector<std::tuple<Pos, std::string>> out{};
        for (auto dir : dirs) {
            auto cand = pos + dir;
            if (!pos2char_.contains(cand)) {
                continue;
            }
            out.push_back(std::make_tuple(cand, dir2char_.at(dir)));
        }
        return out;
    }

    std::unordered_map<std::string, std::vector<std::string>> get_moves_cache_{};
    std::vector<std::string> get_moves(char const start, char const finish) {
        std::string entry{start, finish};
        if (get_moves_cache_.contains(entry)) {
            return get_moves_cache_.at(entry);
        }
        assert(char2pos_.contains(start));
        assert(char2pos_.contains(finish));
        if (start == finish) {
            return {"A"};
        }

        // BFS to find all possible paths
        std::vector<std::string> possible_steps{};
        std::queue<std::pair<Pos, std::string>> queue{};
        size_t optimal{1000};
        std::unordered_map<Pos, bool, PosHash, PosEqual> visited_{};
        visited_[start] = true;
        queue.push(std::make_pair(char2pos_[start], ""));

        while (!queue.empty()) {
            auto [v, steps] = queue.front();
            queue.pop();

            if (v == char2pos_[finish]) {
                if (optimal < steps.size()) {
                    break;
                }
                optimal = steps.size();
                // I forgot to add the "A" at first, which casued a lot of pains and patching that up in other places.
                possible_steps.push_back(steps + "A");
            }

            for (auto [neighbour, step] : get_neighbours(v)) {
                visited_[neighbour] = true;
                queue.push(std::make_pair(neighbour, steps + step));
            }
        }

        get_moves_cache_[entry] = possible_steps;
        return possible_steps;
    }
};

struct NumericKeypad : public Keypad {
    NumericKeypad()
        : Keypad(std::unordered_map<Pos, char, PosHash, PosEqual>{{{0, 0}, '7'},
                                                                  {{1, 0}, '8'},
                                                                  {{2, 0}, '9'},
                                                                  {{0, 1}, '4'},
                                                                  {{1, 1}, '5'},
                                                                  {{2, 1}, '6'},
                                                                  {{0, 2}, '1'},
                                                                  {{1, 2}, '2'},
                                                                  {{2, 2}, '3'},
                                                                  {{1, 3}, '0'},
                                                                  {{2, 3}, 'A'}}) {}

    std::unordered_map<std::string, std::vector<std::string>> solve_cache_{};
    std::vector<std::string> solve(std::string const& inp) {
        if (solve_cache_.contains(inp)) {
            return solve_cache_[inp];
        }

        std::vector<std::vector<std::string>> possible_sequences{};
        for (size_t i{0}; i < inp.size(); i++) {
            char prev = i == 0 ? 'A' : inp[i - 1];
            auto candidate_sequence = get_moves(prev, inp[i]);
            possible_sequences.push_back(candidate_sequence);
        }

        std::vector<std::string> out{};
        for (size_t i{0}; i < possible_sequences.size(); i++) {
            out = cartesian_product(out, possible_sequences[i]);
        }

        // Filter out moves such as ^<^, <v< and prefer <<v etc
        auto end = std::remove_if(out.begin(), out.end(), [](auto const& seq) -> bool {
            std::unordered_map<char, bool> found{};
            char current{seq.front()};
            for (auto const& entry : seq) {
                if (entry == 'A') {
                    found.clear();
                    current = entry;
                    continue;
                }

                if (found.contains(entry)) {
                    return true;
                }

                if (entry != current) {
                    found[current] = true;
                    current = entry;
                    continue;
                }
            }
            return false;
        });
        out.erase(end, out.end());

        solve_cache_[inp] = out;
        return out;
    }
};

struct DirectionalKeypad : public Keypad {
    DirectionalKeypad()
        : Keypad(std::unordered_map<Pos, char, PosHash, PosEqual>{
              {{1, 0}, '^'}, {{2, 0}, 'A'}, {{0, 1}, '<'}, {{1, 1}, 'v'}, {{2, 1}, '>'}}) {}

    std::unordered_map<std::string, int64_t> solve_lengths_rec_cache_{};
    int64_t solve_lengths_rec(char current, char finish, int64_t depth = 2) {
        std::string cache_entry{current, finish};
        cache_entry += std::to_string(depth);
        if (solve_lengths_rec_cache_.contains(cache_entry)) {
            return solve_lengths_rec_cache_[cache_entry];
        }

        auto sequences = get_moves(current, finish);
        if (depth == 1) {
            assert(sequences.size() > 0);
            int64_t out{static_cast<int64_t>(sequences.front().size())};
            return out;
        }

        int64_t shortest_path{INT64_MAX};
        for (auto const& seq : sequences) {
            int64_t length{0};
            std::string cand{"A" + seq};
            for (size_t i{0}; i < cand.size() - 1; i++) {
                length += solve_lengths_rec(cand[i], cand[i + 1], depth - 1);
            }
            shortest_path = std::min({shortest_path, length});
        }
        solve_lengths_rec_cache_[cache_entry] = shortest_path;
        return shortest_path;
    }
};

int64_t solve(std::vector<std::string> const& inp, int64_t depth) {
    NumericKeypad nkpd{};
    DirectionalKeypad dkpd{};

    int64_t ans{0};
    for (auto code : inp) {
        auto possible_sequences_1 = nkpd.solve(code);
        int64_t shortest_path{INT64_MAX};
        for (auto const& seq : possible_sequences_1) {
            assert(seq.size() > 0);

            int64_t length{0};
            std::string cand{"A" + seq};
            for (size_t i{0}; i < cand.size() - 1; i++) {
                length += dkpd.solve_lengths_rec(cand[i], cand[i + 1], depth);
            }
            shortest_path = std::min({shortest_path, length});
        }

        std::regex pattern("0*([1-9]\\d*)");
        std::smatch match{};
        int64_t number{0};
        int64_t length{shortest_path};
        assert(std::regex_search(code, match, pattern));
        number = std::stoi(match[1].str());
        int64_t add{number * length};
        ans += add;
    }
    return ans;
}

int64_t solve_1(std::vector<std::string> const& inp) { return solve(inp, 2); }

int64_t solve_2(std::vector<std::string> inp) { return solve(inp, 25); }

int main() {
    auto sample = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 126384);

    auto input = string_utils::read_input(AOC_INPUT);
    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
