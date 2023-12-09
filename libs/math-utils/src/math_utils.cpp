#include "math_utils.h"

#include <cassert>
#include <numeric>

namespace math_utils {

int64_t lcm(std::vector<int64_t> vec) {
    assert(vec.size() >= 2);

    int64_t res = vec.at(0);
    for (size_t i = 1; i < vec.size(); i++) {
        res = ((vec[i] * res)) / (std::gcd(vec[i], res));
    }
    return res;
}

}  // namespace math_utils
