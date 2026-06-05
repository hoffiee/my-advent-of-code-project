/**
 * https://adventofcode.com/2019/day/14
 */
#include <icecream.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2019::d14 {


struct Unit{};

using Reaction = std::unordered_map<std::string, int64_t>;
using Reactions = std::unordered_map<std::string, std::pair<int64_t, Reaction>>;


// int64_t recurse(Reactions const& reactions, std::string const& key, int64_t amount) {
//     IC(key, amount);
//     if (key == "ORE") {
//         return amount;
//     }
//
//     auto [mult, reqs] = reactions.at(key);
//
//     int64_t out{0};
//     // int64_t adjusted_amount{static_cast<int64_t>(std::ceil((double)amount/mult))};
//     int64_t adjusted_amount{(amount + mult - 1)/(mult)};
//     IC(mult, reqs, amount/mult, adjusted_amount);
//     for (auto const& [k,v]: reqs) {
//         out += recurse(reactions, k, adjusted_amount*v);
//     }
//     IC(out);
//     return out;
// }

std::unordered_map<std::string, int64_t> recurse(
    Reactions const& reactions,
    std::unordered_map<std::string, int64_t> const& keys
) {
    std::unordered_map<std::string, int64_t> out{};
    for (auto const& [key, amount]: keys) {
        auto [mult, reqs] = reactions.at(key);

        IC(mult, reqs);
        for (auto const& [key2, amount2]: reqs) {
            int64_t adjusted_multiplier{static_cast<int64_t>(std::ceil((double)amount/mult))};
            IC(key2, amount, amount2, amount*amount2);
            out[key2] += adjusted_multiplier*amount2;
        }
    }
    IC(out, out.contains("ORE"), out.size());
    if (out.contains("ORE") && out.size() == 1) {
        return out;
    }

    for (auto& [k, v]: out) {
        auto mult = std::get<0>(reactions.at(k));
        v = static_cast<int64_t>(std::ceil((double)v/mult) * mult);
        // IC(k, v, mult);
    }

    IC(out);
    IC("");
    return recurse(reactions, out);
}

int64_t solve_1(std::vector<std::string> inp) {
    Reactions reactions{};

    for (auto line: inp) {
        line.erase(std::remove_if(line.begin(), line.end(), [](auto const ch){ return ch == ','; }), line.end());
        auto spl = aoc::string::split(line, ' ');
        Reaction values{};
        for (std::size_t i{0}; i < spl.size(); i += 2) {
            if (spl.at(i) == "=>") {
                int64_t multiplier{std::stoi(spl.at(i+1))};
                std::string name{spl.at(i+2)};
                reactions[name] = {multiplier, values};
                break;
            }
            int64_t multiplier{std::stoi(spl.at(i))};
            std::string name{spl.at(i+1)};
            values[name] = multiplier;
        }
    }
    IC(reactions);

    // IC(recurse(reactions, {{"ORE", 1}}));
    // IC(recurse(reactions, {{"ORE", 9}}));
    // IC(recurse(reactions, {{"A", 1}}));
    // IC(recurse(reactions, "A", 2));
    // IC(recurse(reactions, "B", 3));
    // IC(recurse(reactions, "C", 5));
    // IC(recurse(reactions, "A", 10));
    // IC(recurse(reactions, "B", 24));
    // IC(recurse(reactions, "AB", 1));

    auto out = recurse(reactions, {{"FUEL", 1}});
    assert(out.contains("ORE"));
    int64_t out1{out.at("ORE")};
    IC(out1);
    return out1;
}

int64_t solve_2(std::vector<std::string> inp) {
    static_cast<void>(inp);
    return 0;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 165);
    assert(solve_2(sample) == 0);

    auto sample1 = aoc::utils::read_input("day14-sample-1.input");
    assert(solve_1(sample1) == 13312);

    auto sample2 = aoc::utils::read_input("day14-sample-2.input");
    assert(solve_1(sample2) == 180697);

    auto sample3 = aoc::utils::read_input("day14-sample-3.input");
    assert(solve_1(sample3) == 2210736);
}

};  // namespace aoc::y2019::d14

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = aoc::y2019::d14::solve_1(inp);
        std::cout << "part 1: " << res << std::endl;
        assert(res == 0);
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = aoc::y2019::d14::solve_2(inp);
        std::cout << "part 2: " << res << std::endl;
        assert(res == 0);
    };

    return aoc::run(argc, argv, aoc::y2019::d14::samples, solve_1_wrapper, solve_2_wrapper, input);
}
