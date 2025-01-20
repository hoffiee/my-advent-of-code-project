#ifndef LIB_2019_INTCODE_COMPUTER_H_
#define LIB_2019_INTCODE_COMPUTER_H_

#include <string>
#include <unordered_map>
#include <vector>

namespace aoc {
namespace y2019 {

class IntcodeComputer {
   public:
    std::vector<int64_t> output_{};
    std::vector<int64_t> input_{};

    IntcodeComputer(std::vector<int64_t> const& program);
    int64_t exec();
    void print() const;
    void set_input(int64_t inp);

   private:
    std::size_t memory_size_{};
    int64_t relative_base_{0};
    std::size_t ip_{0};
    std::unordered_map<std::size_t, int64_t> registers_{};

    int64_t& get_parameter(int64_t& value, int64_t mode);
};

};  // namespace y2019
};  // namespace aoc

#endif
