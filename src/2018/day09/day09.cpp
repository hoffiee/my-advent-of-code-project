/**
 * https://adventofcode.com/2018/day/9
 *
 * using std::deque and std::rotate seems to work but std::rotate swaps the
 * elements so it got really slow when increasing the amount of marbles. Switching
 * it out for a linked list where I move an iterator around to keep track of
 * the current marble.
 *
 * aoc_tags: deque, linked-list
 */
#include <algorithm>
#include <cassert>
#include <deque>
#include <icecream.hpp>
#include <list>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

struct MarbleBoard {
    std::list<int64_t> container_{0};
    std::list<int64_t>::iterator it_{container_.begin()};

    void insert(int64_t val) {
        // std::next doesn't seem to wrap around as I first expected it to do.
        for (int i{0}; i < 2; i++) {
            it_++;
            if (it_ == container_.end()) {
                it_ = container_.begin();
            }
        }
        it_ = container_.insert(it_, val);
    }

    int64_t remove() {
        for (int i{0}; i < 7; i++) {
            if (it_ == container_.begin()) {
                it_ = container_.end();
            }
            it_--;
        }
        int64_t out{*it_};
        it_ = container_.erase(it_);
        return out;
    }

    int64_t front() const { return *it_; }

    size_t size() const { return container_.size(); }
};

void print(MarbleBoard const& inp, int64_t player = 0, int64_t marble = 0) {
    std::cout << "[" << player + 1 << "|" << marble << "] ";
    for (auto const& it_ : inp.container_) {
        if (it_ == inp.front()) {
            std::cout << "(" << it_ << ") ";
            continue;
        }
        std::cout << it_ << " ";
    }
    std::cout << std::endl;
}

int64_t solve(std::vector<std::string> const& inp, int64_t multiplier = 1) {
    auto numbers = aoc::string::numbers_from_string(inp[0]);
    assert(numbers.size() == 2);

    int64_t players = numbers[0];
    int64_t marbles = numbers[1] * multiplier;

    MarbleBoard game{};
    std::vector<int64_t> scores(players, 0);

    int64_t player{-1};
    for (int64_t marble{1}; marble < marbles + 1; marble++) {
        player = (player + 1) % players;
        if (marble % 23 != 0) {
            game.insert(marble);
            continue;
        }
        scores[player] += marble;
        scores[player] += game.remove();
    }
    return *std::max_element(scores.begin(), scores.end());
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve(sample) == 32);

    auto sample1 = aoc::utils::read_input("day09-sample-1.input");
    assert(solve(sample1) == 8317);

    auto sample2 = aoc::utils::read_input("day09-sample-2.input");
    assert(solve(sample2) == 146373);

    auto sample3 = aoc::utils::read_input("day09-sample-3.input");
    assert(solve(sample3) == 2764);

    auto sample4 = aoc::utils::read_input("day09-sample-4.input");
    assert(solve(sample4) == 54718);

    auto sample5 = aoc::utils::read_input("day09-sample-5.input");
    assert(solve(sample5) == 37305);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve(inp);
        assert(res == 398048);
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve(inp, 100);
        assert(res == 3180373421);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
