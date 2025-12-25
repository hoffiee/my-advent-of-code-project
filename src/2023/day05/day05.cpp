/**
 * https://adventofcode.com/2023/day/5
 */
#include AOC_HEADER

#include <omp.h>

#include <climits>
#include <icecream.hpp>
#include <map>
#include <numeric>
#include <unordered_map>

struct Range {
    int64_t x;
    int64_t y;
    int64_t len;

    Range(int64_t x, int64_t y, int64_t len) : x(x), y(y), len(len){};
    bool in_range(int64_t src);
    int64_t f(int64_t src);
};

bool Range::in_range(int64_t src) { return x <= src && src < x + len; }

int64_t Range::f(int64_t src) { return src - x + y; }

struct Map {
    std::map<int64_t, Range> map;
    std::map<int64_t, Range> mapinv;

    void add_range(int64_t destination_start, int64_t source_start, int64_t length);
    void add_range(std::string line);
    void print();
    int64_t operator[](int64_t idx);
    int64_t inv(int64_t idx);

    // Used only in part 2
    bool in_range(int64_t x);
};

void Map::add_range(int64_t destination_start, int64_t source_start, int64_t length) {
    map.emplace(std::make_pair(source_start, Range(source_start, destination_start, length)));
    mapinv.emplace(std::make_pair(destination_start, Range(destination_start, source_start, length)));
}

bool Map::in_range(int64_t x) {
    for (auto& [key, range] : map) {
        // since keys are sorted, exit early if we've passed it and there are
        // no future values in which it fits
        if (x < key) {
            return false;
        }
        if (range.in_range(x)) {
            return true;
        }
    }
    return false;
}

void Map::add_range(std::string line) {
    std::stringstream ss(line);
    int64_t dst_start = 0;
    int64_t src_start = 0;
    int64_t len = 0;
    ss >> dst_start >> src_start >> len;
    add_range(dst_start, src_start, len);
}

void Map::print() {
    for (auto& [key, elem] : map) {
        IC(key, elem.x, elem.y, elem.len);
    }
}

int64_t Map::operator[](int64_t idx) {
    for (auto& [key, elem] : map) {
        if (elem.in_range(idx)) {
            return elem.f(idx);
        }
    }
    return idx;
}

int64_t Map::inv(int64_t idx) {
    for (auto& [key, elem] : mapinv) {
        if (elem.in_range(idx)) {
            return elem.f(idx);
        }
    }
    return idx;
}

int64_t solve_1(std::vector<std::string> inp) {
    std::vector<int64_t> seeds;
    {
        std::stringstream ss(inp.at(0).substr(inp.at(0).find(":") + 1));
        int64_t seed = 0;
        while (ss >> seed) {
            seeds.push_back(seed);
        }
    }

    Map seed_to_soil;
    Map soil_to_fertilizer;
    Map fertilizer_to_water;
    Map water_to_light;
    Map light_to_temperature;
    Map temperature_to_humidity;
    Map humidity_to_location;
    for (size_t i = 1; i < inp.size(); i++) {
        if (inp.at(i).find("seed-to-soil") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                seed_to_soil.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("soil-to-fertilizer") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                soil_to_fertilizer.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("fertilizer-to-water") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                fertilizer_to_water.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("water-to-light") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                water_to_light.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("light-to-temperature") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                light_to_temperature.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("temperature-to-humidity") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                temperature_to_humidity.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("humidity-to-location") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                humidity_to_location.add_range(inp.at(i));
            }
        }
    }

    auto total_map = [&](int64_t seed) {
        return humidity_to_location
            [temperature_to_humidity
                 [light_to_temperature[water_to_light[fertilizer_to_water[soil_to_fertilizer[seed_to_soil[seed]]]]]]];
    };

    int64_t min = INT_MAX;
    for (auto seed : seeds) {
        if (int64_t candidate = total_map(seed); candidate < min) {
            min = candidate;
        }
    }

    return min;
}

int64_t solve_2(std::vector<std::string> inp) {
    Map seeds;
    {
        std::stringstream ss(inp.at(0).substr(inp.at(0).find(":") + 1));
        int64_t seed = 0;
        int64_t len = 0;
        while (ss >> seed >> len) {
            seeds.add_range(seed, seed, len);
        }
    }

    Map seed_to_soil;
    Map soil_to_fertilizer;
    Map fertilizer_to_water;
    Map water_to_light;
    Map light_to_temperature;
    Map temperature_to_humidity;
    Map humidity_to_location;
    for (size_t i = 1; i < inp.size(); i++) {
        if (inp.at(i).find("seed-to-soil") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                seed_to_soil.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("soil-to-fertilizer") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                soil_to_fertilizer.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("fertilizer-to-water") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                fertilizer_to_water.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("water-to-light") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                water_to_light.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("light-to-temperature") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                light_to_temperature.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("temperature-to-humidity") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                temperature_to_humidity.add_range(inp.at(i));
            }
        } else if (inp.at(i).find("humidity-to-location") != std::string::npos) {
            for (i++; i < inp.size() && inp.at(i) != ""; i++) {
                humidity_to_location.add_range(inp.at(i));
            }
        }
    }
    humidity_to_location.print();

    auto total_map_inv = [&](int64_t location) {
        return seed_to_soil.inv(soil_to_fertilizer.inv(fertilizer_to_water.inv(water_to_light.inv(
            light_to_temperature.inv(temperature_to_humidity.inv(humidity_to_location.inv(location)))))));
    };

    int64_t min = 0;
    // TODO: Calculate the next step in order for the mapping to move into
    // another range along the way, figure out a way to do so and use that as
    // the next step instead of i++
    for (int64_t i = 0; i < 1'000'000'000; i++) {
        if (seeds.in_range(total_map_inv(i))) {
            min = i;
            break;
        }
    }

    return min;
}
