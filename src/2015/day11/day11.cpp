/**
 * https://adventofcode.com/2015/day/11
 */
#include <algorithm>
#include <cassert>
#include <icecream.hpp>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

bool validate_1(std::string const& pass) {
    for (size_t i{0}; i < pass.size() - 2; i++) {
        char base{pass[i]};
        if (pass[i + 1] == (base + 1) && pass[i + 2] == (base + 2)) {
            return true;
        }
    }
    return false;
}

bool validate_2(std::string const& pass) {
    for (size_t i{0}; i < pass.size(); i++) {
        switch (pass[i]) {
            case 'i':
            case 'o':
            case 'l':
                return false;
        }
    }
    return true;
}

bool validate_3(std::string const& pass) {
    std::unordered_map<std::string, int> count{};
    for (size_t i{0}; i < pass.size() - 1; i++) {
        if (pass[i] == pass[i + 1]) {
            count[pass.substr(i, 2)]++;
        }
    }
    return count.size() > 1;
}

bool validate(std::string const& pass) { return validate_1(pass) && validate_2(pass) && validate_3(pass); }

std::string next(std::string pass) {
    bool carry{true};
    for (size_t i{pass.size()}; i > 0 && carry; i--) {
        pass[i - 1]++;
        carry = false;
        if (pass[i - 1] > 'z') {
            pass[i - 1] = 'a';
            carry = true;
        }
    }
    return pass;
}

std::string next_validated(std::string pass) {
    auto nx = next(pass);
    while (!validate(nx)) {
        nx = next(nx);
    }
    return nx;
}

std::string solve_1(std::vector<std::string> const& inp) { return next_validated(inp[0]); }

std::string solve_2(std::vector<std::string> const& inp) { return next_validated(next_validated(inp[0])); }

void samples() {
    assert(validate_1("abc"));
    assert(validate_1("bcd"));
    assert(validate_1("cde"));
    assert(validate_1("xyz"));
    assert(validate_1("abd") == false);

    assert(validate_2("abc"));
    assert(validate_2("dec"));
    assert(validate_2("hjkmmn"));
    assert(validate_2("hijklmmn") == false);
    assert(validate_2("hjklmmon") == false);
    assert(validate_2("hjkmmon") == false);
    assert(validate_2("hjlkmmn") == false);

    assert(validate_3("abc") == false);
    assert(validate_3("hjkmmn") == false);
    assert(validate_3("hhkmmn"));
    assert(validate_3("mmkmmn") == false);
    assert(validate_3("abbcegjk") == false);
    assert(validate_3("abbceffg"));

    assert(validate_1("hijklmmn"));
    assert(validate("hijklmmn") == false);

    assert(validate_1("abbceffg") == false);
    assert(validate_3("abbceffg"));
    assert(validate("abbceffg") == false);

    assert(validate_3("abbcegjk") == false);
    assert(validate("abbcegjk") == false);

    assert(next("zz") == "aa");
    assert(next("ab") == "ac");
    assert(next("zzzzzzzz") == "aaaaaaaa");

    assert(next_validated("abcdefgh") == "abcdffaa");
    assert(next_validated("ghijklmn") == "ghjaabcc");
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_1(inp);
        assert(res == "hepxxyzz");
        std::cout << "part 1: " << res << std::endl;
    };

    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto res = solve_2(inp);
        assert(res == "heqaabcc");
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
