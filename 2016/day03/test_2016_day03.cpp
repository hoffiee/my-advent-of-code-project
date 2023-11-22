#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_case_1) {
    std::vector<std::string> inp = {"5 10 25"};
    auto [part1, part2] = solve(inp);
    ASSERT_EQ(part1, 0);
}

TEST(AOC_TEST, test_case_2) {
    std::vector<std::string> inp = {"5 10 25"};
    auto out = parse_data(inp);
    ASSERT_EQ(out.at(0).at(0), 5);
    ASSERT_EQ(out.at(0).at(1), 10);
    ASSERT_EQ(out.at(0).at(2), 25);
}

TEST(AOC_TEST, test_case_3) {
    std::vector<std::string> inp = {
        "101 301 501", "102 302 502", "103 303 503", "201 401 601", "202 402 602", "203 403 603",
    };
    auto parsed_triangles = parse_data(inp);
    auto out = transpose_triangles(parsed_triangles);
    ASSERT_EQ(out.at(0).at(0), 101);
    ASSERT_EQ(out.at(0).at(1), 102);
    ASSERT_EQ(out.at(0).at(2), 103);

    ASSERT_EQ(out.at(2).at(0), 301);
    ASSERT_EQ(out.at(2).at(1), 302);
    ASSERT_EQ(out.at(2).at(2), 303);

    ASSERT_EQ(out.at(5).at(0), 601);
    ASSERT_EQ(out.at(5).at(1), 602);
    ASSERT_EQ(out.at(5).at(2), 603);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
