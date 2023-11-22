#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "30373", "25512", "65332", "33549", "35390",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 21);
    ASSERT_EQ(part2, 8);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
