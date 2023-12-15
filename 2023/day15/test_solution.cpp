#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_hash_1) {
    std::string inp = "HASH";
    auto out = internal::hash(inp);
    ASSERT_EQ(out, 52);
}

TEST(AOC_TEST, test_part1_1) {
    std::vector<std::string> inp = {"rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7"};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 1320);
}

TEST(AOC_TEST, test_part2_1) {
    std::vector<std::string> inp = {"rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7"};
    auto out = solve_2(inp);
    ASSERT_EQ(out, 145);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
