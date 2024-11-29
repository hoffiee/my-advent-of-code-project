#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_part1_1) {
    std::vector<std::string> inp = {
        "19, 13, 30 @ -2,  1, -2",
        "18, 19, 22 @ -1, -1, -2",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 1);
}

TEST(AOC_TEST, test_part1_2) {
    std::vector<std::string> inp = {
        "19, 13, 30 @ -2,  1, -2",
        "20, 25, 34 @ -2, -2, -4",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 1);
}

TEST(AOC_TEST, test_part1_3) {
    std::vector<std::string> inp = {
        "19, 13, 30 @ -2,  1, -2",
        "12, 31, 28 @ -1, -2, -1",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_4) {
    std::vector<std::string> inp = {
        "19, 13, 30 @ -2,  1, -2",
        "20, 19, 15 @  1, -5, -3",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_5) {
    std::vector<std::string> inp = {
        "18, 19, 22 @ -1, -1, -2",
        "20, 25, 34 @ -2, -2, -4",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_6) {
    std::vector<std::string> inp = {
        "18, 19, 22 @ -1, -1, -2",
        "12, 31, 28 @ -1, -2, -1",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_7) {
    std::vector<std::string> inp = {
        "18, 19, 22 @ -1, -1, -2",
        "20, 19, 15 @  1, -5, -3",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_8) {
    std::vector<std::string> inp = {
        "20, 25, 34 @ -2, -2, -4",
        "12, 31, 28 @ -1, -2, -1",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_9) {
    std::vector<std::string> inp = {
        "20, 25, 34 @ -2, -2, -4",
        "20, 19, 15 @  1, -5, -3",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_10) {
    std::vector<std::string> inp = {
        "12, 31, 28 @ -1, -2, -1",
        "20, 19, 15 @  1, -5, -3",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_part1_11) {
    std::vector<std::string> inp = {
        "19, 13, 30 @ -2,  1, -2", "18, 19, 22 @ -1, -1, -2", "20, 25, 34 @ -2, -2, -4",
        "12, 31, 28 @ -1, -2, -1", "20, 19, 15 @  1, -5, -3",
    };
    auto out = solve_1(inp, 7, 27);
    ASSERT_EQ(out, 2);
}

// possible edge case: parallel lines but opposite directions, collides in one point?

TEST(AOC_TEST, test_part2_1) {
    std::vector<std::string> inp = {
        "19, 13, 30 @ -2,  1, -2", "18, 19, 22 @ -1, -1, -2", "20, 25, 34 @ -2, -2, -4",
        "12, 31, 28 @ -1, -2, -1", "20, 19, 15 @  1, -5, -3",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 47);
}

#if 0
#endif

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
