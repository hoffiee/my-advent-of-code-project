/**
 * https://adventofcode.com/2024/day/24
 *
 * Ohh my, attempted some steps to resolve it automatically, backed off and reused the same logic to identify faulty
 * outputs, then generated a graph and inspected manually. It kept flagging z31, and z32 as faulty even though they're
 * not part of the final answer, later figured out that was because I were using int64_t, so switching to uint64_t fixed
 * that.
 *
 * Generates a network.dot that I inspected with xdot
 *
 * https://theorycircuit.com/wp-content/uploads/2018/07/full-adder-circuit.png
 */
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <icecream.hpp>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "aoc_utils.h"
#include "string_utils.h"

// TODO move to utils
struct TupleHash {
    size_t operator()(std::tuple<std::string, std::string> const& t) const {
        return std::hash<std::string>{}(std::get<0>(t) + std::get<1>(t));
    }
};

struct Gate {
    std::string name_{};
    std::string input1_{};
    std::string input2_{};
    std::string type_{};
    std::optional<uint64_t> value_{};

    friend std::ostream& operator<<(std::ostream& os, Gate const& g) {
        if (g.value_.has_value()) {
            os << g.name_ << "(" << g.value_.value() << ")";
        } else {
            os << g.input1_ << " " << g.type_ << " " << g.input2_ << " > " << g.name_;
        }
        return os;
    }
};

struct Memory {
    std::unordered_map<std::string, Gate> memory_{};
    uint64_t bits_{};

    Memory(std::vector<std::string> inp) {
        bool parsing_memory{true};
        for (auto line : inp) {
            if (line == "") {
                parsing_memory = false;
                continue;
            }

            if (parsing_memory) {
                std::regex pattern("(.*): (\\d+)");
                std::smatch matches{};
                assert(std::regex_match(line, matches, pattern));
                std::string key{matches[1].str()};
                uint64_t value{std::stoull(matches[2].str())};
                memory_[key].value_ = value;
                memory_[key].name_ = key;

                uint64_t current_bits = std::stoll(key.substr(1, 2));
                if (bits_ < current_bits) {
                    bits_ = current_bits;
                }
                continue;
            }
            auto entries = aoc::string::split(line, ' ');
            memory_[entries[4]].input1_ = entries[0];
            memory_[entries[4]].input2_ = entries[2];
            memory_[entries[4]].type_ = entries[1];
            memory_[entries[4]].name_ = entries[4];
        }
    }

    static uint64_t oper(std::string op, uint64_t in1, uint64_t in2) {
        if (op == "AND") {
            return in1 & in2;
        }
        if (op == "XOR") {
            return in1 ^ in2;
        }
        if (op == "OR") {
            return in1 | in2;
        }
        assert(false);
        return -1;
    }

    void set(char mem, uint64_t val) {
        for (auto& [key, gate] : memory_) {
            if (key.front() != mem) {
                continue;
            }
            auto num = string_utils::numbers_from_string(gate.name_)[0];
            gate.value_ = static_cast<uint64_t>((val & (1 << num)) > 0);
        }
    }
    void set_x(uint64_t val) { set('x', val); }
    void set_y(uint64_t val) { set('y', val); }

    uint64_t calculate() {
        uint64_t val{0};
        for (auto const& [key, gate] : memory_) {
            if (key.front() != 'z') {
                continue;
            }
            auto num = string_utils::numbers_from_string(gate.name_)[0];
            val |= get_value(key) << num;
        }
        return val;
    }

    uint64_t get_value(std::string name) {
        if (!memory_.contains(name)) {
            return 0;
        }
        if (memory_[name].value_.has_value()) {
            return memory_[name].value_.value();
        }

        uint64_t input1 = get_value(memory_[name].input1_);
        uint64_t input2 = get_value(memory_[name].input2_);

        memory_[name].value_ = oper(memory_[name].type_, input1, input2);
        return memory_[name].value_.value();
    }
};

void print_graph(std::vector<std::string> const& inp) {
    std::ofstream file{"network.dot"};
    if (!file.is_open()) {
        assert(false);
    }
    file << "digraph D {" << std::endl;
    bool search{true};
    int step{0};
    for (auto line : inp) {
        if (search) {
            if (line == "") {
                search = false;
            }
            continue;
        }
        auto entries = aoc::string::split(line, ' ');
        file << entries[0] + " -> " + entries[1] + "_" + std::to_string(step) << std::endl;
        file << entries[2] + " -> " + entries[1] + "_" + std::to_string(step) << std::endl;
        file << entries[1] + "_" + std::to_string(step) + " -> " + entries[4] << std::endl;
        step++;
    }
    file << "}" << std::endl;
    file.close();
}

uint64_t solve_1(std::vector<std::string> inp) {
    Memory memory(inp);
    return memory.calculate();
}

std::string solve_2(std::vector<std::string> inp) {
    uint64_t bits{};
    {
        // TODO Fix a better way of getting the number of bits from input.
        Memory mem{inp};
        bits = mem.bits_;
    }

    // Find broken bits.
    std::unordered_map<std::string, bool> faulty{};
    for (uint64_t bit{0}; bit < bits; bit++) {
        auto check_faulty = [&inp, &faulty](uint64_t x, uint64_t y, uint64_t bit) -> void {
            Memory memory(inp);
            memory.set_x(x);
            memory.set_y(y);
            memory.calculate();
            char key[4]{};
            std::sprintf(key, "z%02ld", bit);
            if (memory.get_value(key) == 0) {
                faulty[key];
            }
        };

        check_faulty(1 << bit, 0, bit);
        check_faulty(0, 1 << bit, bit);
        check_faulty(1 << bit, 1 << bit, bit + 1);
    }

    for (auto [key, val] : faulty) {
        std::cout << key << ", ";
    }
    std::cout << std::endl;

    print_graph(inp);

    std::vector<std::string> swapped{// z38, z16, z08, z39, z33, z09,
                                     "z08", "cdj",
                                     // z38, z16, z39, z33
                                     "z16", "mrb",
                                     // z38, z39, z33
                                     "qjd", "dhm",
                                     // z33
                                     "z32", "gfm"};

    std::sort(swapped.begin(), swapped.end());
    return aoc::string::join(swapped, ",");
}

int main() {
    auto sample1 = string_utils::read_input("day24-sample-1.input");
    assert(solve_1(sample1) == 4);

    auto sample2 = string_utils::read_input("day24-sample-2.input");
    assert(solve_1(sample2) == 2024);

    auto input = string_utils::read_input(AOC_INPUT);
    auto part1 = solve_1(input);
    assert(part1 == 55114892239566);

    auto fixed = string_utils::read_input("day24-fixed.input");
    auto part2 = solve_2(fixed);
    assert(part2 == "cdj,dhm,gfm,mrb,qjd,z08,z16,z32");

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
