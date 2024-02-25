#include "string_utils.h"

#include <cctype>
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

std::vector<int> numbers_from_string(std::string str) {
    std::string tmp{};
    std::vector<int> out{};

    for (size_t i = 0; i < str.size(); i++) {
        if (std::isdigit(static_cast<unsigned char>(str[i]))) {
            tmp += str[i];
            continue;
        }

        if (tmp.empty()) {
            continue;
        }

        out.emplace_back(std::stoi(tmp));
        tmp.clear();
    }

    // If string is empty we had something in the end that we never cleared out
    // add that to output before we return
    if (!tmp.empty()) {
        out.emplace_back(std::stoi(tmp));
    }

    return out;
}

}  // namespace string_utils
