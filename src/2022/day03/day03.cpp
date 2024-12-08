#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

static vector<string> read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    vector<string> compartments;
    while (getline(input, line)) {
        compartments.emplace_back(line);
    }
    return compartments;
}

static int char_to_int(unsigned char ch) {
    int out = 0;
    if (isupper(ch)) {
        out = ch - 'A' + 27;
    } else if (islower(ch)) {
        out = ch - 'a' + 1;
    }
    return out;
}

static int count_and_sum_priorities(string input, int occurence) {
    vector<int> character_frequency(26 * 2 + 1, 0);
    for (char item : input) {
        ++character_frequency.at(char_to_int(item));
    }
    auto ind = std::find(character_frequency.begin(), character_frequency.end(), occurence);
    return static_cast<int>(ind - character_frequency.begin());
}

static int solution_1(vector<string> input) {
    int sum_of_priorities = 0;
    for (auto& rucksack : input) {
        auto compartment_1 = rucksack.substr(0, rucksack.size() / 2);
        auto compartment_2 = rucksack.substr(rucksack.size() / 2, rucksack.size() / 2);
        std::sort(compartment_1.begin(), compartment_1.end());
        std::sort(compartment_2.begin(), compartment_2.end());
        {
            auto last = std::unique(compartment_1.begin(), compartment_1.end());
            compartment_1.erase(last, compartment_1.end());
        }
        {
            auto last = std::unique(compartment_2.begin(), compartment_2.end());
            compartment_2.erase(last, compartment_2.end());
        }
        auto rucksack_unique_items = compartment_1 + compartment_2;
        sum_of_priorities += count_and_sum_priorities(rucksack_unique_items, 2);
    }
    return sum_of_priorities;
}

static int solution_2(vector<string> input) {
    int sum_of_priorities = 0;
    for (size_t i = 0; i < input.size() / 3; ++i) {
        std::string combined_unique_rucksacks = "";
        for (size_t ii = 0; ii < 3; ++ii) {
            auto rucksack = input.at(3 * i + ii);
            std::sort(rucksack.begin(), rucksack.end());
            {
                auto last = std::unique(rucksack.begin(), rucksack.end());
                rucksack.erase(last, rucksack.end());
            }
            combined_unique_rucksacks += rucksack;
        }
        sum_of_priorities += count_and_sum_priorities(combined_unique_rucksacks, 3);
    }
    return sum_of_priorities;
}

static void run_and_check_solutions(string task, int (*solution_1)(vector<string>), int expected_1,
                                    int (*solution_2)(vector<string>), int expected_2) {
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
    run_and_check_solutions("day03-sample.input", solution_1, 157, solution_2, 70);
    run_and_check_solutions("day03.input", solution_1, 8153, solution_2, 2342);
}
