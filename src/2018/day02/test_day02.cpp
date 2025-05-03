#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "abcdef", "bababc", "abbcde", "abcccd", "aabcdd", "abcdee", "ababab",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 12);
}

TEST(AOC_TEST, test_case_2) {
    std::vector<std::string> inp = {
        "abcdef",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_3) {
    std::vector<std::string> inp = {
        "bababc",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 1);
}

TEST(AOC_TEST, test_case_4) {
    std::vector<std::string> inp = {
        "abbcde",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_5) {
    std::vector<std::string> inp = {
        "abcccd",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_6) {
    std::vector<std::string> inp = {
        "aabcdd",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_7) {
    std::vector<std::string> inp = {
        "abcdee",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_8) {
    std::vector<std::string> inp = {
        "ababab",
    };
    auto part1 = solve_1(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_9) {
    std::vector<std::string> inp = {
        "abcde", "fghij", "klmno", "pqrst", "fguij", "axcye", "wvxyz",
    };
    auto part2 = solve_2(inp);
    ASSERT_EQ(part2, "fgij");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
