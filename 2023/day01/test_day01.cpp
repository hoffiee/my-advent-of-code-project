#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "1abc2",
        "pqr3stu8vwx",
        "a1b2c3d4e5f",
        "treb7uchet",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 142);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "two1nine",         "eightwothree", "abcone2threexyz", "xtwone3four",
        "4nineeightseven2", "zoneight234",  "7pqrstsixteen",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 281);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
