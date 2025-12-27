/**
 * https://adventofcode.com/2024/day/15
 *
 * aoc_tags: 2d grid, moving boxes
 */
#include <ncurses.h>

#include <cassert>
#include <complex>
#include <icecream.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace {

using Pos = std::complex<int64_t>;

struct PosHash {
    std::size_t operator()(const Pos& c) const {
        return std::hash<int>()(c.real()) ^ (std::hash<int>()(c.imag()) << 8);
    }
};

struct PosEqual {
    bool operator()(Pos const& lhs, Pos const& rhs) const {
        return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }
};

bool operator<(Pos const& lhs, Pos const& rhs) { return lhs.real() < rhs.real(); }

namespace Dir {
constexpr Pos Up = {0, -1};
constexpr Pos Down = {0, 1};
constexpr Pos Left = {-1, 0};
constexpr Pos Right = {1, 0};
}  // namespace Dir

std::tuple<std::vector<std::string>, std::string> parse(std::vector<std::string> const& inp) {
    bool parse_grid{true};
    std::vector<std::string> map{};
    std::string moveset{};
    for (auto line : inp) {
        if (line == "") {
            parse_grid = false;
            continue;
        }
        if (parse_grid) {
            map.emplace_back(line);
        } else {
            moveset += line;
        }
    }
    return {map, moveset};
}

std::unordered_map<char, Pos> const direction_transform{
    {'^', Dir::Up}, {'v', Dir::Down}, {'<', Dir::Left}, {'>', Dir::Right}};
};  // namespace

struct Warehouse {
    std::unordered_map<Pos, Pos, PosHash, PosEqual> boxes_{};
    std::unordered_map<Pos, int, PosHash, PosEqual> walls_{};
    int64_t row_sz_{};
    int64_t col_sz_{};
    Pos robot_pos_{-1, -1};

    Warehouse(int64_t row_sz, int64_t col_sz) : row_sz_{row_sz}, col_sz_{col_sz} {};
    Warehouse(std::vector<std::string> const& map)
        : row_sz_{static_cast<int64_t>(map.size())}, col_sz_{static_cast<int64_t>(map.at(0).size())} {
        for (int64_t y{0}; y < row_sz_; y++) {
            for (int64_t x{0}; x < col_sz_; x++) {
                Pos cand{x, y};
                switch (map.at(y).at(x)) {
                    case '@':
                        robot_pos_ = cand;
                        break;
                    case 'O':
                        boxes_[cand];
                        break;
                    case '#':
                        walls_[cand];
                        break;
                    case '.':
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
        }
    };

    void print(bool render = false) const {
        if (render) {
            clear();
            init_pair(1, COLOR_BLUE, -1);
            init_pair(2, COLOR_RED, -1);
        }
        for (int64_t y{0}; y < row_sz_; y++) {
            for (int64_t x{0}; x < col_sz_; x++) {
                Pos node{x, y};
                if (render) {
                    if (robot_pos_ == node) {
                        mvaddch(y, x, '@' | COLOR_PAIR(1));
                        continue;
                    }
                    if (boxes_.contains(node)) {
                        mvaddch(y, x, 'O' | COLOR_PAIR(2));
                        continue;
                    }
                    if (walls_.contains(node)) {
                        mvaddch(y, x, '#');
                        continue;
                    }
                    mvaddch(y, x, ' ');
                } else {
                    if (robot_pos_ == node) {
                        std::cout << "@";
                        continue;
                    }
                    if (boxes_.contains(node)) {
                        std::cout << "O";
                        continue;
                    }
                    if (walls_.contains(node)) {
                        std::cout << "#";
                        continue;
                    }
                    std::cout << " ";
                }
            }
            if (!render) {
                std::cout << std::endl;
            }
        }
    }

    bool within_bounds(Pos pos) const {
        if ((pos.real() < 0) || (pos.imag() < 0) || (col_sz_ <= pos.real()) || (row_sz_ <= pos.imag())) {
            return false;
        }
        return true;
    }

    virtual bool can_move_box(Pos pos, Pos dir) const {
        Pos cand{pos + dir};
        if (!within_bounds(cand) || walls_.contains(cand)) {
            return false;
        }
        if (boxes_.contains(cand) && !can_move_box(cand, dir)) {
            return false;
        }
        return true;
    }

    virtual bool move_box(Pos pos, Pos dir) {
        Pos cand{pos + dir};
        if (!within_bounds(cand) || walls_.contains(cand)) {
            return false;
        }

        if (boxes_.contains(cand) && !move_box(cand, dir)) {
            return false;
        }

        boxes_.erase(pos);
        auto [_, ins] = boxes_.insert({cand, false});
        assert(ins);

        return true;
    }

    bool move(Pos dir) {
        Pos cand{robot_pos_ + dir};
        if (!within_bounds(cand) || walls_.contains(cand)) {
            return false;
        }

        if (boxes_.contains(cand)) {
            if (!can_move_box(cand, dir)) {
                return false;
            }
            move_box(cand, dir);
        }
        robot_pos_ = cand;
        return true;
    }

    int64_t score() const {
        int64_t acc{0};
        for (auto [box1, box2] : boxes_) {
            // Handle both Warehouse and ExtendedWarehouse boxes
            if (box2 == Pos{} || box1 < box2) {
                acc += 100 * box1.imag() + box1.real();
            }
        }
        return acc;
    }
};

struct ExtendedWarehouse : Warehouse {
    ExtendedWarehouse(std::vector<std::string> const& map)
        : Warehouse{static_cast<int64_t>(map.size()), static_cast<int64_t>(2 * map.at(0).size())} {
        for (int64_t y{0}; y < static_cast<int64_t>(map.size()); y++) {
            for (int64_t x{0}; x < static_cast<int64_t>(map.at(y).size()); x++) {
                Pos cand{2 * x, y};
                switch (map.at(y).at(x)) {
                    case '@':
                        robot_pos_ = cand;
                        break;
                    case 'O':
                        boxes_[cand] = cand + Dir::Right;
                        boxes_[cand + Dir::Right] = cand;
                        break;
                    case '#':
                        walls_[cand];
                        walls_[cand + Dir::Right];
                        break;
                    case '.':
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
        }
    };

    void print(bool render = false) const {
        if (render) {
            clear();
            init_pair(1, COLOR_BLUE, -1);
            init_pair(2, COLOR_RED, -1);
        }
        for (int64_t y{0}; y < row_sz_; y++) {
            for (int64_t x{0}; x < col_sz_; x++) {
                Pos node{x, y};
                if (render) {
                    if (robot_pos_ == node) {
                        mvaddch(y, x, '@' | COLOR_PAIR(1));
                        continue;
                    }
                    if (boxes_.contains(node)) {
                        mvaddch(y, x, '[' | COLOR_PAIR(2));
                        x++;
                        mvaddch(y, x, ']' | COLOR_PAIR(2));
                        continue;
                    }
                    if (walls_.contains(node)) {
                        mvaddch(y, x, '#');
                        continue;
                    }
                    mvaddch(y, x, ' ');
                } else {
                    if (robot_pos_ == node) {
                        std::cout << "@";
                        continue;
                    }
                    if (boxes_.contains(node)) {
                        std::cout << "O";
                        continue;
                    }
                    if (walls_.contains(node)) {
                        std::cout << "#";
                        continue;
                    }
                    std::cout << " ";
                }
            }
            if (!render) {
                std::cout << std::endl;
            }
        }
    }

    bool can_move_box_x(Pos pos, Pos dir) const {
        assert(dir.imag() == 0);
        Pos cand{pos + dir};
        if (!within_bounds(cand) || walls_.contains(cand)) {
            return false;
        }
        if (boxes_.contains(cand) && !can_move_box_x(cand, dir)) {
            return false;
        }
        return true;
    }

    bool can_move_box_y(Pos pos, Pos dir) const {
        assert(dir.real() == 0);
        Pos cand1{pos + dir};
        Pos cand2{boxes_.at(pos) + dir};
        if (!within_bounds(cand1) || !within_bounds(cand2) || walls_.contains(cand1) || walls_.contains(cand2)) {
            return false;
        }
        if ((boxes_.contains(cand1) && !can_move_box(cand1, dir)) ||
            (boxes_.contains(cand2) && !can_move_box(cand2, dir))) {
            return false;
        }
        return true;
    }

    bool can_move_box(Pos pos, Pos dir) const {
        if (dir.real() != 0) {
            return can_move_box_x(pos, dir);
        }
        return can_move_box_y(pos, dir);
    }

    bool move_box_x(Pos pos, Pos dir) {
        assert(dir.imag() == 0);
        Pos cand{pos + dir};
        if (!within_bounds(cand)) {
            return false;
        }
        if (walls_.contains(cand)) {
            return false;
        }

        if (boxes_.contains(cand)) {
            if (!move_box(cand, dir)) {
                return false;
            }
        }

        auto new_ref = boxes_.at(pos) + dir;
        boxes_.erase(pos);
        auto [_, ins] = boxes_.insert({cand, new_ref});
        assert(ins);
        return true;
    }

    bool move_box_y(Pos pos, Pos dir) {
        assert(dir.real() == 0);
        Pos cand1{pos + dir};
        Pos cand2{boxes_.at(pos) + dir};

        if (boxes_.contains(cand1)) {
            move_box(cand1, dir);
        }
        if (boxes_.contains(cand2)) {
            move_box(cand2, dir);
        }

        boxes_.erase(boxes_.at(pos));
        boxes_.erase(pos);

        auto res = boxes_.insert({cand1, cand2});
        assert(std::get<1>(res));
        res = boxes_.insert({cand2, cand1});
        assert(std::get<1>(res));

        return true;
    }

    bool move_box(Pos pos, Pos dir) override {
        if (dir.real() != 0) {
            return move_box_x(pos, dir);
        }
        return move_box_y(pos, dir);
    }
};

int64_t solve_1(std::vector<std::string> inp, bool render = false) {
    auto [map, moveset] = parse(inp);
    Warehouse warehouse{map};

    if (render) {
        initscr();
        cbreak();
        noecho();
        start_color();
        use_default_colors();
        curs_set(0);
    }

    for (auto dir : moveset | std::views::transform([](auto ch) { return direction_transform.at(ch); })) {
        warehouse.move(dir);
        if (render) {
            warehouse.print(true);
            refresh();
            napms(5);
        }
    }

    if (render) {
        endwin();
    }
    int64_t ans{warehouse.score()};
    return ans;
}

int64_t solve_2(std::vector<std::string> inp, bool render = false) {
    auto [map, moveset] = parse(inp);
    ExtendedWarehouse warehouse{map};

    if (render) {
        initscr();
        cbreak();
        noecho();
        start_color();
        use_default_colors();
        curs_set(0);
    }

    for (auto dir : moveset | std::views::transform([](auto ch) { return direction_transform.at(ch); })) {
        warehouse.move(dir);
        if (render) {
            warehouse.print(true);
            refresh();
            napms(25);
        }
    }

    if (render) {
        getch();
        endwin();
    }

    int64_t ans{warehouse.score()};
    return ans;
}

void samples() {
    auto sample1 = aoc::utils::read_input("day15-sample-1.input");
    assert(solve_1(sample1) == 2028);

    auto sample2 = aoc::utils::read_input("day15-sample-2.input");
    assert(solve_1(sample2) == 10092);

    auto sample3 = aoc::utils::read_input("day15-sample-3.input");
    assert(solve_2(sample3) == (105 + 100 * 2 + 7 + 100 * 3 + 6));
    assert(solve_2(sample2) == 9021);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_1(inp);
        assert(res == 1478649);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const res = solve_2(inp, false);
        assert(res == 1495455);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
