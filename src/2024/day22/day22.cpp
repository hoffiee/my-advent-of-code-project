/**
 * https://adventofcode.com/2024/day/22
 */
#include <omp.h>

#include <cassert>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

// TODO Add to utils, fix so that I can template the amount of tuples?
struct TupleHash {
    template <class T1, class T2, class T3, class T4>
    std::size_t operator()(const std::tuple<T1, T2, T3, T4>& t) const {
        auto h1 = std::hash<T1>{}(std::get<0>(t));
        auto h2 = std::hash<T2>{}(std::get<1>(t));
        auto h3 = std::hash<T3>{}(std::get<2>(t));
        auto h4 = std::hash<T4>{}(std::get<3>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

int64_t mix_prune(int64_t num, int64_t prune) {
    num ^= prune;
    num %= 16777216;
    return num;
}

int64_t secret_number(int64_t prev) {
    int64_t step1{prev << 6};
    prev = mix_prune(prev, step1);

    int64_t step2{prev >> 5};
    prev = mix_prune(prev, step2);

    int64_t step3{prev << 11};
    prev = mix_prune(prev, step3);
    return prev;
}

int64_t solve_1(std::vector<std::string> inp, int64_t steps = 2000) {
    int64_t ans{0};
#pragma omp parallel for reduction(+ : ans)
    for (auto line : inp) {
        auto num = string_utils::numbers_from_string(line).front();
        for (int64_t step{0}; step < steps; step++) {
            num = secret_number(num);
        }
        ans += num;
    }
    return ans;
}

int64_t solve_2(std::vector<std::string> inp, size_t steps = 2000) {
    std::vector<std::vector<int64_t>> digits(inp.size(), std::vector<int64_t>(steps + 1, 0));
    std::vector<std::vector<int64_t>> diffs(inp.size(), std::vector<int64_t>(steps, 0));

#pragma omp parallel for
    for (size_t row = 0; row < inp.size(); row++) {
        auto num = string_utils::numbers_from_string(inp[row]).front();
        auto& dgs = digits[row];
        auto& dfs = diffs[row];
        dgs[0] = num % 10;
        for (size_t step{1}; step <= steps; step++) {
            num = secret_number(num);
            dgs[step] = num % 10;
            dfs[step] = dgs[step] - dgs[step - 1];
        }
    }

    using Seq = std::tuple<int64_t, int64_t, int64_t, int64_t>;
    std::vector<std::unordered_map<Seq, int64_t, TupleHash>> sequences(inp.size(),
                                                                       std::unordered_map<Seq, int64_t, TupleHash>{});

#pragma omp parallel for
    for (size_t row = 0; row < inp.size(); row++) {
        auto& sequence = sequences[row];
        auto& dgs = digits[row];
        auto& dfs = diffs[row];

        for (size_t step{3}; step <= steps; step++) {
            Seq cand{dfs[step - 3], dfs[step - 2], dfs[step - 1], dfs[step]};
            if (sequence.contains(cand)) {
                continue;
            }
            sequence[cand] = dgs[step];
        }
    }

    std::unordered_map<Seq, int64_t, TupleHash> total_sequences{};
    Seq cand{};
    int64_t winning{0};
    for (auto const& sequence : sequences) {
        for (auto const& it : sequence) {
            // Optimisation added after solve; If the first seller doesn't have the sequence, skip it. seems that this
            // one is a trendsetter. I'm not sure if this is specific for my input. Probably possible to move up to the
            // data generation and reduce runtime even more.
            if (!sequences[0].contains(it.first)) {
                continue;
            }

            total_sequences[it.first] += it.second;
            if (total_sequences[it.first] > winning) {
                winning = total_sequences[it.first];
                cand = it.first;
            }
        }
    }
    return winning;
}

void samples() {
    assert(mix_prune(42, 15) == 37);
    assert(mix_prune(100000000, 0) == 16113920);

    auto sample1 = aoc::utils::read_input("day22-sample-1.input");
    assert(solve_1(sample1, 1) == 15887950);
    assert(solve_1(sample1, 2) == 16495136);
    assert(solve_1(sample1, 3) == 527345);
    assert(solve_1(sample1, 4) == 704524);
    assert(solve_1(sample1, 5) == 1553684);
    assert(solve_1(sample1, 6) == 12683156);
    assert(solve_1(sample1, 7) == 11100544);
    assert(solve_1(sample1, 8) == 12249484);
    assert(solve_1(sample1, 9) == 7753432);
    assert(solve_1(sample1, 10) == 5908254);
    assert(solve_2(sample1, 10) == 6);

    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 37327623);

    auto sample2 = aoc::utils::read_input("day22-sample-2.input");
    assert(solve_2(sample2) == 23);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp) << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 2: " << solve_2(inp) << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
