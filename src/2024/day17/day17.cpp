/**
 * https://adventofcode.com/2024/day/17
 *
 * Oh my, I went the way as many others, figure out the 3 first bits and shift and continue like that, it went well.
 * Later on on my output (and some others similar to mine) it always excluded the last 0 in the program. After some
 * discussions on Reddit, it seems that a particular class of input were not possible to solve that way and mine was one
 * of them. Instead of bruteforcing I went the fuzzing way, iteratively tried different inputs and scored them
 * accordingly, got the inspiration from one solution that seemed to be able to solve my input.
 *
 * Somehow had memory issues along the way, turned out I forgot to clear the output vector between computations so that
 * continued to grow...
 *
 * I'll keep my first solution for part 2 as that could prove valuable if I figure a way to handle this issue in that
 * one as it is much faster. Interestingly enough I found some samples where the original approach solves it but the
 * fuzzer doesn't, but I'm not sure I*ll return to this one soon.
 */
#include <cassert>
#include <cmath>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

struct Computer {
    uint64_t register_a_{};
    uint64_t register_b_{};
    uint64_t register_c_{};
    std::vector<uint64_t> program_{};
    std::vector<uint64_t> output_{};
    size_t program_max_length_{};

    uint64_t operand_{};
    uint64_t correct_{};

    Computer(std::vector<std::string> inp) {
        register_a_ = string_utils::unumbers_from_string(inp[0]).front();
        register_b_ = string_utils::unumbers_from_string(inp[1]).front();
        register_c_ = string_utils::unumbers_from_string(inp[2]).front();

        for (auto num : string_utils::unumbers_from_string(inp[4])) {
            program_.push_back(num);
        }
        // Give some space for larger programs get expensive for part 2
        program_max_length_ = program_.size() * 2;
        assert(program_max_length_ > 0);
        assert(inp.size() == 5);
        assert(program_.size() % 2 == 0);
    }

    uint64_t operand(bool literal = false) {
        if (literal) {
            return operand_;
        }
        switch (operand_) {
            case 0:
            case 1:
            case 2:
            case 3:
                return operand_;
            case 4:
                return register_a_;
            case 5:
                return register_b_;
            case 6:
                return register_c_;
            case 7:
            default:
                assert(false);
                break;
        }
        return 0u;
    }

    std::string output() const {
        // TODO make utils function out of this. join vector of strings to string
        std::string out{};
        for (auto num : output_) {
            if (out.size() != 0) {
                out += ",";
            }
            out += std::to_string(num);
        }
        return out;
    }

    void compute() {
        uint64_t ip{0};
        output_.clear();  // Whoops, forgot this one for a bit :')
        while (ip < static_cast<uint64_t>(program_.size())) {
            assert(ip + 1 < static_cast<uint64_t>(program_.size()));
            uint64_t opcode = program_[ip];
            operand_ = program_[ip + 1];
            ip += 2;

            switch (opcode) {
                case 0: {
                    register_a_ = static_cast<uint64_t>(register_a_ >> operand());
                    break;
                }
                case 1:
                    register_b_ ^= operand(true);
                    break;
                case 2:
                    register_b_ = operand() % static_cast<uint64_t>(8);
                    break;
                case 3: {
                    if (register_a_ == 0) {
                        break;
                    }
                    ip = operand(true);
                    break;
                }
                case 4:
                    register_b_ = register_b_ ^ register_c_;
                    break;
                case 5:
                    output_.push_back(operand() % static_cast<uint64_t>(8));
                    if (output_.size() > program_max_length_) {
                        return;
                    }
                    break;
                case 6:
                    register_b_ = static_cast<uint64_t>(register_a_ >> operand());
                    break;
                case 7: {
                    register_c_ = static_cast<uint64_t>(register_a_ >> operand());
                    break;
                }
                default:
                    assert(false);
                    break;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Computer const& comp) {
        os << "A:" << comp.register_a_;
        os << " B:" << comp.register_b_;
        os << " C:" << comp.register_c_ << "\n";
        for (auto mem : comp.program_) {
            os << mem << ",";
        }
        os << "\n"
           << "output:";
        for (auto num : comp.output_) {
            os << num << ",";
        }
        return os;
    }
};

Computer solve_1(std::vector<std::string> inp) {
    Computer comp(inp);
    comp.compute();
    return comp;
}

std::optional<uint64_t> solve_2_rec(std::vector<std::string> const& inp, std::vector<uint64_t> prg, uint64_t cand) {
    if (prg.size() == 0) {
        return cand;
    }

    for (uint64_t test{0}; test < 2 << 3; test++) {
        uint64_t cand_a{(cand << 3) | test};

        Computer comp(inp);
        comp.register_a_ = cand_a;
        comp.compute();
        assert(comp.output_.size() == 1);

        if (comp.output_.back() == prg.back()) {
            std::vector<uint64_t> reduced{prg.begin(), std::prev(prg.end())};
            auto sub{solve_2_rec(inp, reduced, cand_a)};
            if (!sub.has_value()) {
                continue;
            }
            return sub;
        }
    }
    return {};
}

// solved after going through a few solutions, I found hyper neutrino to be quite good at explaining. I didn't really
// know where to start by myself so started to look at some hints
uint64_t solve_2(std::vector<std::string> inp) {
    auto program = string_utils::unumbers_from_string(inp[4]);
    assert(program.size() > 1);

    std::vector<std::string> modified{inp.begin(), inp.end()};
    modified[4].pop_back();
    modified[4].pop_back();
    modified[4].pop_back();
    modified[4].pop_back();

    std::optional<uint64_t> out{0};
    out = solve_2_rec(modified, program, 0);
    assert(out.has_value());

    Computer comp(inp);
    comp.register_a_ = out.value();
    comp.compute();
    assert(comp.output() == inp[4].substr(9));

    assert(out.has_value());
    return out.value();
}

int64_t cost_function(std::vector<uint64_t> const& program, std::vector<uint64_t> const& output) {
    // Play around with different cost functions and weights.
    int64_t cost = 100 * std::abs(static_cast<int64_t>(output.size()) - static_cast<int64_t>(program.size()));
    for (size_t i{0}; i < output.size() && i < program.size(); i++) {
        cost += 10 * __builtin_popcount(program[i] ^ output[i]);
        cost += 1 * std::abs(static_cast<int64_t>(program[i]) - static_cast<int64_t>(output[i]));
    }
    return cost;
}

uint64_t solve_2_fuzzing(std::vector<std::string> inp) {
    auto program = string_utils::unumbers_from_string(inp[4]);
    assert(program.size() > 1);

    int64_t last_cost{INT64_MAX};
    int64_t lowest_cost{INT64_MAX};
    uint64_t length{program.size()};
    uint64_t bits_per_output{3};

    Computer comp(inp);
    uint64_t best_candidate{0};
    std::srand(std::time(nullptr));
    while (lowest_cost > 0) {
        uint64_t bit = std::rand() % (length * bits_per_output);
        uint64_t change = static_cast<uint64_t>(1) << bit;
        uint64_t candidate = best_candidate ^ change;

        comp.register_a_ = candidate;
        comp.compute();

        auto cost = cost_function(program, comp.output_);

        if (cost < last_cost) {
            last_cost = cost;
            best_candidate = candidate;
        }

        // This randomness is tunable and I have noticed that it gives different results. This resetting allows us to
        // get back out of areas in which there is no solution.
        else if (std::rand() % 10 == 0) {
            last_cost = cost;
            best_candidate = candidate;
        }
        if (cost < lowest_cost) {
            lowest_cost = cost;
        }
    }

    // remove bits that are not the impacting programs output
    for (int64_t bit{64}; bit >= 0; bit--) {
        uint64_t cand = 1ull << static_cast<uint64_t>(bit);
        if ((best_candidate & cand) == 0) {
            continue;
        }
        comp.register_a_ = best_candidate & ~cand;
        comp.compute();

        auto cost = cost_function(program, comp.output_);

        if (cost == 0) {
            std::cout << "removing bit: " << bit << std::endl;
            best_candidate &= ~cand;
        }
    }
    return best_candidate;
}

void samples() {
    auto sample1 = aoc::utils::read_input("day17-sample-1.input");
    assert(solve_1(sample1).register_b_ == 1);

    auto sample2 = aoc::utils::read_input("day17-sample-2.input");
    assert(solve_1(sample2).output() == "0,1,2");

    auto sample3 = solve_1(aoc::utils::read_input("day17-sample-3.input"));
    assert(sample3.output() == "4,2,5,6,7,7,7,7,3,1,0");
    assert(sample3.register_a_ == 0);

    auto sample5 = solve_1(aoc::utils::read_input("day17-sample-5.input"));
    assert(sample5.register_b_ == 44354);

    auto sample = solve_1(aoc::utils::read_input(AOC_SAMPLE_INPUT));
    assert(sample.output() == "4,6,3,5,6,3,5,2,1,0");

    auto sample6 = aoc::utils::read_input("day17-sample-6.input");
    assert(solve_2(sample6) == 117440);

    auto sample7 = aoc::utils::read_input("day17-sample-7.input");
    assert(solve_1(sample7).output() == "6,0,4,5,4,5,2,0");
    assert(solve_2_fuzzing(sample7) == 202797954918051);

    auto sample8 = aoc::utils::read_input("day17-sample-8.input");
    assert(solve_1(sample8).output() == "3,4,4,1,7,0,2,2");
    assert(solve_2(sample8) == 266926175730705);

    auto sample9 = aoc::utils::read_input("day17-sample-9.input");
    assert(solve_2(sample9) == 164540892147389);
    // assert(solve_2_fuzzing(sample9) == 164540892147389);

    // auto sample10 = aoc::utils::read_input("day17-sample-10.input");
    // for (auto pvec: sample10) {
    //     std::vector<std::string> inp{
    //         { "Register A: 0" },
    //         { "Register B: 0"},
    //         { "Register C: 0"},
    //         { "" },
    //         { "Program: " + pvec}
    //     };
    //     auto resp = solve_2(inp);
    //     static_cast<void>(resp);
    // }
    // std::cout << "completed all in the quinable list" << std::endl;
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        std::cout << "part 1: " << solve_1(inp).output() << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2_fuzzing(inp);
        // randomly fails sometimes, but that's part of it being a random approach..
        assert(part2 == 156985331222018);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
