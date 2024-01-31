#ifndef LIB_2021_DAY04_H_
#define LIB_2021_DAY04_H_

#include <string>
#include <vector>

int solve_1(std::vector<std::string> inp);
int solve_2(std::vector<std::string> inp);


namespace internal {

std::vector<std::vector<bool>> possible_paths(std::vector<std::string>& map, ssize_t xs, ssize_t ys);
std::vector<std::vector<bool>> possible_directions(std::vector<std::string> map, ssize_t xs, ssize_t ys);


}

#endif
