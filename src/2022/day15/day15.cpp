/**
 * Didn't figure this one out so this is an second attempt when reading other
 * solutions as well to get some inspiration and finding new techniques etc.
 */
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <sstream>

#include "aoc_runner.h"
#include "aoc_utils.h"

struct Position {
    int64_t x;
    int64_t y;
    int64_t distance(Position point) const { return std::abs(x - point.x) + std::abs(y - point.y); }
    friend std::istream& operator>>(std::istream& is, Position& pos) {
        is >> pos.x >> pos.y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Position& pos) {
        os << "[" << pos.x << "," << pos.y << "]";
        return os;
    }
};

struct Interval {
    int64_t min;
    int64_t max;
    bool subsumes(const Interval& other) const { return min <= other.min && other.max <= max; }
    bool overlaps(const Interval& other) const {
        return (min <= other.min && other.min <= max) || (min <= other.max && other.max <= max) ||
               other.subsumes(*this);
    }
    friend auto operator==(const Interval& lhs, const Interval& rhs) {
        return lhs.min == rhs.min && lhs.max == rhs.max;
    }
    friend auto operator<(const Interval& lhs, const Interval& rhs) { return lhs.min < rhs.min; }
    Interval join(const Interval& other) const { return Interval{std::min(other.min, min), std::max(other.max, max)}; }
    int64_t length() const { return max - min; }
};

struct Sensor {
    Position position{};
    Position beacon{};

    /* Calculate the interval covered by this Sensor */
    std::optional<Interval> coverage_at_row(int64_t y_coord) const {
        int64_t beacon_distance = position.distance(beacon);
        if (std::abs(position.y - y_coord) > beacon_distance) {
            return std::nullopt;
        }
        return Interval{position.x - (beacon_distance - std::abs(position.y - y_coord)),
                        position.x + (beacon_distance - std::abs(position.y - y_coord))};
    }
    friend std::istream& operator>>(std::istream& is, Sensor& sensor) {
        is >> sensor.position.x >> sensor.position.y >> sensor.beacon.x >> sensor.beacon.y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Sensor& sensor) {
        os << "[" << sensor.position.x << "," << sensor.position.y << "](" << sensor.beacon.x << "," << sensor.beacon.y
           << ")";
        return os;
    }
};

static std::vector<Interval> coverage_at_row(const std::vector<Sensor>& sensors, int64_t y_coord) {
    /* Go over all sensors, get their intervals and filter out empty ones */
    auto has_value = [](const auto& opt) { return opt.has_value(); };
    auto get_value = [](const auto& opt) { return *opt; };
    auto coverage_at = [y_coord](const auto& sensor) { return sensor.coverage_at_row(y_coord); };

    std::vector<std::optional<Interval>> intervals;
    std::transform(sensors.begin(), sensors.end(), std::back_inserter(intervals), coverage_at);

    /* a filter or a copy_if would be much neater here.*/
    std::vector<Interval> valid_intervals;
    for (auto& opt : intervals) {
        if (has_value(opt)) {
            valid_intervals.emplace_back(get_value(opt));
        }
    }
    std::sort(valid_intervals.begin(), valid_intervals.end());

    std::vector<Interval> merged;
    auto it = valid_intervals.begin();
    Interval prev = *it;
    ++it;
    while (it != valid_intervals.end()) {
        Interval curr = *it;
        if (prev.overlaps(curr)) {
            prev = prev.join(curr);
        } else {
            merged.push_back(prev);
            prev = curr;
        }
        ++it;
    }
    merged.push_back(prev);
    return merged;
}

static int64_t count_covered_spaces_at_coord(const std::vector<Sensor>& sensors, int64_t y_coord) {
    auto result = coverage_at_row(sensors, y_coord);
    auto sum = [](int64_t acc, const Interval& interval) { return acc + interval.length(); };
    return std::accumulate(result.begin(), result.end(), static_cast<int64_t>(0), sum);
}

static int64_t tuning_frequence(const std::vector<Sensor>& sensors, int64_t max) {
    int64_t out = 0;
    for (int64_t y = 0; y < max + 1; ++y) {
        auto intervals = coverage_at_row(sensors, y);
        if (intervals.size() > 1) {
            out = (intervals.front().max + 1) * 4'000'000 + y;
            break;
        }
    }
    return out;
}

static void test() {
    std::vector<Sensor> sensors{{{2, 18}, {-2, 15}},  {{9, 16}, {10, 16}},  {{13, 2}, {15, 3}},   {{12, 14}, {10, 16}},
                                {{10, 20}, {10, 16}}, {{14, 17}, {10, 16}}, {{8, 7}, {2, 10}},    {{2, 0}, {2, 10}},
                                {{0, 11}, {2, 10}},   {{20, 14}, {25, 17}}, {{17, 20}, {21, 22}}, {{16, 7}, {15, 3}},
                                {{14, 3}, {15, 3}},   {{20, 1}, {15, 3}}};
    assert(sensors.at(6).coverage_at_row(-3) == std::nullopt);
    assert((sensors.at(6).coverage_at_row(-2) == Interval{8, 8}));
    assert((sensors.at(6).coverage_at_row(7) == Interval{-1, 17}));
    assert(count_covered_spaces_at_coord(sensors, 10) == 26);
}

static std::vector<Sensor> read_and_parse_data(std::string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    std::string line;
    std::vector<Sensor> out;
    while (getline(input, line)) {
        std::stringstream ss(line);
        Sensor sensor;
        ss >> sensor;
        out.push_back(std::move(sensor));
    }
    return out;
}

void samples() {
    test();

    auto const tmp = read_and_parse_data("day15-sample.preprocessed.input");
    auto const part1 = count_covered_spaces_at_coord(tmp, 10);
    assert(part1 == 26);
    auto const part2 = tuning_frequence(tmp, 40);
    assert(part2 == 56000011);
}

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto const tmp = read_and_parse_data("day15.preprocessed.input");
        auto const res = count_covered_spaces_at_coord(tmp, 2'000'000);
        assert(res == 5176944);
        std::cout << "part 1: " << res << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto tmp = read_and_parse_data("day15.preprocessed.input");
        auto const res = tuning_frequence(tmp, 4'000'000);
        assert(res == 13350458933732);
        std::cout << "part 2: " << res << std::endl;
    };

    return aoc::run(argc, argv, samples, solve_1_wrapper, solve_2_wrapper, input);
}
