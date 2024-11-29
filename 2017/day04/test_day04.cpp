#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "aa bb cc dd ee",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 1);
}

TEST(AOC_TEST, test_case_2) {
    std::vector<std::string> inp = {
        "aa bb cc dd aa",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_3) {
    std::vector<std::string> inp = {
        "aa bb cc dd aaa",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 1);
}

TEST(AOC_TEST, test_case_4) {
    std::vector<std::string> inp = {
        "aa bb cc dd ee",
        "aa bb cc dd aa",
        "aa bb cc dd aaa",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 2);
}

TEST(AOC_TEST, test_case_5) {
    std::vector<std::string> inp = {
        "abcde fghij",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 1);
}

TEST(AOC_TEST, test_case_6) {
    std::vector<std::string> inp = {
        "abcde xyz ecdab",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_7) {
    std::vector<std::string> inp = {
        "a ab abc abd abf abj",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 1);
}

TEST(AOC_TEST, test_case_8) {
    std::vector<std::string> inp = {
        "iiii oiii ooii oooi oooo",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 1);
}

TEST(AOC_TEST, test_case_9) {
    std::vector<std::string> inp = {
        "oiii ioii iioi iiio",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_10) {
    std::vector<std::string> inp = {
        "abcde fghij", "abcde xyz ecdab", "a ab abc abd abf abj", "iiii oiii ooii oooi oooo", "oiii ioii iioi iiio",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part2, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
