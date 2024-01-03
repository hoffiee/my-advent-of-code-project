/**
 * https://adventofcode.com/2023/day/24
 */
#include AOC_HEADER

#include <string_utils.h>

#include <icecream.hpp>
#include <sstream>
#include <cstdint>
#include <Eigen/Dense>

struct Vec3 {
    int64_t x;
    int64_t y;
    int64_t z;
    Vec3(int64_t x, int64_t y, int64_t z): x(x), y(y), z(z) {};
    friend std::ostream& operator<<(std::ostream& os, const Vec3& obj);
};

std::ostream& operator<<(std::ostream& os, const Vec3& obj) {
    os << "[" << obj.x << "," << obj.y << "," << obj.z << "]";
    return os;
}

struct Line {
    Vec3 pos;
    Vec3 vel;
    Line(Vec3 pos, Vec3 vel): pos(pos), vel(vel) {};
    friend std::ostream& operator<<(std::ostream& os, const Line& obj);
};

std::ostream& operator<<(std::ostream& os, const Line& obj) {
    os << "pos: " << obj.pos << ", vel: " << obj.vel;
    return os;
}

static std::vector<Line> parse_input(std::vector<std::string>& inp) {
    std::vector<Line> lines;
    lines.reserve(inp.size());
    for (auto& entry: inp) {
        auto data = string_utils::split_string(entry, '@');

        int64_t x = 0;
        int64_t y = 0;
        int64_t z = 0;
        char ign;
        {
            std::stringstream ss(data.at(0));
            ss >> x >> ign >> y >> ign >> z;
        }
        Vec3 pos(x, y, z);
        {
            std::stringstream ss(data.at(1));
            ss >> x >> ign >> y >> ign >> z;
        }
        Vec3 vel(x, y, z);

        lines.emplace_back(Line{pos, vel});
    }
    return lines;
}

static bool check_intersection(const Line& lhs, const Line& rhs, int64_t min, int64_t max) {
    // Check that we have full rank, if not they're parallel
    double vx1 = static_cast<double>(lhs.vel.x);
    double vy1 = static_cast<double>(lhs.vel.y);
    double vx2 = static_cast<double>(rhs.vel.x);
    double vy2 = static_cast<double>(rhs.vel.y);

    if (vy1*vx2 - vx1*vy2 == 0) {
        return false;
    }

    double x1 = static_cast<double>(lhs.pos.x);
    double y1 = static_cast<double>(lhs.pos.y);
    double x2 = static_cast<double>(rhs.pos.x);
    double y2 = static_cast<double>(rhs.pos.y);

    // This is generated in calc1.jl
    double t1 = (x2 + (vx2*(y2 + (-vy1*(x2 - x1)) / vx1 - y1)) / ((vx2*vy1) / vx1 - vy2) - x1) / vx1;
    double t2 = (y2 + (-vy1*(x2 - x1)) / vx1 - y1) / ((vx2*vy1) / vx1 - vy2);

    // collisions in the past does not count
    if (t1 < 0 || t2 < 0) {
        return false;
    }

    // Calculate collision position
    int64_t px_col = static_cast<int64_t>(x1 + vx1*t1);
    int64_t py_col = static_cast<int64_t>(y1 + vy1*t1);

    // Check within test area
    if (min <= px_col && px_col <= max && min <= py_col && py_col <= max) {
        return true;
    }
    return false;
}

int solve_1(std::vector<std::string> inp, int64_t min, int64_t max) {
    auto lines = parse_input(inp);
    int count = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = i + 1; j < lines.size(); j++) {
            if (check_intersection(lines.at(i), lines.at(j), min, max)) {
                count++;
            }
        }
    }
    return count;
}

int64_t solve_2(std::vector<std::string> inp) {
    auto lines = parse_input(inp);

    // Since using different lines from the set gives different results, let's take an offset
    size_t offset = inp.size() / 4;

    double A_x = static_cast<double>(lines.at(offset).pos.x);
    double A_y = static_cast<double>(lines.at(offset).pos.y);
    double A_z = static_cast<double>(lines.at(offset).pos.z);
    double Avx = static_cast<double>(lines.at(offset).vel.x);
    double Avy = static_cast<double>(lines.at(offset).vel.y);
    double Avz = static_cast<double>(lines.at(offset).vel.z);

    double B_x = static_cast<double>(lines.at(lines.size() / 2).pos.x);
    double B_y = static_cast<double>(lines.at(lines.size() / 2).pos.y);
    double B_z = static_cast<double>(lines.at(lines.size() / 2).pos.z);
    double Bvx = static_cast<double>(lines.at(lines.size() / 2).vel.x);
    double Bvy = static_cast<double>(lines.at(lines.size() / 2).vel.y);
    double Bvz = static_cast<double>(lines.at(lines.size() / 2).vel.z);

    double C_x = static_cast<double>(lines.at(lines.size() - offset).pos.x);
    double C_y = static_cast<double>(lines.at(lines.size() - offset).pos.y);
    double C_z = static_cast<double>(lines.at(lines.size() - offset).pos.z);
    double Cvx = static_cast<double>(lines.at(lines.size() - offset).vel.x);
    double Cvy = static_cast<double>(lines.at(lines.size() - offset).vel.y);
    double Cvz = static_cast<double>(lines.at(lines.size() - offset).vel.z);

    // This is copied from jupyter notebook
    Eigen::Matrix<double, 6, 6> A;
    Eigen::Matrix<double, 6, 1> b;

    A << Avy - Bvy, -Avx + Bvx, 0, -A_y + B_y, A_x - B_x, 0,
         Avy - Cvy, -Avx + Cvx, 0, -A_y + C_y, A_x - C_x, 0,
         Avz - Bvz, 0, -Avx + Bvx, -A_z + B_z, 0, A_x - B_x,
         Avz - Cvz, 0, -Avx + Cvx, -A_z + C_z, 0, A_x - C_x,
         0, Avz - Bvz, -Avy + Bvy, 0, -A_z + B_z, A_y - B_y,
         0, Avz - Cvz, -Avy + Cvy, 0, -A_z + C_z, A_y - C_y;

    b << A_x*Avy - A_y*Avx - B_x*Bvy + B_y*Bvx,
         A_x*Avy - A_y*Avx - C_x*Cvy + C_y*Cvx,
         A_x*Avz - A_z*Avx - B_x*Bvz + B_z*Bvx,
         A_x*Avz - A_z*Avx - C_x*Cvz + C_z*Cvx,
         A_y*Avz - A_z*Avy - B_y*Bvz + B_z*Bvy,
         A_y*Avz - A_z*Avy - C_y*Cvz + C_z*Cvy;

    // Solve Ax=b with a QR decomposition
    // https://eigen.tuxfamily.org/dox/group__LeastSquares.html
    Eigen::Matrix<double, 6, 1> x;
    x << A.colPivHouseholderQr().solve(b);

    // Index 0-2 is xyz positions
    return static_cast<int64_t>(std::round(x[0]) + std::round(x[1]) + std::round(x[2]));
}
