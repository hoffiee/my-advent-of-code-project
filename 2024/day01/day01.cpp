/**
 * https://adventofcode.com/2024/day/1
 */
#include <fstream>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

int solve_1(std::vector<std::string> inp) {
    std::vector<int> lst1{};
    std::vector<int> lst2{};

    for (auto& line : inp) {
        int num1{};
        int num2{};
        std::stringstream ss(line);
        ss >> num1 >> num2;
        lst1.push_back(num1);
        lst2.push_back(num2);
    }

    std::sort(lst1.begin(), lst1.end());
    std::sort(lst2.begin(), lst2.end());

    assert(lst1.size() == lst2.size());
    int sum{std::inner_product(lst1.cbegin(), lst1.cend(), lst2.cbegin(), static_cast<int>(0), std::plus<>(),
                               [](auto const& lhs, auto const& rhs) { return std::abs(lhs - rhs); })};

    return sum;
}

int solve_2(std::vector<std::string> inp) {
    std::vector<int> lst1{};
    std::unordered_map<int, int> lst2{};

    for (auto& line : inp) {
        int num1{};
        int num2{};
        std::stringstream ss(line);
        ss >> num1 >> num2;
        lst1.push_back(num1);
        lst2[num2]++;
    }

    return std::accumulate(lst1.cbegin(), lst1.cend(), static_cast<int>(0),
                           [&lst2](auto const sum, auto const val) { return sum + lst2[val] * val; });
}

int main() {
    std::ifstream input_file;
    input_file.open(AOC_INPUT);
    // input_file.open(AOC_SAMPLE_INPUT);
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::vector<std::string> input;
    std::string line;
    while (getline(input_file, line)) {
        input.push_back(line);
    }

    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
