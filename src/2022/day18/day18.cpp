/* Current brute force for part 2, currently took 277 days when I calculated
 * it, so scrap that. Search space is too large */
#include <chrono>
#include <fstream>
#include <iostream>

/* Solution includes */
#include <algorithm>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace {
using std::cout;
using std::endl;
using std::string;
using std::vector;
using scans = vector<std::tuple<int, int, int>>;
}  // namespace

static scans read_and_parse_data(string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "couldn't read file" << std::endl;
        return {};
    }
    string line;
    scans out;
    while (getline(input, line)) {
        std::stringstream ss(line);
        char delim;
        int x;
        int y;
        int z;
        ss >> x >> delim >> y >> delim >> z;
        out.push_back(std::make_tuple(x, y, z));
    }
    return out;
}

struct Cube {
    int x = 0;
    int y = 0;
    int z = 0;
    vector<Cube*> adjacent;

    bool operator==(const Cube& c) const { return (x == c.x) && (y == c.y) && (z == c.z); }

    friend std::ostream& operator<<(std::ostream& os, Cube& cube) {
        os << "(" << cube.x << "," << cube.y << "," << cube.z << "):" << cube.adjacent.size();
        return os;
    }
};

struct hash_fn {
    std::size_t operator()(const Cube& cube) const {
        std::size_t h1 = std::hash<int>()(cube.x);
        std::size_t h2 = std::hash<int>()(cube.y);
        std::size_t h3 = std::hash<int>()(cube.z);

        return h1 ^ h2 ^ h3;
    }
};

static void check_and_add_adjacent(std::unordered_map<Cube, Cube, hash_fn>& grid, Cube& c, int x, int y, int z) {
    Cube cand{x, y, z};
    if (grid.find(cand) == grid.end() || cand == c) {
        /* If there's nothing here, go to the next */
        /* Skip itself */
        return;
    }
    // cout << "(" << x << "," << y << "," << z << "), ";

    grid[c].adjacent.push_back(&grid[cand]);
}

static int solution_1(scans scan) {
    // cout << endl;
    int xmin = 0;
    int ymin = 0;
    int zmin = 0;
    int xmax = 0;
    int ymax = 0;
    int zmax = 0;

    // std::sort(scan.begin(), scan.end(), [](const std::tuple<int, int, int>
    // lhs, const std::tuple<int, int, int> rhs){
    //         int lhs_z = std::get<2>(lhs);
    //         int rhs_z = std::get<2>(rhs);
    //         return lhs_z < rhs_z;
    // });

    std::unordered_map<Cube, Cube, hash_fn> grid;
    for (auto& point : scan) {
        auto [x, y, z] = point;
        // cout << x << " " << y << " " << z << endl;

        xmin = std::min(x, xmin);
        ymin = std::min(y, ymin);
        zmin = std::min(z, zmin);
        xmax = std::max(x, xmax);
        ymax = std::max(y, ymax);
        zmax = std::max(z, zmax);

        Cube c{x, y, z};
        if (grid.find(c) != grid.end()) {
            throw std::logic_error("Something's wrong here, cube shouldn't exist here!");
        }
        grid[c] = c;
    }

    // cout << endl;
    for (auto& point : scan) {
        auto [x, y, z] = point;
        // cout << x << " " << y << " " << z << endl;

        Cube c{x, y, z};
        if (grid.find(c) == grid.end()) {
            throw std::logic_error("Something's wrong here, cube should exist!");
        }

        // cout << "adjacent\n\t";
        for (int xi = std::max(xmin, x - 1); xi <= std::min(xmax, x + 1); ++xi) {
            check_and_add_adjacent(grid, c, xi, y, z);
        }
        for (int yi = std::max(ymin, y - 1); yi <= std::min(ymax, y + 1); ++yi) {
            check_and_add_adjacent(grid, c, x, yi, z);
        }
        for (int zi = std::max(zmin, z - 1); zi <= std::min(zmax, z + 1); ++zi) {
            check_and_add_adjacent(grid, c, x, y, zi);
        }
        // cout << endl;
    }
    // cout << xmax << " " << ymax << " " << zmax << endl;

    // for (auto& it: grid) {
    //     cout << it.second << endl;
    // }

    auto addition = [](int a, const std::pair<Cube, Cube>& cube) { return a + 6 - cube.second.adjacent.size(); };

    return std::accumulate(grid.begin(), grid.end(), 0, addition);
}

static int solution_2(scans scan) {
    cout << endl;
    int xmin = 0;
    int ymin = 0;
    int zmin = 0;
    int xmax = 0;
    int ymax = 0;
    int zmax = 0;

    // std::sort(scan.begin(), scan.end(), [](const std::tuple<int, int, int>
    // lhs, const std::tuple<int, int, int> rhs){
    //         int lhs_z = std::get<2>(lhs);
    //         int rhs_z = std::get<2>(rhs);
    //         return lhs_z < rhs_z;
    // });

    std::unordered_map<Cube, Cube, hash_fn> grid;
    for (auto& point : scan) {
        auto [x, y, z] = point;

        xmin = std::min(x, xmin);
        ymin = std::min(y, ymin);
        zmin = std::min(z, zmin);
        xmax = std::max(x, xmax);
        ymax = std::max(y, ymax);
        zmax = std::max(z, zmax);

        Cube c{x, y, z};
        if (grid.find(c) != grid.end()) {
            throw std::logic_error("Something's wrong here, cube shouldn't exist here!");
        }
        grid[c] = c;
    }
    cout << xmin << " " << xmax << " " << ymin << " " << ymax << " " << zmin << " " << zmax << " " << endl;

    int count = 0;

    /* Part 2: This does the assumption that the exterior is simple, does not
     * take the following into account
     *     _   _
     *   _| |_| |_
     *      ^ ^
     * this has 8 edges, my algorithm will miss the two inner edges that I have
     * marked with ^  when viewed from the side.
     *
     * Scrap this.
     */
    for (int y = ymin; y <= ymax; ++y) {
        for (int z = zmin; z <= zmax; ++z) {
            Cube cand{xmin, y, z};
            for (int xlow = xmin; xlow <= xmax; ++xlow) {
                cand.x = xlow;
                if (grid.find(cand) != grid.end()) {
                    ++count;
                    break;
                }
            }
            for (int xhigh = xmax; xhigh >= xmin; --xhigh) {
                cand.x = xhigh;
                if (grid.find(cand) != grid.end()) {
                    ++count;
                    break;
                }
            }
        }
    }
    cout << "x" << count << endl;

    for (int x = xmin; x <= xmax; ++x) {
        for (int z = zmin; z <= zmax; ++z) {
            Cube cand{x, ymin, z};
            for (int ylow = ymin; ylow <= ymax; ++ylow) {
                cand.y = ylow;
                if (grid.find(cand) != grid.end()) {
                    ++count;
                    break;
                }
            }
            for (int yhigh = ymax; yhigh >= ymin; --yhigh) {
                cand.y = yhigh;
                if (grid.find(cand) != grid.end()) {
                    ++count;
                    break;
                }
            }
        }
    }
    cout << "y" << count << endl;

    for (int y = ymin; y <= ymax; ++y) {
        for (int x = xmin; x <= xmax; ++x) {
            Cube cand{x, y, zmin};
            for (int zlow = zmin; zlow <= zmax; ++zlow) {
                cand.z = zlow;
                if (grid.find(cand) != grid.end()) {
                    ++count;
                    break;
                }
            }
            for (int zhigh = zmax; zhigh >= zmin; --zhigh) {
                cand.z = zhigh;
                if (grid.find(cand) != grid.end()) {
                    ++count;
                    break;
                }
            }
        }
    }
    cout << "z" << count << endl;

    return count;
}

static void run_and_check_solutions(string task, int (*solution_1)(scans), int expected_1, int (*solution_2)(scans),
                                    int expected_2) {
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

int main(void) {
    auto solution_1_sample = [](scans in) { return solution_1(in); };
    auto solution_2_sample = [](scans in) { return solution_2(in); };
    run_and_check_solutions("day18-sample.input", solution_1_sample, 64, solution_2_sample, 58);

    auto solution_1_puzzle = [](scans in) { return solution_1(in); };
    auto solution_2_puzzle = [](scans in) { return solution_2(in); };
    run_and_check_solutions("day18.input", solution_1_puzzle, 3500, solution_2_puzzle, 0);
}
