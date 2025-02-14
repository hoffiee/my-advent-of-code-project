#include AOC_HEADER

#include <algorithm>
#include <functional>
#include <numeric>

static int solve(std::vector<int>& masses, std::function<int(const int)> calculator) {
    std::vector<int> modules_fuel_need;
    std::transform(masses.cbegin(), masses.cend(), std::back_inserter(modules_fuel_need), calculator);
    return std::accumulate(modules_fuel_need.cbegin(), modules_fuel_need.cend(), 0);
}

int solve_1(std::vector<std::string> input) {
    std::vector<int> masses(input.size());
    std::transform(input.cbegin(), input.cend(), masses.begin(), [](std::string const& str) { return std::stoi(str); });
    std::function<int(const int)> calc_fuel = [](const int mass) { return mass / 3 - 2; };
    return solve(masses, calc_fuel);
}

int solve_2(std::vector<std::string> input) {
    std::vector<int> masses(input.size());
    std::transform(input.cbegin(), input.cend(), masses.begin(), [](std::string const& str) { return std::stoi(str); });
    std::function<int(const int)> calc_fuel = [&calc_fuel](const int mass) {
        int fuel = mass / 3 - 2;
        return (fuel > 0) ? fuel + calc_fuel(fuel) : 0;
    };
    return solve(masses, calc_fuel);
}
