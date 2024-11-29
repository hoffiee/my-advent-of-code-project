#include "gtest/gtest.h"

#include AOC_HEADER

TEST(AOC_TEST, nice_string_three_vovels) {
    {
        std::string word = "aei";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "xazegov";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "aeiouaeiouaeiou";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "bev";
        ASSERT_EQ(is_nice_string(word), false);
    }
}

TEST(AOC_TEST, nice_string_invalid_combinations) {
    {
        std::string word = "abc";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "ab";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "cd";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "pq";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "xy";
        ASSERT_EQ(is_nice_string(word), false);
    }
}

TEST(AOC_TEST, nice_string_examples) {
    {
        std::string word = "ugknbfddgicrmopn";
        ASSERT_EQ(is_nice_string(word), true);
    }
    {
        std::string word = "aaa";
        ASSERT_EQ(is_nice_string(word), true);
    }

    {
        std::string word = "jchzalrnumimnmhp";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "haegwjzuvuyypxyu";
        ASSERT_EQ(is_nice_string(word), false);
    }
    {
        std::string word = "dvszwmarrgswjxmb";
        ASSERT_EQ(is_nice_string(word), false);
    }
}

TEST(AOC_TEST, solve_1_test) {
    std::vector<std::string> words{
        "ugknbfddgicrmopn", "aaa", "jchzalrnumimnmhp", "haegwjzuvuyypxyu", "dvszwmarrgswjxmb",
    };

    ASSERT_EQ(solve_1(words), 2);
}

TEST(AOC_TEST, solve_2_test) {
    std::vector<std::string> words{
        "qjhvhtzxzqqjkmpb",
        "xxyxx",
        "uurcxstgmygtbstg",
        "ieodomkazucvgmuy",
    };

    ASSERT_EQ(solve_2(words), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
