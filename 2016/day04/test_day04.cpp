#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {
        "aaaaa-bbb-z-y-x-123[abxyz]",
        "a-b-c-d-e-f-g-h-987[abcde]",
        "not-a-real-room-404[oarel]",
        "totally-real-room-200[decoy]",
    };
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 1514);
}

TEST(AOC_TEST, test_case_2) {
    std::string inp = "qzmt-zixmtkozy-ivhz";
    int sector_id = 343;

    shift_cipher(inp, sector_id);

    ASSERT_EQ(inp, "very encrypted name");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
