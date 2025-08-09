/**
 * https://adventofcode.com/2019/day/13
 */
#include <icecream.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"
#include "intcode_computer.h"

namespace aoc::y2019::d13 {

int64_t solve_1(std::vector<std::string> inp) {
    static_cast<void>(inp);
    assert(inp.size() == 1);

    auto program = string_utils::numbers_from_string(inp.at(0));

    IntcodeComputer comp(program);

    comp.exec();

    auto const& output = comp.output_;

    int64_t count{0};
    for (std::size_t i{0}; i < output.size(); i += 3) {
        if (output.at(i+2) == 2) {
            count++;
        }
    }
    return count;
}

int64_t print(std::vector<int64_t> const& output, bool const draw) {
    int64_t score{0};
    int64_t max_x{0};
    int64_t max_y{0};
    for (std::size_t i{0}; i < output.size(); i += 3) {
        int64_t const x{output.at(i)};
        int64_t const y{output.at(i+1)};
        if (x == -1 && y == 0) {
            continue;
        }
        max_x = std::max(max_x, x);
        max_y = std::max(max_y, y);
    }

    std::vector<std::vector<int64_t>> screen(max_y + 1, std::vector<int64_t>(max_x + 1, 0));

    for (std::size_t i{0}; i < output.size(); i += 3) {
        int64_t const x{output.at(i)};
        int64_t const y{output.at(i+1)};
        if (x == -1 && y == 0) {
            score = output.at(i+2);
            continue;
        }
        screen.at(y).at(x) = output.at(i+2);
    }

    bool blocks_left{false};
    for (std::size_t y{0}; y < screen.size(); y++ ) {
        for (std::size_t x{0}; x < screen.front().size(); x++ ) {
            char toprint{' '};
            switch (screen.at(y).at(x)) {
                // wall
                case 1: {
                    toprint = '|';
                    // std::cout << "#";
                    break;
                }
                // block
                case 2: {
                    // std::cout << "¤";
                    toprint = '#';
                    blocks_left = true;
                    break;
                }
                // horizontal paddle
                case 3: {
                    // std::cout << "-";
                    toprint = '=';
                    break;
                }
                // Ball
                case 4: {
                    // std::cout << "o";
                    toprint = 'o';
                    break;
                }
                // Empty tile
                case 0:
                default: {
                    // std::cout << " ";
                    // toprint = ' '
                    break;
                }
            }
            if (draw) {
                std::cout << toprint;
            }
        }
        if (draw) {
            std::cout << std::endl;
        }
    }
    if (draw) {
        std::cout << "Score: " << score << std::endl;
    }
    if (!blocks_left) {
        return score;
    }
    return 0;
}

int64_t calculate_joystick_output(std::vector<int64_t> const& output) {
    std::optional<int64_t> ball{std::nullopt};
    std::optional<int64_t> paddle{std::nullopt};
    for (std::size_t i{0}; i < output.size(); i += 3) {
        int64_t const x{output.at(i)};
        int64_t const obj{output.at(i+2)};
        if (obj == 3) {
            paddle = x;
        }
        else if (obj == 4) {
            ball = x;
        }
    }
    assert(ball.has_value());
    assert(paddle.has_value());

    auto diff = ball.value() - paddle.value();

    return std::clamp(
        diff,
        static_cast<int64_t>(-1),
        static_cast<int64_t>(1)
    );
}

int64_t solve_2(std::vector<std::string> inp) {
    static_cast<void>(inp);
    assert(inp.size() == 1);

    auto program = string_utils::numbers_from_string(inp.at(0));
    program.at(0) = 2;

    // TODO: Handle the growing state to speed up, keep track of the state and
    // only update the ones that gets updated
    IntcodeComputer comp(program);
    comp.exec();
    auto const& output = comp.output_;

    int64_t score = 0;
    while (score == 0) {
        comp.exec();
        score = print(output, false);
        int64_t input{calculate_joystick_output(output)};
        comp.set_input(input);
    }

    return score;
}

void samples() {
}

};  // namespace aoc::y2019::d13

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2019::d13::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2019::d13::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2019::d13::samples, solve_1_wrapper, solve_2_wrapper, input);
}
