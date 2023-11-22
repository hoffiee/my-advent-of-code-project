#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

static std::pair<int, int> gift_wrapping(std::string input) {
    int length = 0;
    int width = 0;
    int height = 0;
    char del = '\0';

    std::stringstream ss(input);
    ss >> length >> del >> width >> del >> height;

    std::vector<int> sides_size{
        length * width,
        width * height,
        height * length,
    };

    std::vector<int> sides_dist{
        2 * length,
        2 * width,
        2 * height,
    };

    int sum_ribbon = std::accumulate(sides_dist.cbegin(), sides_dist.cend(), static_cast<int>(0));

    auto double_sum = [](const int acc, const int num) { return acc + 2 * num; };

    return {std::accumulate(sides_size.cbegin(), sides_size.cend(), static_cast<int>(0), double_sum) +
                *std::min_element(sides_size.cbegin(), sides_size.cend()),
            sum_ribbon - *std::max_element(sides_dist.cbegin(), sides_dist.cend()) + length * width * height};
}

static std::pair<int, int> solve(std::vector<std::string> input) {
    int paper = 0;
    int ribbon = 0;
    for (auto gift : input) {
        auto [p, r] = gift_wrapping(gift);
        paper += p;
        ribbon += r;
    }

    return {paper, ribbon};
}

static void test() {
    assert(gift_wrapping("2x3x4").first == 58);
    assert(gift_wrapping("1x1x10").first == 43);

    assert(gift_wrapping("2x3x4").second == 34);
    assert(gift_wrapping("1x1x10").second == 14);
}

int main() {
    test();

    std::ifstream input_file;
    input_file.open("day02.input");
    if (!input_file.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::string line;
    std::vector<std::string> input;
    while (getline(input_file, line)) {
        input.emplace_back(line);
    }

    auto [paper, ribbon] = solve(input);
    std::cout << paper << " " << ribbon << std::endl;

    return 0;
}
