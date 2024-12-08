#include AOC_HEADER

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Register {
    int x = 1;
    int cycle = 0;
    int signal_strength = 0;

    Register() = default;
    void increment();
    void increment(int val);
    void set_x(int val);
};

void Register::increment() {
    const std::unordered_map<int, int> cycles = {{20, 0}, {60, 0}, {100, 0}, {140, 0}, {180, 0}, {220, 0}};
    ++cycle;
    if (cycles.contains(cycle)) {
        std::cout << cycle << " | " << x << " : " << x * cycle << std::endl;
        signal_strength += x * cycle;
    }
}

void Register::increment(int val) {
    while (val-- > 0) {
        increment();
    }
}

void Register::set_x(int val) { x += val; }

int64_t solve1(std::vector<std::string>& input) {
    Register reg;
    for (auto& instruction : input) {
        // std::cout << instruction << std::endl;

        std::stringstream ss(instruction);

        std::string op;
        int val = 0;
        ss >> op >> val;

        if (op == "noop") {
            reg.increment();
        } else if (op == "addx") {
            // std::cout << op << " " << val << std::endl;

            reg.increment(2);
            reg.set_x(val);
        }
    }

    return reg.signal_strength;
}

int64_t solve2(std::vector<std::string>& input) { return 0; }

std::pair<int64_t, int64_t> solve(std::vector<std::string>& input) { return {solve1(input), solve2(input)}; }
