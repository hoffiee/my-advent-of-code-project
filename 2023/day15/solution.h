#ifndef LIB_2021_DAY04_H_
#define LIB_2021_DAY04_H_

#include <string>
#include <vector>

int solve_1(std::vector<std::string> inp);
int solve_2(std::vector<std::string> inp);

namespace internal {

size_t hash(std::string inp);

}

#endif
