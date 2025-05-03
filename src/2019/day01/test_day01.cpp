#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "12",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 2);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "14",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 2);
}

TEST(AOC_TEST, test_3) {
    std::vector<std::string> inp = {
        "1969",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 654);
}

TEST(AOC_TEST, test_4) {
    std::vector<std::string> inp = {
        "100756",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 33583);
}

TEST(AOC_TEST, test_5) {
    std::vector<std::string> inp = {
        "14",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 2);
}

TEST(AOC_TEST, test_6) {
    std::vector<std::string> inp = {
        "1969",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 966);
}

TEST(AOC_TEST, test_7) {
    std::vector<std::string> inp = {
        "100756",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 50346);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
