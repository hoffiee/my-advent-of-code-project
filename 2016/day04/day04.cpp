#include AOC_HEADER

#include <algorithm>
#include <sstream>
#include <unordered_map>

static std::string calculate_checksum(std::string& name) {
    std::unordered_map<char, int> content;
    for (auto ch : name) {
        if (ch == '-') {
            continue;
        }
        ++content[ch];
    }

    std::vector<std::pair<int, char>> sorted_content;
    for (auto& it : content) {
        sorted_content.emplace_back(it.second, it.first);
    }

    auto cmp = [](std::pair<int, char> const& a, std::pair<int, char> const& b) {
        return a.first != b.first ? a.first > b.first : a.second < b.second;
    };
    std::sort(sorted_content.begin(), sorted_content.end(), cmp);

    std::string calc_checksum = "[";
    for (auto& it : sorted_content) {
        calc_checksum.push_back(it.second);
        if (calc_checksum.size() >= 6) {
            break;
        }
    }
    calc_checksum.push_back(']');

    return calc_checksum;
}

void shift_cipher(std::string& input, int shift) {
    for (auto& ch : input) {
        if (ch == '-') {
            ch = ' ';
            continue;
        }
        ch = static_cast<char>(((ch - 'a') + shift) % 26 + 'a');
    }
}

std::pair<int, int> solve(std::vector<std::string>& input) {
    int count = 0;
    int nortphole_sector_id;
    for (auto room : input) {
        /* replace the last - to separate the name from sector id */
        auto n = room.rfind("-");
        room.at(n) = ' ';

        std::stringstream ss(room);
        std::string name_encrypted;
        int sector_id = 0;
        std::string checksum;

        ss >> name_encrypted >> sector_id >> checksum;

        auto calc_checksum = calculate_checksum(name_encrypted);
        if (calc_checksum == checksum) {
            count += sector_id;
            shift_cipher(name_encrypted, sector_id);
            if (name_encrypted.find("northpole") != std::string::npos) {
                nortphole_sector_id = sector_id;
            }
        }
    }

    return {count, nortphole_sector_id};
}
