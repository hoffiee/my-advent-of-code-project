#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "467..114..", "...*......", "..35..633.", "......#...", "617*......",
        ".....+.58.", "..592.....", "......755.", "...$.*....", ".664.598..",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 4361);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "467..114..", "...*......", "..35..633.", "......#...", "617*......",
        ".....+.58.", "..592.....", "......755.", "...$.*....", ".664.598..",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 467835);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
