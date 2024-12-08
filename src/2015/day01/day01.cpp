#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

static std::pair<int, int> solve(std::string input) {
    int floor = 0;
    int position = -1;

    for (size_t i = 0; i < input.size(); ++i) {
        floor += (input.at(i) == '(') ? +1 : -1;

        if (floor < 0 && position == -1) {
            position = static_cast<int>(i + 1);
        }
    }
    return {floor, position};
}

static void test() {
    assert(solve("(())").first == 0);
    assert(solve("(((").first == 3);
    assert(solve("(()(()(").first == 3);
    assert(solve("))(((((").first == 3);
    assert(solve("())").first == -1);
    assert(solve("))(").first == -1);
    assert(solve(")))").first == -3);
    assert(solve(")())())").first == -3);
    {
        auto [floor, position] = solve(")");
        assert(floor == -1);
        assert(position == 1);
    }
    {
        auto [floor, position] = solve("()())");
        assert(floor == -1);
        assert(position == 5);
    }
}

int main() {
    test();

    std::ifstream input;
    input.open("day01.input");
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return -1;
    }
    std::string line;
    getline(input, line);

    auto [floor, position] = solve(line);
    std::cout << floor << " " << position << std::endl;

    return 0;
}
