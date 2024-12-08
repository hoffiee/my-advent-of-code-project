#include AOC_HEADER
#include "gtest/gtest.h"

TEST(AOC_TEST, test_case_1) { ASSERT_EQ(solve(">", false), 2); }

TEST(AOC_TEST, test_case_2) { ASSERT_EQ(solve("^>v<", false), 4); }

TEST(AOC_TEST, test_case_3) { ASSERT_EQ(solve("^v^v^v^v^v", false), 2); }

TEST(AOC_TEST, test_case_4) { ASSERT_EQ(solve("^v", true), 3); }

TEST(AOC_TEST, test_case_5) { ASSERT_EQ(solve("^>v<", true), 3); }

TEST(AOC_TEST, test_case_6) { ASSERT_EQ(solve("^v^v^v^v^v", true), 11); }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
