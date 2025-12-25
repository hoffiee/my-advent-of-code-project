#include "aoc_runner.h"

#include <iostream>

namespace {

struct State {
    bool print_usage_{false};
    bool sample_{false};
    bool solve_1_{false};
    bool solve_2_{false};

    State(int argc, char** argv) {
        if (argc <= 1) {
            sample_ = true;
            solve_1_ = true;
            solve_2_ = true;
        }

        // Ehh, could get a lib, but need something small and don't want to bring in external libraries too much, after
        // all this is for learning.
        for (int i{1}; i < argc; i++) {
            std::string arg{argv[i]};
            if (arg == "-h" || arg == "--help") {
                print_usage_ = true;
            } else if (arg == "-s" || arg == "--sample") {
                sample_ = true;
            } else if (arg == "-a" || arg == "--all") {
                sample_ = true;
                solve_1_ = true;
                solve_2_ = true;
            } else if (arg.substr(0, 2) == "-p" || arg.substr(0, 6) == "--part") {
                // Handles -p2 or --part=2
                int part{0};
                if (size_t pos = arg.find_first_of("="); pos != std::string::npos) {
                    part = std::stoi(arg.substr(pos + 1));
                }
                // check for -p 2 or --part 2
                else if ((arg == "-p" || arg == "--part")) {
                    if (i + 1 < argc) {
                        // Assumes this is a digit
                        part = std::stoi(argv[i + 1]);
                    }
                } else if (arg.size() > 2) {
                    part = std::stoi(arg.substr(2));
                }

                switch (part) {
                    case 1:
                        solve_1_ = true;
                        break;
                    case 2:
                        solve_2_ = true;
                        break;
                    default:
                        print_usage_ = true;
                        break;
                }
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, State const& state) {
        os << "print_usage(" << state.print_usage_ << "), ";
        os << "sample(" << state.sample_ << "), ";
        os << "solve_1(" << state.solve_1_ << "), ";
        os << "solve_2(" << state.solve_2_ << "), ";
        return os;
    }
};

void usage() {
    printf("Usage: ./YEAR_dayXX [OPTIONS]\n");
    printf("\n");
    printf("Options\n");
    printf("-s, --sample \trun samples.\n");
    printf("-p, --part=X \trun part X, X can be either 1 or 2.\n");
}

};  // namespace

int aoc::run(int argc, char** argv, std::function<void(void)> sample,
             std::function<void(std::vector<std::string> const&)> solve_1,
             std::function<void(std::vector<std::string> const&)> solve_2, std::vector<std::string> const& input) {
    State state(argc, argv);

    if (state.print_usage_) {
        usage();
        return 1;
    }

    if (state.sample_) {
        sample();
        std::cout << "Pre-checks done" << std::endl;
    }
    if (state.solve_1_) {
        solve_1(input);
    }
    if (state.solve_2_) {
        solve_2(input);
    }

    return 0;
}
