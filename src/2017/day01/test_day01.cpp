#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    auto [part1, part2] = solve("1122");
    ASSERT_EQ(part1, 3);
    // ASSERT_EQ(part2, 6);
}

TEST(AOC_TEST, test_case_2) {
    auto [part1, part2] = solve("1111");
    ASSERT_EQ(part1, 4);
}

TEST(AOC_TEST, test_case_3) {
    auto [part1, part2] = solve("1234");
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_4) {
    auto [part1, part2] = solve("91212129");
    ASSERT_EQ(part1, 9);
}

TEST(AOC_TEST, test_case_5) {
    auto [part1, part2] = solve("1212");
    ASSERT_EQ(part2, 6);
}

TEST(AOC_TEST, test_case_6) {
    auto [part1, part2] = solve("1221");
    ASSERT_EQ(part2, 0);
}

TEST(AOC_TEST, test_case_7) {
    auto [part1, part2] = solve("123425");
    ASSERT_EQ(part2, 4);
}

TEST(AOC_TEST, test_case_8) {
    auto [part1, part2] = solve("123123");
    ASSERT_EQ(part2, 12);
}

TEST(AOC_TEST, test_case_9) {
    auto [part1, part2] = solve("12131415");
    ASSERT_EQ(part2, 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
