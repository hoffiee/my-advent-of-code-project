/**
 * 997851 - not correct, it's to low
 * 1444896 - Correct!, damn had to look up how to deal with shared_pointers..
 * 30108156 - too high
 *
 * part 2
 *
 * 404395 - correct! Wooohoo!
 * 40389918 -- too high, it's the root size..
 *
 * This was a really fun task! But boy did it require a lot of thinking and
 * searching for help. I think it would have been easier to do in C for me
 * since I know pointers pretty well, but to use C++ containers and iterators
 * and so on made it quite hard but also fun. Really liked this one
 */
#include AOC_HEADER

#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>

struct File {
    std::string _name;
    int64_t _size;
    File(std::string name, int64_t size) : _name(name), _size(size) {}
    int64_t size() const;
};

struct Dir {
    std::string _name;
    Dir* _parent = nullptr;
    std::unordered_map<std::string, Dir*> subdirs;
    std::unordered_map<std::string, File> files;

    Dir(std::string name) : _name(name), _parent(nullptr) {}
    Dir(std::string name, Dir* parent) : _name(name), _parent(parent) {}

    int64_t size();
    void insert(File& file);
    void insert(Dir* dir);
    void print(int64_t padding);
};

struct Filesystem {
    Dir* root;
    Dir* _current_dir = nullptr;
    /* The amount of time it took to me to be able to use this structure and
     * allow the pointers to be used was a bit embarassing, but it works now
     * after a lot of digging around! look into the mkdir method to see how
     * it's been given out to others */
    std::vector<std::unique_ptr<Dir>> dirs;

    void print();
    void mkdir(std::string& name);
    void cd(std::string tar);
    void insert(File& file);
};

int64_t File::size() const { return _size; }

int64_t Dir::size() {
    /* TODO: cache this? */
    // int64_t _cached_size;
    int64_t out = std::accumulate(subdirs.cbegin(), subdirs.cend(), static_cast<int64_t>(0), [](int64_t acc, auto& it) {
        if (it.first == "/") {
            return acc + static_cast<int64_t>(0);
        }
        return acc + it.second->size();
    });
    out += std::accumulate(files.cbegin(), files.cend(), static_cast<int64_t>(0),
                           [](int64_t acc, const auto& it) { return acc + it.second.size(); });
    return out;
}

void Dir::insert(File& file) { files.insert_or_assign(file._name, std::move(file)); }

void Dir::insert(Dir* dir) {
    subdirs.insert_or_assign(dir->_name, dir);
    // dirs.emplace(dir->_name, dir);
}

void Dir::print(int64_t padding) {
    for (int64_t i = 0; i < padding; ++i) {
        std::cout << "  ";
    }
    std::cout << _name << std::endl;

    for (auto& it : files) {
        for (int64_t i = 0; i < 2 * padding; ++i) {
            std::cout << "  ";
        }
        std::cout << it.second._size << " " << it.first << std::endl;
    }

    for (auto& it : subdirs) {
        if (it.first == "/") {
            continue;
        }
        it.second->print(padding + 1);
    }
}

void Filesystem::mkdir(std::string& name) {
    auto& new_dir = dirs.emplace_back(std::make_unique<Dir>(name, _current_dir));
    if (_current_dir == nullptr) {
        _current_dir = new_dir.get();
    }
    _current_dir->subdirs[name] = new_dir.get();
}

void Filesystem::cd(std::string tar) {
    /* TODO Refactor this */
    if (tar == ".") {
        return;
    }

    if (tar == "..") {
        if (_current_dir == nullptr && _current_dir->_parent == nullptr) {
            return;
        }
        _current_dir = _current_dir->_parent;
        return;
    }

    if (_current_dir == nullptr || !_current_dir->subdirs.contains(tar)) {
        /* create it first */
        mkdir(tar);
    }
    _current_dir = _current_dir->subdirs.at(tar);
}

void Filesystem::print() { dirs.at(0)->print(1); }

void Filesystem::insert(File& file) { _current_dir->insert(file); }

std::pair<int64_t, int64_t> solve(std::vector<std::string>& input) {
    Filesystem fs;
    for (auto& it : input) {
        if (it.at(0) == '$') {
            std::string cmd;
            std::string tar;
            std::stringstream ss(it.substr(2));
            ss >> cmd >> tar;
            if (tar.empty()) {
                continue;
            }
            fs.cd(tar);
        } else {
            if (it.at(0) == 'd') {
                continue;
            }
            std::stringstream ss(it);
            int64_t size = 0;
            std::string name;
            ss >> size >> name;
            File file(name, size);
            fs.insert(file);
        }
    }

    int64_t sum = 0;
    for (auto& it : fs.dirs) {
        int64_t size = it->size();
        if (size <= 100000) {
            sum += size;
        }
    }

    int64_t used_space = fs.dirs.at(0)->size();
    int64_t needed_space = 30000000 - (70000000 - used_space);
    int64_t min = INT64_MAX;
    for (auto& it : fs.dirs) {
        int64_t size = it->size();
        if (size >= needed_space && size < min) {
            min = size;
        }
    }

    return {sum, min};
}
