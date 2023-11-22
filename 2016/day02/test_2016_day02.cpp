#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "ULL",
        "RRDDD",
        "LURDL",
        "UUUUD",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, "1985");
    ASSERT_EQ(part2, "5DB3");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
