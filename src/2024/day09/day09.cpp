/**
 * https://adventofcode.com/2024/day/9
 *
 * Not happy with this; this is quite naive in it's approach and I'm all over the place with the solution for part 1 and
 * part 2, this can be optimized quite a bit..
 */
#include <cstdint>
#include <icecream.hpp>
#include <string>
#include <vector>

#include "string_utils.h"

struct Block {
    enum struct Type : int32_t {
        invalid,
        free,
        file,
    };
    Type type_{Type::invalid};
    int64_t size_{0};
    int64_t id_{-1};

    Block(Type type, int64_t size, int64_t id) : type_{type}, size_{size}, id_{id} {};

    friend std::ostream& operator<<(std::ostream& stream, Block const& block) {
        std::string out{};
        switch (block.type_) {
            case Block::Type::invalid: {
                out = "inv";
                break;
            }
            case Block::Type::free: {
                out = "free| " + std::to_string(block.size_);
                break;
            }
            case Block::Type::file: {
                out = "file| " + std::to_string(block.id_) + ":" + std::to_string(block.size_);
                break;
            }
        }
        stream << out;
        return stream;
    }
};

Block create_file(int64_t id, int64_t size = 1) { return Block(Block::Type::file, size, id); }

Block create_free_space(int64_t size) { return Block(Block::Type::free, size, -1); }

struct Disk {
    std::vector<Block> memory_{};
    std::unordered_map<int64_t, int64_t> size_count_{};

    Disk(std::string inp, bool single_block_file = true) {
        int64_t id{0};
        bool file{true};
        for (auto memory_length : inp) {
            int64_t size{memory_length - '0'};
            if (file) {
                if (single_block_file) {
                    for (int64_t i = 0; i < size; i++) {
                        memory_.push_back(create_file(id));
                    }
                } else {
                    memory_.emplace_back(create_file(id, size));
                }
                file = false;
                id++;
            } else {
                file = true;
                if (size == 0) {
                    continue;
                }
                memory_.push_back(create_free_space(size));
                size_count_[size]++;
            }
        }
    }

    bool available_space(int64_t size) const {
        for (auto const [key, val] : size_count_) {
            if (key >= size && val > 0) {
                return true;
            }
        }
        return false;
    }

    int64_t calculate_checksum() const {
        int64_t pos{0};
        int64_t sum{0};
        for (auto const& it : memory_) {
            if (it.type_ == Block::Type::free) {
                pos += it.size_;
                continue;
            }
            // partial sum of a series
            sum += it.id_ * it.size_ * (2 * pos + it.size_ - 1) / 2;
            pos += it.size_;
        }
        return sum;
    }

    std::vector<Block>::reverse_iterator find_last_file() {
        return std::find_if(memory_.rbegin(), memory_.rend(),
                            [](auto const& b) { return b.type_ == Block::Type::file; });
    }

    void print() {
        for (auto const& block : memory_) {
            for (int64_t i = 0; i < block.size_; i++) {
                switch (block.type_) {
                    case Block::Type::free:
                        std::cout << ".";
                        break;
                    case Block::Type::file:
                        std::cout << block.id_;
                        break;
                    default:
                        break;
                }
            }
        }
        std::cout << std::endl;
    }
};

int64_t solve_1(std::vector<std::string> inp) {
    Disk disk(inp[0]);

    for (auto it{disk.memory_.begin()}; it != disk.memory_.end(); it++) {
        if (it->type_ == Block::Type::file) {
            continue;
        }

        auto last_file = disk.find_last_file();
        if (last_file.base() < it) {
            break;
        }

        for (int64_t i{0}; i < it->size_; i++) {
            disk.memory_.insert(it, create_file(last_file->id_));
            disk.memory_.erase(last_file.base());
            it++;
            last_file = disk.find_last_file();
        }
        disk.memory_.erase(it);
    }
    return disk.calculate_checksum();
}

int64_t solve_2(std::vector<std::string> inp) {
    Disk disk(inp[0], false);

    auto free_available_it = std::next(disk.memory_.begin());
    static_cast<void>(free_available_it);

    for (auto it{std::prev(disk.memory_.end())}; it != disk.memory_.begin(); it--) {
        if (it->type_ == Block::Type::free || !disk.available_space(it->size_)) {
            continue;
        }

        // Find first free with sufficient space
        auto free_it{disk.memory_.begin()};
        for (; free_it != disk.memory_.end(); free_it++) {
            if (free_it->type_ != Block::Type::free) {
                continue;
            }
            if (free_it->size_ >= it->size_ || free_it >= it) {
                break;
            }
        }

        if (free_it > it) {
            // no free space found
            continue;
        }

        if (it->size_ == free_it->size_) {
            *free_it = *it;
            *it = create_free_space(free_it->size_);
            disk.size_count_[it->size_]--;
        } else {
            disk.size_count_[free_it->size_]--;
            free_it->size_ -= it->size_;
            disk.size_count_[free_it->size_]++;
            disk.memory_.insert(free_it, *it);
            it++;
            *it = create_free_space(free_it->size_);
        }
    }
    return disk.calculate_checksum();
}

int main() {
    auto sample1 = string_utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample1) == 1928);
    assert(solve_2(sample1) == 2858);

    auto input = string_utils::read_input(AOC_INPUT);
    auto part1 = solve_1(input);
    auto part2 = solve_2(input);

    std::cout << "output:" << std::endl;
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

    return 0;
}
