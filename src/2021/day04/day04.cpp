/**
 * https://adventofcode.com/2021/day/4
 */
#include AOC_HEADER

#include <algorithm>
#include <icecream.hpp>
#include <sstream>

struct Entry {
    int number;
    bool marked;
};

struct Board {
    Entry grid[5][5];
    int win_at_count = 0;

    Board(std::vector<std::string> inp);
    void mark(int number);
    bool win();
    void set_win_at_count(int count);
    void print();
    int sum_of_unmarked();
};

Board::Board(std::vector<std::string> inp) {
    for (size_t r = 0; r < inp.size(); r++) {
        std::stringstream ss(inp.at(r));
        for (size_t c = 0; c < inp.size(); c++) {
            int number = 0;
            ss >> number;
            grid[r][c].number = number;
            grid[r][c].marked = false;
        }
    }
}

void Board::mark(int number) {
    for (size_t r = 0; r < 5; r++) {
        for (size_t c = 0; c < 5; c++) {
            if (grid[r][c].number == number) {
                grid[r][c].marked = true;
            }
        }
    }
}

bool Board::win() {
    // check rows
    for (size_t r = 0; r < 5; r++) {
        int count = 0;
        for (size_t c = 0; c < 5; c++) {
            if (grid[r][c].marked) {
                count++;
            }
        }
        if (count == 5) {
            return true;
        }
    }
    // check columns
    for (size_t c = 0; c < 5; c++) {
        int count = 0;
        for (size_t r = 0; r < 5; r++) {
            if (grid[r][c].marked) {
                count++;
            }
        }
        if (count == 5) {
            return true;
        }
    }
    return false;
}

void Board::print() {
    for (size_t r = 0; r < 5; r++) {
        for (size_t c = 0; c < 5; c++) {
            if (grid[r][c].marked) {
                std::cout << "*";
            }
            std::cout << grid[r][c].number << "\t";
        }
        std::cout << std::endl;
    }
    IC(win_at_count);
    std::cout << std::endl;
}

int Board::sum_of_unmarked() {
    int sum = 0;
    for (size_t r = 0; r < 5; r++) {
        for (size_t c = 0; c < 5; c++) {
            if (!grid[r][c].marked) {
                sum += grid[r][c].number;
            }
        }
    }
    return sum;
}

void Board::set_win_at_count(int count) { win_at_count = count; }

struct Problem {
    std::vector<int> random_order;
    std::vector<Board> boards;

    Problem(std::vector<std::string> inp);
    int solve(std::function<int(Board&)>);
};

Problem::Problem(std::vector<std::string> inp) {
    std::stringstream ss(inp.at(0));
    while (!ss.eof()) {
        char delim = ',';
        int number = 0;
        ss >> number >> delim;
        random_order.push_back(number);
    }

    int nr_of_boards = (static_cast<int>(inp.size()) - 1) / 6;
    for (int i = 0; i < nr_of_boards; i++) {
        // Slice from array with copy constructor
        auto test = std::vector<std::string>(inp.begin() + 2 + 6 * i, inp.begin() + 2 + 5 + 6 * i);
        boards.emplace_back(Board(test));
    }
}

int solve_1(std::vector<std::string> inp) {
    Problem problem(inp);

    int out = 0;
    for (auto draw : problem.random_order) {
        for (auto& board : problem.boards) {
            board.mark(draw);
        }
        if (std::any_of(problem.boards.begin(), problem.boards.end(), [](Board& b) { return b.win(); })) {
            for (auto& board : problem.boards) {
                //  Maybe avoid checking this twice, return count of unmarked
                //  from win? Check what part 2 does.
                if (board.win()) {
                    out = draw * board.sum_of_unmarked();
                }
            }
            break;
        }
    }
    return out;
}

int solve_2(std::vector<std::string> inp) {
    Problem problem(inp);

    int out = 0;
    int count = 0;
    std::vector<bool> still_playing(problem.boards.size(), true);
    for (auto draw : problem.random_order) {
        for (size_t i = 0; i < problem.boards.size(); i++) {
            problem.boards.at(i).mark(draw);
            if (still_playing.at(i) && problem.boards.at(i).win()) {
                problem.boards.at(i).set_win_at_count(count);
                still_playing.at(i) = false;
            }
        }
        count++;

        if (std::none_of(still_playing.begin(), still_playing.end(), [](bool playing) { return playing; })) {
            auto last_board = std::max_element(problem.boards.begin(), problem.boards.end(), [](auto& lhs, auto& rhs) {
                return lhs.win_at_count < rhs.win_at_count;
            });
            out = draw * last_board->sum_of_unmarked();
            break;
        }
    }
    return out;
}
