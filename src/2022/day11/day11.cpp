/**
 * https://adventofcode.com/2022/day/11
 *
 * increasing to 10000 rounds, and using int64_t (also tried with uint64_t)
 * gave no results. After digging a bit it turns out that one way to handle
 * that was utilize the following property of modulus
 *
 * n % k = (n % (k*m)) % k
 * n % m = (n % (k*m)) % m
 *
 * i.e., we can create a product of all the denominator from each monkeys, and
 * limit our values with the modulo on that product, as the remainder of n%q is
 * the same as (n % (k*m)) % k
 */
#include <icecream.hpp>
#include <optional>
#include <queue>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"
#include "string_utils.h"

namespace aoc::y2022::d11 {

struct Monkey {
    int64_t index_{};
    int64_t divisible_by_{};
    char operator_{};
    int64_t test_product_{};
    int64_t throw_test_true_{};
    int64_t throw_test_false_{};

    std::optional<int64_t> value_{std::nullopt};
    std::queue<int64_t> items_{};

    int64_t fcn(int64_t const val, bool divide) const {
        int64_t value{value_.has_value() ? value_.value() : val};
        int64_t out{};
        switch (operator_) {
            case '+': {
                out = (val + value);
                break;
            }
            case '-': {
                out = (val - value);
                break;
            }
            case '*': {
                out = (val * value);
                break;
            }
            default: {
                assert(false);
                break;
            }
        }
        if (divide) {
            out /= 3;
        } else {
            out %= test_product_;
        }
        return out;
    }

    void set_oper(std::string const& oper) {
        auto const& opers = aoc::string::split(oper, ' ');
        assert(opers.size() == 4);
        assert(opers.at(0) == "");
        assert(opers.at(1) == "old");
        operator_ = opers.at(2).front();
        auto const numbers = string_utils::numbers_from_string(oper);
        if (numbers.size() > 0) {
            assert(numbers.size() == 1u);
            value_ = numbers.front();
        }
    }

    std::pair<int64_t, int64_t> inspect_and_test(bool divide = true) {
        auto level = items_.front();
        items_.pop();

        level = fcn(level, divide);

        if (level % divisible_by_ == 0) {
            return {throw_test_true_, level};
        }
        return {throw_test_false_, level};
    }

    friend std::ostream& operator<<(std::ostream& os, Monkey const& m) {
        os << "index:" << m.index_;
        os << " divisble_by:" << m.divisible_by_;
        os << " items.size():" << m.items_.size();
        os << " operator_:" << m.operator_;
        if (m.value_.has_value()) {
            os << " value_:" << m.value_.value();
        }
        os << " throw_test_true:" << m.throw_test_true_;
        os << " throw_test_false:" << m.throw_test_false_;

        return os;
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    // +1 since last row does'nt have an empty line
    std::size_t nr_of_monkeys{inp.size() / 7 + 1};

    std::vector<Monkey> monkeys(nr_of_monkeys, Monkey{});
    for (std::size_t i{0}; i < nr_of_monkeys; i++) {
        std::size_t offset{i * 7};

        monkeys.at(i).index_ = static_cast<int64_t>(i);

        for (auto const item : string_utils::numbers_from_string(inp.at(offset + 1))) {
            monkeys.at(i).items_.push(item);
        }

        auto const oper = aoc::string::split(inp.at(offset + 2), '=');
        monkeys.at(i).set_oper(oper.back());

        monkeys.at(i).divisible_by_ = string_utils::numbers_from_string(inp.at(offset + 3)).at(0);

        monkeys.at(i).throw_test_true_ = string_utils::numbers_from_string(inp.at(offset + 4)).at(0);
        monkeys.at(i).throw_test_false_ = string_utils::numbers_from_string(inp.at(offset + 5)).at(0);
    }

    std::size_t rounds{20};
    std::vector<int64_t> monkey_inspect_count(nr_of_monkeys, 0);
    for (std::size_t round{0}; round < rounds; round++) {
        for (std::size_t monkey{0}; monkey < monkeys.size(); monkey++) {
            while (!monkeys.at(monkey).items_.empty()) {
                auto const [index, level] = monkeys.at(monkey).inspect_and_test();
                monkey_inspect_count.at(monkey)++;
                monkeys.at(index).items_.push(level);
            }
        }
    }
    std::partial_sort(monkey_inspect_count.begin(), monkey_inspect_count.begin() + 2, monkey_inspect_count.end(),
                      std::greater{});

    return monkey_inspect_count.at(0) * monkey_inspect_count.at(1);
}

int64_t solve_2(std::vector<std::string> inp) {
    // +1 since last row does'nt have an empty line
    std::size_t nr_of_monkeys{inp.size() / 7 + 1};

    std::vector<Monkey> monkeys(nr_of_monkeys, Monkey{});
    int64_t product{1};
    for (std::size_t i{0}; i < nr_of_monkeys; i++) {
        std::size_t offset{i * 7};

        monkeys.at(i).index_ = static_cast<int64_t>(i);

        for (auto const item : string_utils::numbers_from_string(inp.at(offset + 1))) {
            monkeys.at(i).items_.push(item);
        }

        auto const oper = aoc::string::split(inp.at(offset + 2), '=');
        monkeys.at(i).set_oper(oper.back());

        monkeys.at(i).divisible_by_ = string_utils::numbers_from_string(inp.at(offset + 3)).at(0);
        product *= monkeys.at(i).divisible_by_;

        monkeys.at(i).throw_test_true_ = string_utils::numbers_from_string(inp.at(offset + 4)).at(0);
        monkeys.at(i).throw_test_false_ = string_utils::numbers_from_string(inp.at(offset + 5)).at(0);
    }

    for (std::size_t i{0}; i < nr_of_monkeys; i++) {
        monkeys.at(i).test_product_ = product;
    }

    std::size_t rounds{10000};
    std::vector<int64_t> monkey_inspect_count(nr_of_monkeys, 0);
    for (std::size_t round{0}; round < rounds; round++) {
        for (std::size_t monkey{0}; monkey < monkeys.size(); monkey++) {
            while (!monkeys.at(monkey).items_.empty()) {
                auto const [index, level] = monkeys.at(monkey).inspect_and_test(false);
                monkey_inspect_count.at(monkey)++;
                monkeys.at(index).items_.push(level);
            }
        }
    }

    std::partial_sort(monkey_inspect_count.begin(), monkey_inspect_count.begin() + 2, monkey_inspect_count.end(),
                      std::greater{});

    return monkey_inspect_count.at(0) * monkey_inspect_count.at(1);
}

void samples() {
    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 10605);
    assert(solve_2(sample) == 2713310158);
}

};  // namespace aoc::y2022::d11

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2022::d11::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2022::d11::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2022::d11::samples, solve_1_wrapper, solve_2_wrapper, input);
}
