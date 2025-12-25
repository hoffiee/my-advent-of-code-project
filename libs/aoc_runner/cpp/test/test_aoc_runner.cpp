#include "aoc_runner.h"
#include "gtest/gtest.h"

TEST(RUNNER_TEST, test_runner_no_args) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_TRUE(sample_executed);
    ASSERT_TRUE(solve_1_executed);
    ASSERT_TRUE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_sample_shortflag) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-s"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_TRUE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_sample) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "--sample"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_TRUE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_shortflag_no_number) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-p"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 1);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_no_number) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "--part"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 1);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_wrong_number) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "--part=3"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 1);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_1_shortname_no_space) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-p1"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_FALSE(sample_executed);
    ASSERT_TRUE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_1_shortname_space) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-p 1"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_FALSE(sample_executed);
    ASSERT_TRUE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_1) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "--part=1"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_FALSE(sample_executed);
    ASSERT_TRUE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_2_shortname_no_space) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-p2"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_TRUE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_2_shortname_space) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-p 2"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_TRUE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_part_2) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "--part=2"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 0);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_TRUE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_help_shortname) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "-h"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 1);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

TEST(RUNNER_TEST, test_runner_args_help) {
    bool sample_executed{false};
    bool solve_1_executed{false};
    bool solve_2_executed{false};

    auto sample = [&sample_executed](void) -> void { sample_executed = true; };
    auto solve_1 = [&solve_1_executed](std::vector<std::string> const& inp) -> void { solve_1_executed = true; };
    auto solve_2 = [&solve_2_executed](std::vector<std::string> const& inp) -> void { solve_2_executed = true; };

    std::vector<std::string> args{"./example", "--help"};
    std::vector<char*> argv(args.size());
    for (size_t i{0}; i < args.size(); i++) {
        argv[i] = &args[i][0];
    }

    ASSERT_EQ(aoc::run(argv.size(), argv.data(), sample, solve_1, solve_2, {}), 1);

    ASSERT_FALSE(sample_executed);
    ASSERT_FALSE(solve_1_executed);
    ASSERT_FALSE(solve_2_executed);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
