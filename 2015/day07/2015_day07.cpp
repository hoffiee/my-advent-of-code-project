#include AOC_HEADER

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <variant>

struct Connection {
    struct Operator {
        std::string op;
        std::string left;
        std::string right;
    };
    std::variant<uint16_t, Connection::Operator> signal;
    std::function<uint16_t(const std::string&)> get;

    Connection(uint16_t value) : signal(value){};

    Connection(std::string op, std::string left, std::string right, std::function<uint16_t(const std::string&)> _get)
        : signal(Connection::Operator{op, left, right}), get(_get){};

    uint16_t value() {
        if (std::holds_alternative<uint16_t>(signal)) {
            return std::get<uint16_t>(signal);
        }

        auto op = std::get<Connection::Operator>(signal);

        uint16_t left{0};
        uint16_t right{0};

        auto get_or_parse = [&g = get](std::string& input) {
            if (std::isdigit(input.at(0))) {
                return static_cast<uint16_t>(std::stoi(input));
            }
            return g(input);
        };

        /* When each step actually calculates it's value, we cache it. */
        if (op.op == "AND") {
            left = get_or_parse(op.left);
            right = get_or_parse(op.right);
            signal = static_cast<uint16_t>(left & right);
        } else if (op.op == "OR") {
            left = get_or_parse(op.left);
            right = get_or_parse(op.right);
            signal = static_cast<uint16_t>(left | right);
        } else if (op.op == "LSHIFT") {
            left = get_or_parse(op.left);
            right = get_or_parse(op.right);
            signal = static_cast<uint16_t>(left << right);
        } else if (op.op == "RSHIFT") {
            left = get_or_parse(op.left);
            right = get_or_parse(op.right);
            signal = static_cast<uint16_t>(left >> right);
        } else if (op.op == "NOT") {
            right = get_or_parse(op.right);
            signal = static_cast<uint16_t>(~right);
        } else if (op.op == "MAP") {
            right = get_or_parse(op.right);
            signal = static_cast<uint16_t>(right);
        } else {
            throw std::logic_error("Rethink this one too");
        }
        return std::get<uint16_t>(signal);
    }
};

std::pair<uint16_t, uint16_t> solve(std::vector<std::string>& input, std::string signal, std::string modify_signal) {
    std::unordered_map<std::string, Connection> logic;
    auto getter = [&logic](const std::string& connection) { return logic.at(connection).value(); };

    for (auto& description : input) {
        std::stringstream ss(description);

        std::vector<std::string> cmds;
        std::string inp;
        while (ss >> inp) {
            cmds.emplace_back(inp);
        }

        switch (cmds.size()) {
            case 3:
                /* can be either pure mapping or setting a value..*/
                if (std::isdigit(cmds.at(0).at(0))) {
                    logic.insert_or_assign(cmds.at(2), Connection(static_cast<uint16_t>(std::stoi(cmds.at(0)))));
                } else {
                    logic.insert_or_assign(cmds.at(2), Connection("MAP", "", cmds.at(0), getter));
                }
                break;
            case 4:
                logic.insert_or_assign(cmds.at(3), Connection(cmds.at(0), "", cmds.at(1), getter));
                break;
            case 5:
                logic.insert_or_assign(cmds.at(4), Connection(cmds.at(1), cmds.at(0), cmds.at(2), getter));
                break;
            default:
                throw std::logic_error("rethink this");
        }
    }

    /* Exit early if modify_signal isn't specified */
    if (modify_signal.empty()) {
        return std::make_pair(logic.at(signal).value(), 0);
    }

    /* Make a copy and Override the get function in the altered logic circuit
     * so that it won't grab values from the original logic */
    std::unordered_map<std::string, Connection> logic_altered = logic;
    auto getter2 = [&logic_altered](const std::string& connection) { return logic_altered.at(connection).value(); };
    for (auto& it : logic_altered) {
        it.second.get = getter2;
    }

    /* Set b to the value from solution 1 */
    logic_altered.at(modify_signal) = logic.at(signal).value();

    return std::make_pair(logic.at(signal).value(), logic_altered.at(signal).value());
}
