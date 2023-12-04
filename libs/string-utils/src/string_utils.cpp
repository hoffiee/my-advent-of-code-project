#include "string_utils.h"

#include <sstream>

namespace string_utils {

std::vector<std::string> split_string(std::string str, char delim) {
    std::stringstream ss(str);
    std::string tmp;
    std::vector<std::string> out;
    while (getline(ss, tmp, delim)) {
        out.push_back(tmp);
    }
    return out;
}


}
