#include "gtest/gtest.h"

#include AOC_HEADER

// TEST(AOC_TEST, test_part1_1) {
//     std::vector<std::string> inp = {
//         "2413432311323",
//         "3215453535623",
//         "3255245654254",
//         "3446585845452",
//         "4546657867536",
//         "1438598798454",
//         "4457876987766",
//         "3637877979653",
//         "4654967986887",
//         "4564679986453",
//         "1224686865563",
//         "2546548887735",
//         "4322674655533",
//     };
//     auto out = solve_1(inp);
//     ASSERT_EQ(out, 102);
// }

TEST(AOC_TEST, test_part1_2) {
    std::vector<std::string> inp = {
        "112999",
        "911111",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 7);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
