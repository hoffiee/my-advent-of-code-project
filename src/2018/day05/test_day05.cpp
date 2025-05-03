#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::string inp = "dabAcCaCBAcCcaDA";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 10);
    ASSERT_EQ(part2, 4);
}

TEST(AOC_TEST, test_case_2) {
    std::string inp = "aabAAB";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 6);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_3) {
    std::string inp = "abAB";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 4);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_4) {
    std::string inp = "abBA";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 0);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_5) {
    std::string inp = "qQ";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 0);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_6) {
    std::string inp = "qQ";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 0);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_7) {
    std::string inp = "QQ";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 2);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_9) {
    std::string inp = "qq";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 2);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_10) {
    std::string inp = "qQq";
    auto part1 = solve_1(inp);
    auto part2 = solve_2(inp);
    ASSERT_EQ(part1, 1);
    ASSERT_EQ(part2, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
