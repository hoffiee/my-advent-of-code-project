/**
 * 3882224466192 -- answer to high
 * 3882224466194 -- answer to high
 * 3952741911612 -- answer to high
 *
 * I ran this in python and sympy instead which gave me 3882224466191 for part
 * 2 so it seems that perhaps there's multiple possible answers or there's
 * something I have done wrong here, probably the latter. WHen I search for
 * that it seems to be correct in this solution as well though. so I don't know
 * why it considers the numbers above to be correct too.
 *
 * The solution for part 1 was inspired and influenced by Simon Toth solution.
 */
#include <chrono>
#include <fstream>
#include <iostream>

/* Solution includes */
#include <cmath>
#include <functional>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace {
using std::cout;
using std::endl;
using std::string;
}  // namespace

struct Monkey {
    struct _Op {
        char op;
        string left;
        string right;
    };
    std::variant<int64_t, Monkey::_Op> _job;
    std::function<int64_t(const string&)> _query;

    Monkey(int64_t value) : _job(value){};

    Monkey(char op, string left, string right, std::function<int64_t(const string&)> query)
        : _job(Monkey::_Op{op, left, right}), _query(query){};

    int64_t value() {
        if (std::holds_alternative<int64_t>(_job)) {
            return std::get<int64_t>(_job);
        }
        auto op = std::get<Monkey::_Op>(Monkey::_job);
        int64_t left = _query(op.left);
        int64_t right = _query(op.right);
        switch (op.op) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
        }
        return 0;
    }
};

struct Description {
    struct Storage {
        std::unordered_map<string, Monkey> monkeys;
    };
    std::unique_ptr<Storage> db;

    Description() : db(std::make_unique<Storage>()){};

    friend std::istream& operator>>(std::istream& is, Description& riddle) {
        string name;
        while (is >> name) {
            while (std::isspace(is.peek())) {
                is.get();
            }
            if (std::isdigit(is.peek())) {
                int64_t value;
                if (is >> value) {
                    riddle.db->monkeys.insert_or_assign(name, Monkey(value));
                } else {
                    string left;
                    string right;
                    char op = '\0';
                    if (is >> left >> op >> right) {
                        riddle.db->monkeys.insert_or_assign(
                            name, Monkey(op, left, right, [db = riddle.db.get()](const string& name) {
                                return db->monkeys.at(name).value();
                            }));
                    }
                }
            }
        }
        return is;
    }

    int64_t root() { return db->monkeys.at("root").value(); }
};

static int64_t find_number_to_yell(Description& desc) {
    auto& input = desc.db->monkeys.at("humn");
    auto& left_monkey = std::get<Monkey::_Op>(desc.db->monkeys.at("root")._job).left;
    auto& right_monkey = std::get<Monkey::_Op>(desc.db->monkeys.at("root")._job).right;
    auto left = [&]() { return desc.db->monkeys.at(left_monkey).value(); };
    auto right = [&]() { return desc.db->monkeys.at(right_monkey).value(); };

    /*  Binary search didn't find the proper solution, so I played around with
     *  some linear searches. Binary search worked for the sample input, but
     *  not the puzzle */
    // int64_t out = 3952741911612;
    // int64_t out = 3952741821604;
    // int64_t out = 3952739881411;
    int64_t out = 3882224466191;
    int64_t count = 0;
    for (; out >= 0; --out) {
        input = out;
        int64_t mid_result = left() - right();

        if (++count > 10000) {
            count = 0;
            cout << "testing: " << out << endl;
            ;
        }
        if (mid_result == 0) {
            break;
        }
    }
    return out;
}

static Description read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    Description desc;
    while (getline(input, line)) {
        std::stringstream ss(line);
        string name;
        string left;
        string op;
        string right;
        ss >> name >> left >> op >> right;
        if (std::isdigit(left.front())) {
            std::stringstream valss(left);
            int64_t value;
            if (valss >> value) {
                desc.db->monkeys.insert_or_assign(name, Monkey(value));
            }
        } else {
            desc.db->monkeys.insert_or_assign(
                name, Monkey(op.front(), left, right,
                             [db = desc.db.get()](const string& monkey) { return db->monkeys.at(monkey).value(); }));
        }
    }
    return desc;
}

int main(void) {
    for (auto& it : {
             "day21-sample.input",
             "day21-sample.input",
         }) {
        auto desc = read_and_parse_data(it);
        cout << desc.root() << endl;
        cout << find_number_to_yell(desc) << endl;
    }
}
