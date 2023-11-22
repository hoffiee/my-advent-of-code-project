#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::string inp = "111111";
    auto out = criteria_length(inp);
    ASSERT_TRUE(out);
}

TEST(AOC_TEST, test_2) {
    std::string inp = "11111";
    auto out = criteria_length(inp);
    ASSERT_FALSE(out);
}

TEST(AOC_TEST, test_3) {
    std::string inp = "122345";
    auto out = criteria_adjacent_digits(inp);
    ASSERT_TRUE(out);
}

TEST(AOC_TEST, test_4) {
    std::string inp = "123456";
    auto out = criteria_adjacent_digits(inp);
    ASSERT_FALSE(out);
}

TEST(AOC_TEST, test_5) {
    std::string inp = "123455";
    auto out = criteria_adjacent_digits(inp);
    ASSERT_TRUE(out);
}

TEST(AOC_TEST, test_6) {
    std::string inp = "111111";
    auto out = criteria_monotonic_sequence(inp);
    ASSERT_TRUE(out);
}

TEST(AOC_TEST, test_7) {
    std::string inp = "123456";
    auto out = criteria_monotonic_sequence(inp);
    ASSERT_TRUE(out);
}

TEST(AOC_TEST, test_8) {
    std::string inp = "123454";
    auto out = criteria_monotonic_sequence(inp);
    ASSERT_FALSE(out);
}

TEST(AOC_TEST, test_9) {
    auto out = solve_1(111111, 111111);
    ASSERT_EQ(out, 1);
}

TEST(AOC_TEST, test_10) {
    auto out = solve_1(223450, 223450);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_11) {
    auto out = solve_1(123789, 123789);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_12) {
    auto out = solve_2(112233, 112233);
    ASSERT_EQ(out, 1);
}

TEST(AOC_TEST, test_14) {
    auto out = solve_2(111234, 111234);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_15) {
    auto out = solve_2(123444, 123444);
    ASSERT_EQ(out, 0);
}

TEST(AOC_TEST, test_16) {
    auto out = solve_2(111122, 111122);
    ASSERT_EQ(out, 1);
}

TEST(AOC_TEST, test_17) {
    auto out = solve_2(123455, 123455);
    ASSERT_EQ(out, 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
