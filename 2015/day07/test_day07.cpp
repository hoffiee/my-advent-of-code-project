#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, test_d) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "d", "");
    ASSERT_EQ(out1, 72);
}

TEST(AOC_TEST, test_e) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "e", "");
    ASSERT_EQ(out1, 507);
}

TEST(AOC_TEST, test_f) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "f", "");
    ASSERT_EQ(out1, 492);
}

TEST(AOC_TEST, test_g) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "g", "");
    ASSERT_EQ(out1, 114);
}

TEST(AOC_TEST, test_h) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "h", "");
    ASSERT_EQ(out1, 65412);
}

TEST(AOC_TEST, test_i) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "i", "");
    ASSERT_EQ(out1, 65079);
}

TEST(AOC_TEST, test_x) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "x", "");
    ASSERT_EQ(out1, 123);
}

TEST(AOC_TEST, test_y) {
    std::vector<std::string> inp = {
        "123 -> x",        "456 -> y",        "x AND y -> d", "x OR y -> e",
        "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h",   "NOT y -> i",
    };
    auto [out1, ign] = solve(inp, "y", "");
    ASSERT_EQ(out1, 456);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
