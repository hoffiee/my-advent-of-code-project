#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {"+1", "+1", "+1"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 3);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {"+1", "+1", "-2"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_3) {
    std::vector<std::string> inp = {"-1", "-2", "-3"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, -6);
}

TEST(AOC_TEST, test_4) {
    std::vector<std::string> inp = {"+1", "-2", "+3", "+1"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 3);
}

TEST(AOC_TEST, test_5) {
    std::vector<std::string> inp = {"+1", "-1"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_6) {
    std::vector<std::string> inp = {"+3", "+3", "+4", "-2", "-4"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 10);
}

TEST(AOC_TEST, test_7) {
    std::vector<std::string> inp = {"-6", "+3", "+8", "+5", "-6"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 5);
}

TEST(AOC_TEST, test_8) {
    std::vector<std::string> inp = {"+7", "+7", "-2", "-7", "-4"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 14);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
