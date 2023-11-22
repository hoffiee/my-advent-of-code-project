#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "#1 @ 1,3: 4x4",
        "#2 @ 3,1: 4x4",
        "#3 @ 5,5: 2x2",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 4);
    ASSERT_EQ(part2, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
