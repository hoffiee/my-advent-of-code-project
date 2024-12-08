#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

static std::pair<std::vector<int>, std::vector<int>> read_and_parse_data(string filename) {
    std::ifstream input{};
    input.open(filename);

    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }

    string line{};
    std::vector<int> player_1{};
    std::vector<int> player_2{};
    while (getline(input, line)) {
        player_1.push_back(static_cast<int>(line.front() - 'A' + 1));
        player_2.push_back(static_cast<int>(line.back() - 'X' + 1));
    }

    return {player_1, player_2};
}

static int solution_1(pair<vector<int>, vector<int>> input) {
    auto& [player_1, player_2] = input;

    int score = 0;
    for (size_t i = 0; i < player_1.size(); ++i) {
        if (player_1.at(i) == 1) {
            score += 3 * ((player_2.at(i) == 1) + 2 * (player_2.at(i) == 2));
        } else if (player_1.at(i) == 2) {
            score += 3 * ((player_2.at(i) == 2) + 2 * (player_2.at(i) == 3));
        } else if (player_1.at(i) == 3) {
            score += 3 * ((player_2.at(i) == 3) + 2 * (player_2.at(i) == 1));
        }
    }
    return score + std::accumulate(player_2.begin(), player_2.end(), 0);
}

static int solution_2(pair<vector<int>, vector<int>> input) {
    auto& [player_1, player_2] = input;

    int score = 0;
    for (size_t i = 0; i < player_1.size(); ++i) {
        int elf_play = player_1.at(i);

        if (player_2.at(i) == 1) {
            score += 1 * (elf_play == 2) + 2 * (elf_play == 3) + 3 * (elf_play == 1);
        } else if (player_2.at(i) == 2) {
            score += 3;
            score += 1 * (elf_play == 1) + 2 * (elf_play == 2) + 3 * (elf_play == 3);
        } else if (player_2.at(i) == 3) {
            score += 6;
            score += 1 * (elf_play == 3) + 2 * (elf_play == 1) + 3 * (elf_play == 2);
        }
    }
    return score;
}

int main(void) {
    auto sample = read_and_parse_data("day02-sample.input");
    auto input = read_and_parse_data("day02.input");

    std::cout << "Sample solution 1:\t" << solution_1(sample) << std::endl;
    std::cout << "solution 1:\t\t" << solution_1(input) << std::endl;

    std::cout << "Sample solution 2:\t" << solution_2(sample) << std::endl;
    std::cout << "solution 2:\t\t" << solution_2(input) << std::endl;
}
