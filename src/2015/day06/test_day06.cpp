#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, turn_on_all_lights) {
    std::vector<std::string> inp = {
        // preprocess.awk turns the following into
        // "turn on 0,0 through 999,999"
        "p 0 0 999 999",
    };
    auto [lights, brightness] = solve(inp);
    ASSERT_EQ(lights, 1e6);
}

TEST(AOC_TEST, toggle_0_0_to_999_0) {
    std::vector<std::string> inp = {
        // preprocess.awk turns the following into
        // "toggle 0,0 through 999,0"
        "t 0 0 999 0",
    };
    auto [lights, brightness] = solve(inp);
    ASSERT_EQ(lights, 1000);
}

TEST(AOC_TEST, turn_off_499_499_to_500_500) {
    std::vector<std::string> inp = {
        // preprocess.awk turns the following into
        // "turn off 499,499 through 500,500"
        "n 499 499 500 500",
    };
    auto [lights, brightness] = solve(inp);
    ASSERT_EQ(lights, 0);
}

TEST(AOC_TEST, brightness_control_turn_on_0_0_to_0_0) {
    std::vector<std::string> inp = {
        // preprocess.awk turns the following into
        // "turn on 0,0 through 0,0"
        "p 0 0 0 0",
    };
    auto [lights, brightness] = solve(inp);
    ASSERT_EQ(brightness, 1);
}

TEST(AOC_TEST, brightness_control_toggle_0_0_to_999_999) {
    std::vector<std::string> inp = {
        // preprocess.awk turns the following into
        // "toggle 0,0 through 999,999"
        "t 0 0 999 999",
    };
    auto [lights, brightness] = solve(inp);
    ASSERT_EQ(brightness, 2000000);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
