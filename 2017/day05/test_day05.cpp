#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<int> inp = {
        0, 3, 0, 1, -3,
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 5);
    ASSERT_EQ(part2, 10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
