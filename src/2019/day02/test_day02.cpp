#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<int64_t> inp = {1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 3500);
}

TEST(AOC_TEST, test_2) {
    std::vector<int64_t> inp = {1, 0, 0, 0, 99};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 2);
}

TEST(AOC_TEST, test_3) {
    std::vector<int64_t> inp = {2, 3, 0, 3, 99};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 2);
}

TEST(AOC_TEST, test_4) {
    std::vector<int64_t> inp = {2, 4, 4, 5, 99, 0};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 2);
}

TEST(AOC_TEST, test_5) {
    std::vector<int64_t> inp = {1, 1, 1, 4, 99, 5, 6, 0, 99};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 30);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
