#ifndef LIB_2021_DAY04_H_
#define LIB_2021_DAY04_H_

#include <string>
#include <vector>

int solve_1(std::vector<std::string> inp);
int64_t solve_2(std::vector<std::string> inp);

namespace internal {

int64_t solve_factor(std::vector<std::string> inp, int factor);

}

#endif
