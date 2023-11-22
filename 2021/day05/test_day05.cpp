#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "COM)B",
        "B)C",
        "B)G",
        "G)H",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 8);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "COM)B", "B)C", "C)D", "D)E", "E)F", "B)G", "G)H", "D)I", "E)J", "J)K", "K)L",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 42);
}

TEST(AOC_TEST, test_3) {
    std::vector<std::string> inp = {
        "B)C",
        "B)G",
        "COM)B",
        "G)H",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 8);
}

TEST(AOC_TEST, test_4) {
    std::vector<std::string> inp = {
        "B)C", "C)D", "D)E", "E)F", "B)G", "COM)B", "G)H", "D)I", "E)J", "J)K", "K)L",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 42);
}

TEST(AOC_TEST, test_5) {
    std::vector<std::string> inp = {
        "B)C", "C)D", "D)E", "E)F", "B)G", "COM)B", "G)H", "D)I", "I)SAN", "E)J", "J)K", "K)L", "K)YOU",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
