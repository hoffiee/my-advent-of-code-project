#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    auto [x, y, dist, dist_to_hq] = solve("R2, L3");
    ASSERT_EQ(x, 2);
    ASSERT_EQ(y, 3);
    ASSERT_EQ(dist, 5);
}

TEST(AOC_TEST, test_case_2) {
    auto [x, y, dist, dist_to_hq] = solve("R2, R2, R2");
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, -2);
    ASSERT_EQ(dist, 2);
}

TEST(AOC_TEST, test_case_3) {
    auto [x, y, dist, dist_to_hq] = solve("R5, L5, R5, R3");
    ASSERT_EQ(x, 10);
    ASSERT_EQ(y, 2);
    ASSERT_EQ(dist, 12);
}

TEST(AOC_TEST, test_case_4) {
    auto [x, y, dist, dist_to_hq] = solve("R50");
    ASSERT_EQ(x, 50);
    ASSERT_EQ(y, 0);
    ASSERT_EQ(dist, 50);
}

TEST(AOC_TEST, test_case_5) {
    auto [x, y, dist, dist_to_hq] = solve("L50");
    ASSERT_EQ(x, -50);
    ASSERT_EQ(y, 0);
    ASSERT_EQ(dist, 50);
}

TEST(AOC_TEST, test_case_6) {
    auto [x, y, dist, dist_to_hq] = solve("R8, R4, R4, R8");
    ASSERT_EQ(x, 4);
    ASSERT_EQ(y, 4);
    ASSERT_EQ(dist, 8);
    ASSERT_EQ(dist_to_hq, 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
