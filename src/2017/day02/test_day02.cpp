#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "5 1 9 5",
        "7 5 3",
        "2 4 6 8",
    };

    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 18);
}

TEST(AOC_TEST, test_case_2) {
    std::vector<std::string> inp = {
        "5 9 2 8",
        "9 4 7 3",
        "3 8 6 5",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 9);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
