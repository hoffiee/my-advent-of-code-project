#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_part1_1) {
    std::vector<std::string> inp = {
        "#.##..##.",
        "..#.##.#.",
        "##......#",
        "##......#",
        "..#.##.#.",
        "..##..##.",
        "#.#.##.#.",
        "",
        "#...##..#",
        "#....#..#",
        "..##..###",
        "#####.##.",
        "#####.##.",
        "..##..###",
        "#....#..#",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 405);
}

// vertical match by the right edge
TEST(AOC_TEST, test_part1_2) {
    std::vector<std::string> inp = {
        "##....#.##.##",
        "#.....#...#..",
        "#.....##..#..",
        "##....#.##.##",
        "#.....#......",
        "#.#.....#.###",
        ".#.#######.##"
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 12);
}

TEST(AOC_TEST, test_part2_1) {
    std::vector<std::string> inp = {
        "#.##..##.",
        "..#.##.#.",
        "##......#",
        "##......#",
        "..#.##.#.",
        "..##..##.",
        "#.#.##.#.",
        "",
        "#...##..#",
        "#....#..#",
        "..##..###",
        "#####.##.",
        "#####.##.",
        "..##..###",
        "#....#..#",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 400);
}

TEST(AOC_TEST, test_part2_2) {
    std::vector<std::string> inp = {
        ".##..##..##....##",
        ".###....###.##.##",
        "###.#..#.###..###",
        "#...#..#...####..",
        "#.#.#..#.#.####.#",
        "###..##..########",
        "#..#....#..#..#..",
        "..#.####.#..###.#",
        "..########......#",
        "#..##..##..#..#..",
        "#..######..#..#..",
        "####....####..###",
        ".#.##..##.#....#."
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 13); // I think this is the case
}

TEST(AOC_TEST, test_part2_3) {
    std::vector<std::string> inp = {
        "..#...####.",
        "#.#..#.....",
        "##....####.",
        "#..###....#",
        "##.###....#",
        "..#.#......",
        "..#.#......"
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 13); // I think this is the case
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
