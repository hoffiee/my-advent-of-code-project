/* Current brute force for part 2, currently took 277 days when I calculated
 * it, so scrap that. Search space is too large */
/**
 * 4000000
 * 1979192 1946558
 * 1978843 1946558
 * 1979223 1946558
 * 1980389 1946558
 * 2013874 1946558
 *
 * Am I around 2'000'000 ?
 *
 * stopped at 2933907 (t4) and produced 13350458933736. It wasn't correct. It
 * was too high. So after looking into other solutions and solving this, the
 * correct was 13350458933732, which is off by 4. So this was really close.
 */
#include <chrono>
#include <fstream>
#include <iostream>

/* Solution includes */
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdint>
#include <map>
#include <mutex>
#include <numeric>
#include <optional>
#include <random>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <unordered_map>
#include <vector>

namespace {
using std::cout;
using std::endl;
using std::string;
using std::vector;
}  // namespace

struct Position {
    int64_t x;
    int64_t y;
    int64_t distance_to(Position point) { return std::abs(x - point.x) + std::abs(y - point.y); }
    friend std::istream& operator>>(std::istream& is, Position& pos) {
        is >> pos.x >> pos.y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Position& pos) {
        os << "[" << pos.x << "," << pos.y << "]";
        return os;
    }
    bool operator==(const Position& pos) const { return (x == pos.x) && (y == pos.y); }
};

struct hash_fn {
    std::size_t operator()(const Position& pos) const {
        std::size_t h1 = std::hash<int64_t>()(pos.x);
        std::size_t h2 = std::hash<int64_t>()(pos.y);

        return h1 ^ h2;
    }
};

struct Beacon {
    Position cord;
    friend std::istream& operator>>(std::istream& is, Beacon& beacon) {
        is >> beacon.cord;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Beacon& beacon) {
        os << beacon.cord;
        return os;
    }
};

struct Sensor {
    Position cord{};
    Beacon beacon{};

    int64_t distance() { return cord.distance_to(beacon.cord); }
    bool is_in_range_to(Position& pos);
    friend std::istream& operator>>(std::istream& is, Sensor& sensor) {
        is >> sensor.cord >> sensor.beacon;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Sensor& sensor) {
        os << "Sensor" << sensor.cord << " beacon" << sensor.beacon
           << " dist: " << sensor.cord.distance_to(sensor.beacon.cord);
        return os;
    }
};

bool Sensor::is_in_range_to(Position& pos) { return distance() >= cord.distance_to(pos); }

static vector<Sensor> read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    vector<Sensor> out;
    while (getline(input, line)) {
        std::stringstream ss(line);
        Sensor sensor;
        ss >> sensor;
        out.push_back(std::move(sensor));
    }
    return out;
}

static int64_t solution_1(vector<Sensor> sensors, int64_t row) {
    std::sort(sensors.begin(), sensors.end(),
              [](const Sensor& lhs, const Sensor& rhs) { return lhs.cord.y < rhs.cord.y; });

    sensors.erase(std::remove_if(sensors.begin(), sensors.end(),
                                 [row](Sensor& sens) { return sens.distance() < std::abs(sens.cord.y - row); }),
                  sensors.end());

    std::map<int64_t, int64_t> marks;
    int64_t min = INT64_MAX;
    int64_t max = INT64_MIN;
    for (auto sensor : sensors) {
        /* 2*n + 1, for n distance from y and sensor max reach  */
        int64_t dist = sensor.distance() - std::abs(sensor.cord.y - row);
        if (dist < 0) {
            throw std::logic_error("what have I done here?");
        }
        int64_t ncalc = 2 * dist + 1;
        vector<int64_t> indexes_to_mark(ncalc);
        std::iota(indexes_to_mark.begin(), indexes_to_mark.end(), sensor.cord.x - ncalc / 2);

        for (auto index : indexes_to_mark) {
            marks[index] = index;
            if (index < min) {
                min = index;
            }
            if (index > max) {
                max = index;
            }
        }
    }
    for (auto& it : sensors) {
        if (it.beacon.cord.y == row) {
            if (marks.contains(it.beacon.cord.x)) {
                marks.erase(it.beacon.cord.y);
            }
        }
    }
    return marks.size();
}

__attribute__((unused)) static int64_t solution_2(vector<Sensor> sensors, int64_t coordinate_max) {
    cout << endl;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, coordinate_max);

    Position candidate{0, 0};
    while (true) {
        candidate.x = dist6(rng);
        candidate.y = dist6(rng);
        // cout << candidate << endl;

        bool in_range = false;
        for (auto& sensor : sensors) {
            in_range = in_range || sensor.is_in_range_to(candidate);
            if (in_range) {
                break;
            }
        }

        if (!in_range) {
            break;
        }
    }
    return 4000000 * candidate.x + candidate.y;
}

__attribute__((unused)) static int64_t solution_2_2(vector<Sensor> sensors, int64_t coordinate_max) {
    cout << endl;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, coordinate_max);

    std::unordered_map<Position, bool, hash_fn> checked;

    Position candidate{0, 0};
    int count = 0;

    for (; candidate.y <= coordinate_max; ++candidate.y) {
        for (; candidate.x <= coordinate_max; ++candidate.x) {
        }
    }
    while (true) {
        candidate.x = dist6(rng);
        candidate.y = dist6(rng);

        if (checked.find(candidate) != checked.end()) {
            continue;
        }
        // cout << candidate << "havent checked this one yet" << endl;
        checked[candidate] = true;
        if (++count >= 1000) {
            count = 0;
            cout << "\r" << checked.size();
        }

        bool in_range = false;
        for (auto& sensor : sensors) {
            in_range = in_range || sensor.is_in_range_to(candidate);
            if (in_range) {
                break;
            }
        }

        if (!in_range) {
            break;
        }
    }
    cout << endl;
    return 4000000 * candidate.x + candidate.y;
}

std::mutex g_mutex;
static void worker_func(vector<Sensor> sensors, bool* search, Position* return_pos, int64_t start, int64_t step,
                        int64_t max, bool print_process) {
    Position candidate{0, start};
    bool found = false;
    int count = 0;
    for (; *search && candidate.y <= max; candidate.y += step) {
        candidate.x = 0;
        if (print_process) {
            if (++count > 5) {
                cout << "\r" << candidate.y;
            }
        }
        for (; *search && candidate.x <= max; ++candidate.x) {
            bool in_range = false;
            for (auto& sensor : sensors) {
                in_range = in_range || sensor.is_in_range_to(candidate);
                if (in_range) {
                    break;
                }
            }

            if (!in_range) {
                found = true;
                *search = false;
                break;
            }
        }
    }

    if (found) {
        std::lock_guard<std::mutex> lock(g_mutex);
        *return_pos = candidate;
    }
}

__attribute__((unused)) static int64_t solution_2_3(vector<Sensor> sensors, int64_t coordinate_max) {
    cout << endl;

    Position candidate{0, 0};
    bool search = true;

    int64_t offset = 2933907;

    std::thread t1(worker_func, sensors, &search, &candidate, offset + 0, 4, coordinate_max, false);
    std::thread t2(worker_func, sensors, &search, &candidate, offset + 1, 4, coordinate_max, false);
    std::thread t3(worker_func, sensors, &search, &candidate, offset + 2, 4, coordinate_max, false);
    std::thread t4(worker_func, sensors, &search, &candidate, offset + 3, 4, coordinate_max, true);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << endl;
    return 4000000 * candidate.x + candidate.y;
}

static void run_and_check_solutions(string task, int64_t (*solution_1)(vector<Sensor>), int64_t expected_1,
                                    int64_t (*solution_2)(vector<Sensor>), int64_t expected_2) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto input = read_and_parse_data(task);
    std::cout << task << std::endl;
    std::cout << "\ttask 1: " << solution_1(input) << " (" << expected_1 << ")" << std::endl;
    std::cout << "\ttask 2: " << solution_2(input) << " (" << expected_2 << ")" << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "execution time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns"
              << std::endl;
}

static void test() {
    Position pos1{0, 0};
    Position pos2{0, 0};
    Position pos3{1, 0};
    Position pos4{0, 1};
    Position pos5{-1, 0};
    Position pos6{0, -1};

    assert(pos1 == pos2);
    assert(!(pos1 == pos3));
    assert(!(pos1 == pos4));
    assert(!(pos1 == pos5));
    assert(!(pos1 == pos6));

    std::unordered_map<Position, bool, hash_fn> m;

    m[pos1] = true;

    assert(m.find(pos1) != m.end());
    assert(m.find(pos2) != m.end());
    assert(m.find(pos3) == m.end());
    assert(m.find(pos4) == m.end());
    assert(m.find(pos5) == m.end());
    assert(m.find(pos6) == m.end());
}

int main(void) {
    test();
    auto solution_1_sample = [](vector<Sensor> in) { return solution_1(in, 10); };
    auto solution_2_sample = [](vector<Sensor> in) { return solution_2_3(in, 20); };
    run_and_check_solutions("day15-sample.prep.input", solution_1_sample, 26, solution_2_sample, 56000011);

    auto solution_1_puzzle = [](vector<Sensor> in) { return solution_1(in, 2000000); };
    auto solution_2_puzzle = [](vector<Sensor> in) { return solution_2_3(in, 4000000); };
    run_and_check_solutions("day15.prep.input", solution_1_puzzle, 5176944, solution_2_puzzle, 0);
}
