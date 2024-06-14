#include <chrono>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

using std::string;
using std::tuple;
using std::vector;

static vector<tuple<int, int, int, int>> read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    vector<std::tuple<int, int, int, int>> pairs;
    while (getline(input, line)) {
        int elf_1_start, elf_1_end;
        int elf_2_start, elf_2_end;
        sscanf(line.c_str(), "%d-%d,%d-%d", &elf_1_start, &elf_1_end, &elf_2_start, &elf_2_end);
        pairs.emplace_back(std::make_tuple(elf_1_start, elf_1_end, elf_2_start, elf_2_end));
    }
    return pairs;
}

static int solution_1(vector<tuple<int, int, int, int>> input) {
    int count = 0;
    for (auto& it : input) {
        auto [a, b, c, d] = it;
        if ((a <= c && d <= b) || (c <= a && b <= d)) {
            ++count;
        }
    }
    return count;
}

static int solution_2(vector<tuple<int, int, int, int>> input) {
    int count = 0;
    for (auto& it : input) {
        auto [a, b, c, d] = it;
        if (!((b < c) || (d < a))) {
            ++count;
        }
    }
    return count;
}

static void run_and_check_solutions(string task, int (*solution_1)(vector<tuple<int, int, int, int>>), int expected_1,
                                    int (*solution_2)(vector<tuple<int, int, int, int>>), int expected_2) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto input = read_and_parse_data(task);
    std::cout << task << std::endl;
    std::cout << "\ttask 1: " << solution_1(input) << " (" << expected_1 << ")" << std::endl;
    std::cout << "\ttask 2: " << solution_2(input) << " (" << expected_2 << ")" << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "execution time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns"
              << std::endl;
}

int main(void) {
    run_and_check_solutions("day4-sample.input", solution_1, 2, solution_2, 4);
    run_and_check_solutions("day4.input", solution_1, 466, solution_2, 865);
}
