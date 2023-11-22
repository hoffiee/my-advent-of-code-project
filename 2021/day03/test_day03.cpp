#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "00100", "11110", "10110", "10111", "10101", "01111", "00111", "11100", "10000", "11001", "00010", "01010",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 198);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "00100", "11110", "10110", "10111", "10101", "01111", "00111", "11100", "10000", "11001", "00010", "01010",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 230);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
