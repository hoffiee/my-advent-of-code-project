#include "intcode_computer.h"

#include <cassert>
#include <icecream.hpp>
#include <iostream>

namespace aoc::y2019 {

IntcodeComputer::IntcodeComputer(std::vector<int64_t> const& program) : memory_size_{program.size()} {
    for (std::size_t i{0}; i < memory_size_; i++) {
        registers_[i] = program[i];
    }
}

// NOTE: Should probably figure out a better way to deal with access when writing to registers in mode 0,2
int64_t& IntcodeComputer::get_parameter(int64_t& value, int64_t mode) {
    switch (mode) {
        case 1: {
            return value;
        }
        case 2: {
            return registers_[value + relative_base_];
        }
    }
    return registers_[value];
}

int64_t IntcodeComputer::exec() {
    while (ip_ < memory_size_) {
        int64_t opcode{registers_[ip_] % 100};
        int64_t param1_mode{(registers_[ip_] / 100) % 10};
        int64_t param2_mode{(registers_[ip_] / 1000) % 10};
        int64_t param3_mode{(registers_[ip_] / 10000) % 10};
        assert(param3_mode != 1);
        switch (opcode) {
            case 1: {
                get_parameter(registers_[ip_ + 3], param3_mode) =
                    get_parameter(registers_[ip_ + 1], param1_mode) + get_parameter(registers_[ip_ + 2], param2_mode);
                ip_ += 4;
                break;
            }
            case 2: {
                get_parameter(registers_[ip_ + 3], param3_mode) =
                    get_parameter(registers_[ip_ + 1], param1_mode) * get_parameter(registers_[ip_ + 2], param2_mode);
                ip_ += 4;
                break;
            }
            case 3: {
                if (input_.empty()) {
                    return 0;
                }
                get_parameter(registers_[ip_ + 1], param1_mode) = input_.front();
                input_.erase(input_.begin());
                ip_ += 2;
                break;
            }
            case 4: {
                output_.push_back(get_parameter(registers_[ip_ + 1], param1_mode));
                // TODO: run in debug mode
                // std::cerr << "output_: " << output_ << std::endl;
                ip_ += 2;
                break;
            }
            case 5: {
                if (get_parameter(registers_[ip_ + 1], param1_mode) != 0) {
                    ip_ = get_parameter(registers_[ip_ + 2], param2_mode);
                    break;
                }
                ip_ += 3;
                break;
            }
            case 6: {
                if (get_parameter(registers_[ip_ + 1], param1_mode) == 0) {
                    ip_ = get_parameter(registers_[ip_ + 2], param2_mode);
                    break;
                }
                ip_ += 3;
                break;
            }
            case 7: {
                get_parameter(registers_[ip_ + 3], param3_mode) =
                    (get_parameter(registers_[ip_ + 1], param1_mode) < get_parameter(registers_[ip_ + 2], param2_mode));
                ip_ += 4;
                break;
            }
            case 8: {
                get_parameter(registers_[ip_ + 3], param3_mode) = (get_parameter(registers_[ip_ + 1], param1_mode) ==
                                                                   get_parameter(registers_[ip_ + 2], param2_mode));
                ip_ += 4;
                break;
            }
            case 9: {
                relative_base_ += get_parameter(registers_[ip_ + 1], param1_mode);
                ip_ += 2;
                break;
            }
            case 99: {
                ip_ = memory_size_;
                break;
            }
            default: {
                IC(registers_[ip_]);
                assert(false);
                break;
            }
        }
    }

    // TODO: Run this in debug mode
    // validate positive idx
    // for (auto const& [key, _] : registers_) {
    //     assert(key >= 0);
    // }

    return registers_[0];
}

void IntcodeComputer::set_input(int64_t inp) { input_.push_back(inp); }

void IntcodeComputer::print() const {
    for (std::size_t i{0}; i < memory_size_; i++) {
        std::cout << registers_.at(i) << ",";
    }
    std::cout << std::endl;
}

};  // namespace aoc::y2019
