/**
 * https://adventofcode.com/2023/day/19
 *
 * aoc_tags: 
 *
 * TODO: ok, maybe a random approach isn't the way to go...
 */
#include <cassert>
#include <icecream.hpp>
#include <string>
#include <vector>
#include <random>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d19 {

struct Part {
    int64_t x{};
    int64_t m{};
    int64_t a{};
    int64_t s{};

    Part(int64_t x, int64_t m, int64_t a, int64_t s): x{x}, m{m}, a{a}, s{s} {}

    Part(std::string const& line) {
        // check that xmas are always coming in the same order
        auto it_x = std::find(line.cbegin(), line.cend(), 'x');
        auto it_m = std::find(line.cbegin(), line.cend(), 'm');
        auto it_a = std::find(line.cbegin(), line.cend(), 'a');
        auto it_s = std::find(line.cbegin(), line.cend(), 's');
        assert(it_x < it_m);
        assert(it_m < it_a);
        assert(it_a < it_s);
        auto numbers = aoc::string::numbers_from_string(line);
        x = numbers.at(0);
        m = numbers.at(1);
        a = numbers.at(2);
        s = numbers.at(3);
    }

    friend std::ostream& operator<<(std::ostream& os, Part const& p) {
        os << "{x:" << p.x << ",m:" << p.m << ",a:" << p.a << ",s:" << p.s << "}";
        return os;
    }
};

struct Rule {
    std::string target_{};
    bool always_true_{false};
    int64_t Part::* field_;
    int64_t value_{0};
    std::function<bool(int64_t, int64_t)> cmp_;

    Rule(std::string const& line) {
        auto rule_str = aoc::string::split(line, ':');
        if (rule_str.size() == 1) {
            target_ = rule_str.front();
            always_true_ = true;
            return;
        }
        assert(rule_str.size() == 2u);
        assert(line.at(0) == 'x' || line.at(0) == 'm' || line.at(0) == 'a' || line.at(0) == 's');

        switch (line.at(0)) {
            case 'x': {
                field_ = &Part::x;
                break;
            }
            case 'm': {
                field_ = &Part::m;
                break;
            }
            case 'a': {
                field_ = &Part::a;
                break;
            }
            case 's': {
                field_ = &Part::s;
                break;
            }
            default: {
                assert(false);
                break;
            }
        }

        // Check <=, >= etc
        switch (line.at(1)) {
            case '<': {
                cmp_ = [](int64_t lhs, int64_t rhs) -> bool{
                    return lhs < rhs;
                };
                break;
            }
            case '>': {
                cmp_ = [](int64_t lhs, int64_t rhs) -> bool{
                    return lhs > rhs;
                };
                break;
            }
            default: {
                IC(line.at(1));
                assert(false);
            }
        }

        auto number = aoc::string::numbers_from_string(rule_str.front());
        assert(number.size() == 1);
        value_ = number.front();
        target_ = rule_str.back();
    }

    bool check(Part const& p) const {
        if (always_true_) {
            return true;
        }
        return cmp_(p.*field_, value_);
    }
};

struct Workflow {
    std::vector<Rule> rules{};

    Workflow() = default;
    Workflow(std::string const& line) {
        auto rules_str = aoc::string::split(line, ',');
        for (auto const& rule_str: rules_str) {
            rules.push_back(Rule(rule_str));
        }
    }

    std::string process(Part const& part) {
        for (auto const& rule: rules) {
            if (rule.check(part)) {
                return rule.target_;
            }
        }
        assert(false);
        return "";
    }

};

int64_t solve_1(std::vector<std::string> inp) {
    bool sorting_parts{false};
    std::unordered_map<std::string, Workflow> workflows{};

    std::vector<Part> accepted{};
    std::vector<Part> rejected{};

    for (auto const& line: inp) {
        if (line == "") {
            sorting_parts = true;
            continue;
        }

        if (!sorting_parts) {
            auto tmp = aoc::string::split(line, '{');
            workflows[tmp.at(0)] = Workflow(std::string(tmp.at(1).cbegin(), tmp.at(1).cend()-1));
            continue;
        }

        Part p(line);

        std::string step{"in"};
        while (step != "A" && step != "R") {
            step = workflows[step].process(p);
        }

        if (step == "A") {
            accepted.push_back(p);
        }
        else if (step == "R") {
            rejected.push_back(p);
        }
        else {
            assert(false);
        }
    }

    int64_t sum{0};
    for (auto const& p: accepted) {
        auto psum = p.x + p.m + p.a + p.s;
        sum += psum;
    }

    return sum;
}

struct Ranges {
    int64_t min_{4000};
    int64_t max_{0};
    // std::random_device rd{};
    // std::mt19937 gen(rd());
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

    Ranges() {
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_int_distribution<>(0, 4000);
    }

    void update(int64_t val) {
        min_ = std::min({min_, val});
        max_ = std::max({max_, val});
        // dist = std::uniform_int_distribution<>(std::min({min_, max_}), std::max({min_, max_}));
    }

    int64_t rand() {
        return dist(gen);
    }

    int64_t diff() const { return max_ - min_ + 1; }

    friend std::ostream& operator<<(std::ostream& os, Ranges const& p) {
        os << "(" << p.min_ << "," << p.max_ << ")";
        return os;
    }
};


int64_t solve_2(std::vector<std::string> inp) {
    std::unordered_map<std::string, Workflow> workflows{};

    for (auto const& line: inp) {
        if (line == "") {
            break;
        }

        auto tmp = aoc::string::split(line, '{');
        workflows[tmp.at(0)] = Workflow(std::string(tmp.at(1).cbegin(), tmp.at(1).cend()-1));
    }


    for (auto const& [k,v]: workflows) {
        IC(k);
    }

    Ranges xr{};
    Ranges mr{};
    Ranges ar{};
    Ranges sr{};

    for (size_t i{0}; i < 10'000; i++) {
        Part p(xr.rand(), mr.rand(), ar.rand(), sr.rand());
        std::string step{"in"};
        while (step != "A" && step != "R") {
            step = workflows[step].process(p);
        }

        if (step == "A") {
            continue;
        }

        xr.update(p.x);
        mr.update(p.m);
        ar.update(p.a);
        sr.update(p.s);
        IC(xr, mr, ar, sr);
    }
    int64_t sum{xr.diff() * mr.diff() * ar.diff() * sr.diff()};

    IC(sum);

    return sum;
}

void tests() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 19114);
    assert(solve_2(sample) == 167409079868000);
}

}  // namespace aoc::y2023::d18


using namespace aoc::y2023::d19;
int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = solve_1(inp);
        assert(part1 == 352052);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = solve_2(inp);
        assert(part2 > 28606137449920);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, tests, solve_1_wrapper, solve_2_wrapper, input);
}
