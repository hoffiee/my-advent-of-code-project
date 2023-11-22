#include AOC_HEADER

#include <iostream>

struct Keypad {
    size_t _x;
    size_t _y;
    std::vector<std::string> keypad;
    std::string key;

    Keypad(std::vector<std::string> keypad, size_t x, size_t y) : _x(x), _y(y), keypad(keypad) { key = ""; }

    void move(char dir);
    void print();
    void add_key();
    std::string current_key();
};

void Keypad::move(char dir) {
    switch (dir) {
        case 'U':
            if (keypad.at(_y - 1).at(_x) == ' ') {
                break;
            }
            _y -= 1;
            break;
        case 'R':
            if (keypad.at(_y).at(_x + 1) == ' ') {
                break;
            }
            _x += 1;
            break;
        case 'D':
            if (keypad.at(_y + 1).at(_x) == ' ') {
                break;
            }
            _y += 1;
            break;
        case 'L':
            if (keypad.at(_y).at(_x - 1) == ' ') {
                break;
            }
            _x -= 1;
            break;
    }
}

void Keypad::print() {
    for (size_t y = 0; y < keypad.size(); ++y) {
        for (size_t x = 0; x < keypad.at(y).size(); ++x) {
            if (x == _x && y == _y) {
                std::cout << "*";
                continue;
            }
            std::cout << keypad.at(y).at(x);
        }
        std::cout << std::endl;
    }
}

void Keypad::add_key() { key.push_back(keypad.at(_y).at(_x)); }

std::string Keypad::current_key() { return key; }

std::pair<std::string, std::string> solve(std::vector<std::string>& input) {
    std::vector<std::string> keypad_1 = {
        "     ", " 123 ", " 456 ", " 789 ", "     ",
    };
    std::vector<std::string> keypad_2 = {
        "       ", "   1   ", "  234  ", " 56789 ", "  ABC  ", "   D   ", "       ",
    };

    Keypad kp1(keypad_1, 2, 2);
    Keypad kp2(keypad_2, 1, 3);

    for (auto& row : input) {
        for (auto cmd : row) {
            kp1.move(cmd);
            kp2.move(cmd);
        }
        kp1.add_key();
        kp2.add_key();
    }

    return {
        kp1.current_key(),
        kp2.current_key(),
    };
}
