#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "Time:      7  15   30",
        "Distance:  9  40  200",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 288);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "Time:      7  15   30",
        "Distance:  9  40  200",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 71503);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
