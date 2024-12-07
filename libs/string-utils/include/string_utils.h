#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <cstdint>
#include <string>
#include <vector>

namespace string_utils {

std::vector<std::string> split_string(std::string str, char delim);

// TODO: Generalize as template
std::vector<int64_t> numbers_from_string(std::string str);

}  // namespace string_utils

#endif
