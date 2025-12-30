/**
 * https://adventofcode.com/2016/day/9
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

int64_t solve_1(std::vector<std::string> const& inp) {
    auto const& line = inp[0];
    std::string out{};
    std::regex pattern("\\((\\d+)x(\\d+)\\)");
    std::smatch match{};
    for (size_t i{0}; i < line.size();) {
        if (line[i] == '(') {
            std::regex_search(line.cbegin() + i, line.cend(), match, pattern);
            int64_t chars{std::stoll(match[1])};
            int64_t repeat{std::stoll(match[2])};
            auto word = line.substr(i + match.str().size(), chars);
            for (int64_t j{0}; j < repeat; j++) {
                out += word;
            }
            i += match.str().size();
            i += chars;
            continue;
        }
        out += line[i];
        i++;
    }
    return out.size();
}

int64_t decompress(std::string const& inp, std::string m) {
    int64_t count{0};
    for (size_t i{0}; i < inp.size();) {
        if (inp[i] == '(') {
            // Assume that all nested is within the parent's size
            std::regex pattern("\\((\\d+)x(\\d+)\\)");
            std::smatch match{};
            std::regex_search(inp.cbegin() + i, inp.cend(), match, pattern);

            assert(match.size() == 3);
            auto chars = std::stoll(match[1]);
            auto repeat = std::stoll(match[2]);
            assert(chars > 0);
            assert(repeat > 0);

            auto base = inp.cbegin() + match.str().size() + i;
            auto val = decompress({base, base + chars}, match.str());
            i += match.str().size() + chars;
            count += repeat * val;
        } else {
            count++;
            i++;
        }
    }
    return count;
}

int64_t solve_2(std::vector<std::string> inp) {
    for (auto& ch : inp[0]) {
        if (std::isupper(ch)) {
            ch = '.';
        }
    }
    auto out = decompress(inp[0], "");
    return out;
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 6);
    assert(solve_2(sample) == 6);

    auto sample1 = aoc::utils::read_input("day09-sample-1.input");
    assert(solve_1(sample1) == 7);

    auto sample2 = aoc::utils::read_input("day09-sample-2.input");
    assert(solve_1(sample2) == 9);

    auto sample3 = aoc::utils::read_input("day09-sample-3.input");
    assert(solve_1(sample3) == 11);

    auto sample4 = aoc::utils::read_input("day09-sample-4.input");
    assert(solve_1(sample4) == 6);

    auto sample5 = aoc::utils::read_input("day09-sample-5.input");
    assert(solve_1(sample5) == 18);
    assert(solve_2(sample5) == 20);

    auto sample6 = aoc::utils::read_input("day09-sample-6.input");
    assert(solve_2(sample6) == 241920);

    auto sample7 = aoc::utils::read_input("day09-sample-7.input");
    assert(solve_2(sample7) == 445);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_1(inp);
        assert(res == 115118);
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_2(inp);
        assert(res == 11107527530);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
