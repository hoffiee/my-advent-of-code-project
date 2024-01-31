#include "gtest/gtest.h"

#include AOC_HEADER

#if 1
static void assert_possible_paths(
        std::vector<std::vector<bool>>& paths,
        std::vector<std::tuple<size_t, size_t>> possible
        ) {

    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            if (y == 1 && x == 1) {
                continue;
            }

            bool expect_true = false;
            for (auto& [xc, yc] : possible) {
                if (x == xc && y == yc) {
                    expect_true = true;
                }
            }

            if (expect_true) {
                // possible values
                ASSERT_TRUE(paths[y][x]);
            }
            else {
                // no possible values
                ASSERT_FALSE(paths[y][x]);
            }
        }
    }
}
TEST(AOC_TEST, test_possible_paths_period) {
    std::vector<std::string> inp = {
        "...",
        "...",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {});
}

TEST(AOC_TEST, test_possible_paths_bar) {
    std::vector<std::string> inp = {
        "...",
        ".|.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 0},
        {1, 2},
    });
}

TEST(AOC_TEST, test_possible_paths_dash) {
    std::vector<std::string> inp = {
        "...",
        ".-.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {0, 1},
        {2, 1},
    });
}

TEST(AOC_TEST, test_possible_paths_L) {
    std::vector<std::string> inp = {
        "...",
        ".L.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 0},
        {2, 1},
    });
}

TEST(AOC_TEST, test_possible_paths_J) {
    std::vector<std::string> inp = {
        "...",
        ".J.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 0},
        {0, 1},
    });
}

TEST(AOC_TEST, test_possible_paths_7) {
    std::vector<std::string> inp = {
        "...",
        ".7.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 2},
        {0, 1},
    });
}

TEST(AOC_TEST, test_possible_paths_F) {
    std::vector<std::string> inp = {
        "...",
        ".F.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 2},
        {2, 1},
    });
}

TEST(AOC_TEST, test_possible_paths_S) {
    std::vector<std::string> inp = {
        "...",
        ".S.",
        "...",
    };
    auto out = internal::possible_paths(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 0},
        {0, 1},
        {2, 1},
        {1, 2},
    });
}

TEST(AOC_TEST, test_direction_period) {
    std::vector<std::string> inp = {
        "...",
        ".S.",
        "...",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {});
}

TEST(AOC_TEST, test_direction_bar) {
    std::vector<std::string> inp = {
        "|||",
        "|S|",
        "|||",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 0},
        {1, 2},
    });
}

TEST(AOC_TEST, test_direction_dash) {
    std::vector<std::string> inp = {
        "---",
        "-S-",
        "---",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {0, 1},
        {2, 1},
    });
}

TEST(AOC_TEST, test_direction_L) {
    std::vector<std::string> inp = {
        "LLL",
        "LSL",
        "LLL",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {0, 1},
        {1, 2},
    });
}

TEST(AOC_TEST, test_direction_J) {
    std::vector<std::string> inp = {
        "JJJ",
        "JSJ",
        "JJJ",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {2, 1},
        {1, 2},
    });
}

TEST(AOC_TEST, test_direction_7) {
    std::vector<std::string> inp = {
        "777",
        "7S7",
        "777",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {2, 1},
        {1, 0},
    });
}

TEST(AOC_TEST, test_direction_F) {
    std::vector<std::string> inp = {
        "FFF",
        "FSF",
        "FFF",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {0, 1},
        {1, 0},
    });
}

TEST(AOC_TEST, test_direction_S) {
    std::vector<std::string> inp = {
        "SSS",
        "SSS",
        "SSS",
    };
    auto out = internal::possible_directions(inp, 1,  1);
    assert_possible_paths(out, {
        {1, 0},
        {0, 1},
        {2, 1},
        {1, 2},
    });
}
#endif

TEST(AOC_TEST, test_part1_1) {
    std::vector<std::string> inp = {
        ".....",
        ".S-7.",
        ".|.|.",
        ".L-J.",
        ".....",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 4);
}

TEST(AOC_TEST, test_part1_2) {
    std::vector<std::string> inp = {
        "-L|F7",
        "7S-7|",
        "L|7||",
        "-L-J|",
        "L|-JF",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 4);
}

TEST(AOC_TEST, test_part1_3) {
    std::vector<std::string> inp = {
        "..F7.",
        ".FJ|.",
        "SJ.L7",
        "|F--J",
        "LJ...",
    };
    auto out = solve_1(inp);
    ASSERT_EQ(out, 8);
}

TEST(AOC_TEST, test_part2_1) {
    std::vector<std::string> inp = {
        ".....",
        ".S-7.",
        ".|.|.",
        ".L-J.",
        ".....",
    };
    auto out = solve_2(inp);
    ASSERT_EQ(out, 1);
}

// TEST(AOC_TEST, test_part2_2) {
//     std::vector<std::string> inp = {
//         "..F7.",
//         ".FJ|.",
//         "SJ.L7",
//         "|F--J",
//         "LJ...",
//     };
//     auto out = solve_2(inp);
//     ASSERT_EQ(out, 1);
// }

// TEST(AOC_TEST, test_part2_3) {
//     std::vector<std::string> inp = {
//         "...........",
//         ".S-------7.",
//         ".|F-----7|.",
//         ".||.....||.",
//         ".||.....||.",
//         ".|L-7.F-J|.",
//         ".|..|.|..|.",
//         ".L--J.L--J.",
//         "...........",
//     };
//     auto out = solve_2(inp);
//     ASSERT_EQ(out, 4);
// }

// TEST(AOC_TEST, test_part2_4) {
//     std::vector<std::string> inp = {
//         ".F----7F7F7F7F-7....",
//         ".|F--7||||||||FJ....",
//         ".||.FJ||||||||L7....",
//         "FJL7L7LJLJ||LJ.L-7..",
//         "L--J.L7...LJS7F-7L7.",
//         "....F-J..F7FJ|L7L7L7",
//         "....L7.F7||L7|.L7L7|",
//         ".....|FJLJ|FJ|F7|.LJ",
//         "....FJL-7.||.||||...",
//         "....L---J.LJ.LJLJ...",
//     };
//     auto out = solve_2(inp);
//     ASSERT_EQ(out, 10);
// }

// TEST(AOC_TEST, test_part2_5) {
//     std::vector<std::string> inp = {
//         "..........",
//         ".S------7.",
//         ".|F----7|.",
//         ".||....||.",
//         ".||....||.",
//         ".|L-7F-J|.",
//         ".|..||..|.",
//         ".L--JL--J.",
//         "..........",
//     };
//     auto out = solve_2(inp);
//     ASSERT_EQ(out, 4);
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
