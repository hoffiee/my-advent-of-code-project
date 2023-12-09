#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {
        "32T3K 765",  // One pair
        "T55J5 684",  // three of a kind
        "KK677 28",   // two pair
        "KTJJT 220",  // two pair
        "QQQJA 483",  // Three of a kind
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 6440);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {
        "32T3K 765",  // One pair
        "T55J5 684",  // three of a kind
        "KK677 28",   // two pair
        "AAAAA 2",    // Added: Five of a kind
        "KTJJT 220",  // two pair
        "QQQJA 483",  // Three of a kind
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 6440 + 6 * 2);
}

TEST(AOC_TEST, test_3) {
    std::vector<std::string> inp = {
        "32T3K 765",  // One pair
        "T55J5 684",  // three of a kind
        "KK677 28",   // two pair
        "AAAAA 2",    // Added: Five of a kind
        "99999 4",    // Added: Five of a kind lower
        "KTJJT 220",  // two pair
        "QQQJA 483",  // Three of a kind
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 6440 + 6 * 4 + 7 * 2);
}

TEST(AOC_TEST, test_4) {
    std::vector<std::string> inp = {
        "32T3K 765",  // One pair
        "T55J5 684",  // three of a kind
        "KK677 28",   // two pair
        "AAAAA 2",    // Added: Five of a kind
        "KKKKK 4",    // Added: Five of a kind lower
        "KTJJT 220",  // two pair
        "QQQJA 483",  // Three of a kind
        "23332 8",    // Full house
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 6440 + 6 * 8 + 7 * 4 + 8 * 2);
}

TEST(AOC_TEST, test_5) {
    std::vector<std::string> inp = {
        "23456 100",  // High card
        "23457 400",  // High card
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 400 * 2 + 100 * 1);
}

TEST(AOC_TEST, test_6) {
    std::vector<std::string> inp = {
        "2A34A 100",  // One pair
        "24345 400",  // One pair
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 400 * 1 + 100 * 2);
}

TEST(AOC_TEST, test_7) {
    std::vector<std::string> inp = {
        "55224 100",  // two pair
        "55KK3 400",  // two pair
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 400 * 2 + 100 * 1);
}

TEST(AOC_TEST, test_8) {
    std::vector<std::string> inp = {
        "22342 100",  // three of a kind
        "AAAKJ 400",  // three of a kind
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 400 * 2 + 100 * 1);
}

TEST(AOC_TEST, test_9) {
    std::vector<std::string> inp = {
        "AAKKK 100",  // three of a kind
        "TTJJJ 400",  // three of a kind
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 400 * 1 + 100 * 2);
}

TEST(AOC_TEST, test_11) {
    std::vector<std::string> inp = {
        "QTTTT 100",  // four of a kind
        "TTTTQ 400",  // four of a kind
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 400 * 1 + 100 * 2);
}

TEST(AOC_TEST, test_12) {
    std::vector<std::string> inp = {
        "32T3K 765",  // One pair
        "T55J5 684",  // three of a kind
        "KK677 28",   // two pair
        "KTJJT 220",  // two pair
        "QQQJA 483",  // Three of a kind
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 5905);
}

TEST(AOC_TEST, test_13) {
    std::vector<std::string> inp = {
        "QJJQ2 1",   // four
        "QQQQ2 10",  // four
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1 + 2 * 10);
}

TEST(AOC_TEST, test_14) {
    std::vector<std::string> inp = {
        "KJJK2 1",   // four
        "QQQQ2 10",  // four
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 2 * 1 + 1 * 10);
}

TEST(AOC_TEST, test_15) {
    std::vector<std::string> inp = {
        "2KJJK 1",   // four
        "QQQQ2 10",  // four
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1 * 1 + 2 * 10);
}

TEST(AOC_TEST, test_16) {
    std::vector<std::string> inp = {
        "2KJJQ 1",  // three
        "QQQK2 10",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1 * 1 + 2 * 10);
}

// full house
TEST(AOC_TEST, test_17) {
    std::vector<std::string> inp = {
        "KJQQK 1",
        "KQQQK 10",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1 * 1 + 2 * 10);
}

// full house
TEST(AOC_TEST, test_18) {
    std::vector<std::string> inp = {
        "JKQQK 1",
        "KQQQK 10",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1 * 1 + 2 * 10);
}

// two pair
TEST(AOC_TEST, test_19) {
    std::vector<std::string> inp = {
        "QQ344 1",
        "Q45QJ 10",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1 * 1 + 2 * 10);
}

TEST(AOC_TEST, test_20) {
    std::vector<std::string> inp = {
        "JQ344 1",
        "345QJ 10",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 2 * 1 + 1 * 10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
