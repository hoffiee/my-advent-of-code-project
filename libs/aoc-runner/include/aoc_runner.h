#ifndef AOC_RUNNER_H_
#define AOC_RUNNER_H_

#include <functional>
#include <string>
#include <vector>

namespace aoc {

int run(int argc, char** argv, std::function<void(void)> sample,
        std::function<void(std::vector<std::string> const&)> solve_1,
        std::function<void(std::vector<std::string> const&)> solve_2, std::vector<std::string> const& input);

};

#endif
