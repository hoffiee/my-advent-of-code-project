#include "gtest/gtest.h"

#include "aoc_utils.h"

TEST(AOC_UTILS_TEST, test_string_join) {
    std::vector<std::string> inp {};
    ASSERT_EQ(aoc::string::join(inp), "");

    inp = { "hello", };
    ASSERT_EQ(aoc::string::join(inp), "hello");

    inp = { "hello", "there", "mr", "piglett" };
    ASSERT_EQ(aoc::string::join(inp), "hellotheremrpiglett");

    inp = { "hello", "there", "mr", "piglett" };
    ASSERT_EQ(aoc::string::join(inp, ","), "hello,there,mr,piglett");

    inp = { "can", "you", "dance", };
    ASSERT_EQ(aoc::string::join(inp, "-cow-"), "can-cow-you-cow-dance");
}

TEST(AOC_UTILS_TEST, test_string_split) {
    std::string inp{};
    ASSERT_TRUE(aoc::string::split(inp) == std::vector<std::string>{});

    inp = "";
    ASSERT_TRUE(aoc::string::split(inp) == std::vector<std::string>{});

    inp = "hellohello";
    ASSERT_TRUE(aoc::string::split(inp) == std::vector<std::string>{"hellohello"});

    inp = "hello,hello";
    std::vector<std::string> expected{
        "hello",
        "hello"
    };
    ASSERT_TRUE(aoc::string::split(inp) == expected);

    inp = "hello,hello";
    expected = {
        "hello,hello"
    };
    ASSERT_TRUE(aoc::string::split(inp, '=') == expected);

    inp = "hello=hello";
    expected = {
        "hello",
        "hello"
    };
    ASSERT_TRUE(aoc::string::split(inp, '=') == expected);

    inp = "hello there captain Bowmount, how, do, you, drink your juice?";
    expected = {
        "hello there captain Bowmount",
        " how",
        " do",
        " you",
        " drink your juice?"
    };
    ASSERT_TRUE(aoc::string::split(inp, ',') == expected);
}

TEST(AOC_UTILS_TEST, test_math_mod) {
    ASSERT_EQ(aoc::math::mod(-7, 10), 3);
    ASSERT_EQ(aoc::math::mod(7, -10), 7);
    ASSERT_EQ(aoc::math::mod(-7, -10), 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
