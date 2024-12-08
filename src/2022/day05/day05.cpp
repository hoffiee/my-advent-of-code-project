#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#define MAX_CRATES 9

using std::pair;
using std::string;
using std::tuple;
using std::vector;
using stacks_t = vector<vector<char>>;
using instructions_t = vector<tuple<int, int, int>>;

static tuple<stacks_t, instructions_t> read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    stacks_t stack_of_crates{MAX_CRATES};
    instructions_t instructions;
    string line;
    bool parsing_stack_of_crates = true;
    while (getline(input, line)) {
        if (line.empty()) {
            parsing_stack_of_crates = false;
            continue;
        }
        if (parsing_stack_of_crates) {
            for (size_t i = 1; i < line.length(); i += 4) {
                if (line.at(i) != ' ' && !std::isdigit(line.at(i))) {
                    auto start = stack_of_crates.at(i / 4).begin();
                    stack_of_crates.at(i / 4).insert(start, line.at(i));
                }
            }
        } else {
            std::stringstream ss{line};
            string skip_word;
            int count = -1;
            int from = -1;
            int to = -1;
            ss >> skip_word >> count >> skip_word >> from >> skip_word >> to;
            instructions.emplace_back(std::make_tuple(count, from - 1, to - 1));
        }
    }
    return {stack_of_crates, instructions};
}

static string construct_output(stacks_t stack_of_crates) {
    string out = "";
    for (auto& stack : stack_of_crates) {
        if (!stack.empty()) {
            out += stack.back();
        }
    }
    return out;
}

static string solution_1(stacks_t stack_of_crates, instructions_t instructions) {
    for (auto [count, from, to] : instructions) {
        std::move(stack_of_crates.at(from).rbegin(), stack_of_crates.at(from).rbegin() + count,
                  std::back_inserter(stack_of_crates.at(to)));
        stack_of_crates.at(from).erase(stack_of_crates.at(from).end() - count, stack_of_crates.at(from).end());
    }
    return construct_output(stack_of_crates);
}

static string solution_2(stacks_t stack_of_crates, instructions_t instructions) {
    for (auto [count, from, to] : instructions) {
        std::move(stack_of_crates.at(from).end() - count, stack_of_crates.at(from).end(),
                  std::back_inserter(stack_of_crates.at(to)));
        stack_of_crates.at(from).erase(stack_of_crates.at(from).end() - count, stack_of_crates.at(from).end());
    }
    return construct_output(stack_of_crates);
}

static void run_and_check_solutions(string task, string (*solution_1)(stacks_t, instructions_t), string expected_1,
                                    string (*solution_2)(stacks_t, instructions_t), string expected_2) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto [stack_of_crates, instructions] = read_and_parse_data(task);
    std::cout << task << std::endl;
    std::cout << "\ttask 1: " << solution_1(stack_of_crates, instructions) << " (" << expected_1 << ")" << std::endl;
    std::cout << "\ttask 2: " << solution_2(stack_of_crates, instructions) << " (" << expected_2 << ")" << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "execution time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns"
              << std::endl;
}

int main(void) {
    run_and_check_solutions("day05-sample.input", solution_1, "CMZ", solution_2, "MCD");
    run_and_check_solutions("day05.input", solution_1, "FCVRLMVQP", solution_2, "RWLWGJGFD");
}
