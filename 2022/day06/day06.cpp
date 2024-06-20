#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using std::string;

static string read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    getline(input, line);
    return line;
}

static int64_t solution(string message, size_t offset) {
    std::unordered_map<char, int64_t> freq;
    size_t i = 0;
    for (; i < message.length(); ++i) {
        ++freq[message.at(i)];
        if (i >= offset) {
            --freq[message.at(i - offset)];
            if (freq[message.at(i - offset)] == 0) {
                freq.erase(message.at(i - offset));
            }
        }
        if (freq.size() == offset) {
            break;
        }
    }
    return static_cast<int64_t>(i + 1);
}

static void run_and_check_solutions(string task, int64_t (*solution_1)(string), int64_t expected_1,
                                    int64_t (*solution_2)(string), int64_t expected_2) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto message = read_and_parse_data(task);
    std::cout << task << std::endl;
    std::cout << "\ttask 1: " << solution_1(message) << " (" << expected_1 << ")" << std::endl;
    std::cout << "\ttask 2: " << solution_2(message) << " (" << expected_2 << ")" << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "execution time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns"
              << std::endl;
}

int main(void) {
    auto solution_1 = [](string msg) { return solution(msg, 4); };
    auto solution_2 = [](string msg) { return solution(msg, 14); };

    std::vector<string> test_samples = {
        "mjqjpqmgbljsphdztnvjfqwrcgsmlb",     // expects 7, 19
        "bvwbjplbgvbhsrlpgdmjqwftvncz",       // expects 5, 23
        "nppdvjthqldpwncqszvftbrmjlhg",       // expects 6, 23
        "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",  // expects 10, 29
        "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"    // expects 11, 26
    };
    for (auto& test : test_samples) {
        std::cout << solution_1(test) << ", " << solution_2(test) << std::endl;
    }

    run_and_check_solutions("day06-sample.input", solution_1, 7, solution_2, 19);
    run_and_check_solutions("day06.input", solution_1, 1100, solution_2, 2421);
}
