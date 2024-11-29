#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_1) {
    std::vector<std::string> inp = {"R8,U5,L5,D3", "U7,R6,D4,L4"};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 6);
}

TEST(AOC_TEST, test_2) {
    std::vector<std::string> inp = {"R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 159);
}

TEST(AOC_TEST, test_3) {
    std::vector<std::string> inp = {"R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51",
                                    "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"};
    auto out = solve_1(inp);
    ASSERT_EQ(out, 135);
}

TEST(AOC_TEST, test_4) {
    std::vector<std::string> inp = {"R8,U5,L5,D3", "U7,R6,D4,L4"};
    auto out = solve_2(inp);
    ASSERT_EQ(out, 30);
}

TEST(AOC_TEST, test_5) {
    std::vector<std::string> inp = {"R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"};
    auto out = solve_2(inp);
    ASSERT_EQ(out, 610);
}

TEST(AOC_TEST, test_6) {
    std::vector<std::string> inp = {"R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51",
                                    "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"};
    auto out = solve_2(inp);
    ASSERT_EQ(out, 410);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
