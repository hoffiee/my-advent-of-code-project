#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "R 4", "U 4", "L 3", "D 1", "R 4", "D 1", "L 5", "R 2",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 13);
    ASSERT_EQ(part2, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
