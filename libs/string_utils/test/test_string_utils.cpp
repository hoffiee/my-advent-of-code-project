#include "gtest/gtest.h"
#include "string_utils.h"

TEST(STRING_UTILS_TEST, test_int_from_strings_no_numbers) {
    std::string inp = {"abc"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_TRUE(out.empty());
}

TEST(STRING_UTILS_TEST, test_int_from_strings_one_digit_beginning) {
    std::string inp = {"1abc"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 1);
    ASSERT_EQ(out.at(0), 1);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_one_digit_middle) {
    std::string inp = {"a1c"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 1);
    ASSERT_EQ(out.at(0), 1);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_one_digit_end) {
    std::string inp = {"abc1"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 1);
    ASSERT_EQ(out.at(0), 1);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_three_digits_beginning) {
    std::string inp = {"123abc"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 1);
    ASSERT_EQ(out.at(0), 123);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_two_digits_middle) {
    std::string inp = {"a12c"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 1);
    ASSERT_EQ(out.at(0), 12);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_four_digits_end) {
    std::string inp = {"abc1234"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 1);
    ASSERT_EQ(out.at(0), 1234);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_two_numbers_start_middle) {
    std::string inp = {"12a bcs34sda"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 2);
    ASSERT_EQ(out.at(0), 12);
    ASSERT_EQ(out.at(1), 34);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_two_numbers_middle_end) {
    std::string inp = {"a bcs34sda678"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 2);
    ASSERT_EQ(out.at(0), 34);
    ASSERT_EQ(out.at(1), 678);
}

TEST(STRING_UTILS_TEST, test_int_from_strings_three_numbers_ignore_period) {
    std::string inp = {"a bcs34sda6.8"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 3);
    ASSERT_EQ(out.at(0), 34);
    ASSERT_EQ(out.at(1), 6);
    ASSERT_EQ(out.at(2), 8);
}

TEST(STRING_UTILS_TEST, test_example_from_puzzle_1) {
    std::string inp = {"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 7);
    ASSERT_EQ(out.at(0), 1);
    ASSERT_EQ(out.at(1), 3);
    ASSERT_EQ(out.at(2), 4);
    ASSERT_EQ(out.at(3), 1);
    ASSERT_EQ(out.at(4), 2);
    ASSERT_EQ(out.at(5), 6);
    ASSERT_EQ(out.at(6), 2);
}

TEST(STRING_UTILS_TEST, test_example_from_puzzle_2) {
    std::string inp = {"Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 14);
    ASSERT_EQ(out.at(0), 2);
    ASSERT_EQ(out.at(1), 13);
    ASSERT_EQ(out.at(2), 32);
    ASSERT_EQ(out.at(3), 20);
    ASSERT_EQ(out.at(4), 16);
    ASSERT_EQ(out.at(5), 61);
    ASSERT_EQ(out.at(6), 61);
    ASSERT_EQ(out.at(7), 30);
    ASSERT_EQ(out.at(8), 68);
    ASSERT_EQ(out.at(9), 82);
    ASSERT_EQ(out.at(10), 17);
    ASSERT_EQ(out.at(11), 32);
    ASSERT_EQ(out.at(12), 24);
    ASSERT_EQ(out.at(13), 19);
}

TEST(STRING_UTILS_TEST, test_example_from_2024_day14) {
    std::string inp = {"p=2,4 v=2,-3"};
    auto out = string_utils::numbers_from_string(inp);
    ASSERT_EQ(out.size(), 4);
    ASSERT_EQ(out.at(0), 2);
    ASSERT_EQ(out.at(1), 4);
    ASSERT_EQ(out.at(2), 2);
    ASSERT_EQ(out.at(3), -3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
