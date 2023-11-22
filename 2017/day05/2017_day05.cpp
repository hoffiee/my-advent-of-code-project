#include AOC_HEADER

#include <functional>
#include <iostream>

__attribute__((unused)) static void print(std::vector<int> inp) {
    std::cout << "[";
    for (auto it : inp) {
        std::cout << it << ", ";
    }
    std::cout << std::endl;
}

static int step_through_instructions(std::vector<int> instructions, std::function<int(int)> step) {
    ssize_t current_instruction = 0;
    ssize_t next_instruction = 0;
    int count = 0;
    while (true) {
        ++count;
        int jump_offset = instructions.at(current_instruction);
        next_instruction += jump_offset;
        instructions.at(current_instruction) = step(jump_offset);
        current_instruction = next_instruction;
        if (next_instruction < 0 || static_cast<ssize_t>(instructions.size()) <= next_instruction) {
            break;
        }
    }
    return count;
}

std::pair<int, int> solve(std::vector<int>& instructions) {
    auto step_1 = [](const ssize_t n) { return n + 1; };
    auto step_2 = [](const ssize_t n) {
        if (n >= 3) {
            return n - 1;
        }
        return n + 1;
    };

    return {
        step_through_instructions(instructions, step_1),
        step_through_instructions(instructions, step_2),
    };
}
