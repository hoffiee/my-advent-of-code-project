#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_part1_1) {
    std::vector<std::string> inp = {
        "...#......", ".......#..", "#.........", "..........", "......#...",
        ".#........", ".........#", "..........", ".......#..", "#...#.....",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 374);
}

TEST(AOC_TEST, test_part2_1) {
    std::vector<std::string> inp = {
        "...#......", ".......#..", "#.........", "..........", "......#...",
        ".#........", ".........#", "..........", ".......#..", "#...#.....",
    };
    auto out = internal::solve_factor(inp, 10);
    ASSERT_EQ(out, 1030);
}

TEST(AOC_TEST, test_part2_2) {
    std::vector<std::string> inp = {
        "...#......", ".......#..", "#.........", "..........", "......#...",
        ".#........", ".........#", "..........", ".......#..", "#...#.....",
    };
    auto out = internal::solve_factor(inp, 100);
    ASSERT_EQ(out, 8410);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
