#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {"1518-11-01 00:00 Guard #10 begins shift",
                                    "1518-11-01 00:05 falls asleep",
                                    "1518-11-01 00:25 wakes up",
                                    "1518-11-01 00:30 falls asleep",
                                    "1518-11-01 00:55 wakes up",
                                    "1518-11-01 23:58 Guard #99 begins shift",
                                    "1518-11-02 00:40 falls asleep",
                                    "1518-11-02 00:50 wakes up",
                                    "1518-11-03 00:05 Guard #10 begins shift",
                                    "1518-11-03 00:24 falls asleep",
                                    "1518-11-03 00:29 wakes up",
                                    "1518-11-04 00:02 Guard #99 begins shift",
                                    "1518-11-04 00:36 falls asleep",
                                    "1518-11-04 00:46 wakes up",
                                    "1518-11-05 00:03 Guard #99 begins shift",
                                    "1518-11-05 00:45 falls asleep",
                                    "1518-11-05 00:55 wakes up"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 240);
    ASSERT_EQ(part2, 4455);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
