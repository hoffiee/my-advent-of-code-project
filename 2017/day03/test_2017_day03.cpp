#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    auto [part1, part2] = solve(1);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_2) {
    auto [part1, part2] = solve(12);
    ASSERT_EQ(part1, 3);
}

TEST(AOC_TEST, test_case_3) {
    auto [part1, part2] = solve(23);
    ASSERT_EQ(part1, 2);
}

TEST(AOC_TEST, test_case_4) {
    auto [part1, part2] = solve(1024);
    ASSERT_EQ(part1, 31);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
