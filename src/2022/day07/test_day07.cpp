#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "$ cd /",  "$ ls",    "dir a",  "14848514 b.txt", "8504156 c.dat", "dir d",         "$ cd a",    "$ ls",
        "dir e",   "29116 f", "2557 g", "62596 h.lst",    "$ cd e",        "$ ls",          "584 i",     "$ cd ..",
        "$ cd ..", "$ cd d",  "$ ls",   "4060174 j",      "8033020 d.log", "5626152 d.ext", "7214296 k",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 95437);
    ASSERT_EQ(part2, 24933642);
}

TEST(AOC_TEST, test_case_2) {
    std::vector<std::string> inp = {
        "$ cd /", "$ cd a", "$ cd a", "$ ls", "400 j.txt", "$ cd b", "$ ls", "400 j.txt", "$ cd ..", "$ cd a", "$ cd b",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 2800);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
