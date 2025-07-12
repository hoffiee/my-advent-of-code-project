/**
 * https://adventofcode.com/2023/day/20
 */

#include <fstream>
#include <icecream.hpp>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "aoc_runner.h"
#include "aoc_utils.h"

namespace aoc::y2023::d20 {

enum class Pulse : std::int8_t {
    Low,
    High,
};

std::ostream& operator<<(std::ostream& os, Pulse const& m) {
    switch (m) {
        case Pulse::Low: {
            os << " -low-> ";
            break;
        }
        case Pulse::High: {
            os << " -high-> ";
            break;
        }
        default: {
            assert(false);
            break;
        }
    }
    return os;
}

struct Event {
    std::string src{};
    Pulse pulse{};
    std::string dst{};

    friend std::ostream& operator<<(std::ostream& os, Event const& m) {
        os << m.src << m.pulse << m.dst;
        return os;
    }
};

struct Counter {
    std::uint64_t counter_high_{0};
    std::uint64_t counter_low_{0};

    Counter() = default;

    void count(Event const event) {
        switch (event.pulse) {
            case Pulse::Low: {
                counter_low_++;
                break;
            }
            case Pulse::High: {
                counter_high_++;
                break;
            }
            default: {
                assert(false);
                break;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Counter const& m) {
        os << "low: " << m.counter_low_ << ", ";
        os << "high: " << m.counter_high_ << ", ";
        return os;
    }
};

struct Module {
    std::string const name_{};
    std::vector<std::string> subscribers_{};
    std::unordered_map<std::string, Pulse> inputs_{};
    bool conjunction_{false};

    Module(std::string const& name) : name_{name} {}

    void subscribe(std::string const& name) { subscribers_.emplace_back(name); }

    virtual void register_input(std::string const& name) {}

    virtual std::vector<Event> step(Event const event) = 0;

    friend std::ostream& operator<<(std::ostream& os, Module const& m) {
        os << "name: " << m.name_ << ", ";
        os << "conj: " << m.conjunction_ << ", ";
        os << "inputs: [";
        for (auto const& [input, _] : m.inputs_) {
            os << input << ",";
        }
        os << "] ";
        os << "subs: [";
        for (auto const& sub : m.subscribers_) {
            os << sub << ",";
        }
        os << "]";
        return os;
    }
};

struct BroadcastModule : public Module {
    BroadcastModule(std::string const& name) : Module(name) {}

    std::vector<Event> step(Event const event) override {
        std::vector<Event> events_out{};
        for (auto const& sub : subscribers_) {
            events_out.emplace_back(Event{name_, event.pulse, sub});
        }
        return events_out;
    }
};

struct FlipFlopModule : public Module {
    bool state_{false};

    FlipFlopModule(std::string const& name) : Module(name) {}

    std::vector<Event> step(Event const event) override {
        switch (event.pulse) {
            case Pulse::Low: {
                state_ = !state_;
                break;
            }
            case Pulse::High: {
                // Do nothing and return
                return {};
                break;
            }
            default: {
                assert(false);
                break;
            }
        }

        Pulse signal_out{state_ ? Pulse::High : Pulse::Low};
        std::vector<Event> events_out{};
        for (auto const& sub : subscribers_) {
            events_out.emplace_back(Event{name_, signal_out, sub});
        }
        return events_out;
    }
};

struct ConjunctionModule : public Module {
    Pulse prev_pulse_{Pulse::Low};
    ConjunctionModule(std::string const& name) : Module(name) { conjunction_ = true; }

    void register_input(std::string const& name) override { inputs_[name] = Pulse::Low; }

    std::vector<Event> step(Event const event) override {
        if (!inputs_.contains(event.src)) {
            std::cout << "inputs_ does not have a key for " << event.src << std::endl;
            assert(false);
        }
        inputs_.at(event.src) = event.pulse;

        bool send_low_pulse{true};
        for (auto const& [input, pulse] : inputs_) {
            if (pulse == Pulse::Low) {
                send_low_pulse = false;
                break;
            }
        }

        Pulse output{send_low_pulse ? Pulse::Low : Pulse::High};
        std::vector<Event> events_out{};
        for (auto const& sub : subscribers_) {
            events_out.emplace_back(Event{name_, output, sub});
        }
        return events_out;
    }
};

using Modules = std::unordered_map<std::string, std::unique_ptr<Module>>;

Modules create_modules(std::vector<std::string> const& inp) {
    Modules modules{};

    for (auto const& line : inp) {
        auto items = aoc::string::split(line, ' ');
        std::string name{items[0].cbegin() + 1, items[0].cend()};
        switch (items.at(0).at(0)) {
            // boardcaster
            case 'b': {
                modules["broadcaster"] = std::make_unique<BroadcastModule>(items.at(0));
                break;
            }
            // Flip Flop module
            case '%': {
                modules[name] = std::make_unique<FlipFlopModule>(name);
                break;
            }
            case '&': {
                modules[name] = std::make_unique<ConjunctionModule>(name);
                break;
            }
            default: {
                assert(false);
                break;
            }
        }
    }

    for (auto const& line : inp) {
        auto items = aoc::string::split(line, ' ');
        std::string src{items[0].cbegin() + 1, items[0].cend()};
        switch (items.at(0).at(0)) {
            // boardcaster
            case 'b': {
                src = "broadcaster";
                break;
            }
            case '%':
            case '&': {
                break;
            }
            default: {
                assert(false);
                break;
            }
        }

        for (std::size_t i{2}; i < items.size(); i++) {
            std::string dst = items.at(i);
            dst.erase(std::remove_if(dst.begin(), dst.end(), [](auto const chr) { return chr == ','; }), dst.end());

            if (!modules.contains(src)) {
                std::cout << "modules doesn't contain: " << src << std::endl;
                assert(false);
            }

            modules.at(src)->subscribe(dst);

            // If output sink, add
            if (!modules.contains(dst)) {
                modules[dst] = std::make_unique<FlipFlopModule>(dst);
            }
            if (modules.at(dst)->conjunction_) {
                if (!modules.contains(dst)) {
                    std::cout << "modules doesn't contain: " << dst << std::endl;
                    assert(false);
                }
                modules.at(dst)->register_input(src);
            }
        }
    }

    return modules;
}

int64_t solve_1(std::vector<std::string> inp) {
    auto modules = create_modules(inp);
    Counter counter{};
    std::queue<Event> queue{};
    for (std::size_t i{0}; i < 1000u; i++) {
        queue.push(Event{"aptly", Pulse::Low, "broadcaster"});

        while (!queue.empty()) {
            auto const event = queue.front();

            counter.count(event);
            queue.pop();

            auto const new_events = modules[event.dst]->step(event);

            // IC(event, new_events);
            for (auto const& new_event : new_events) {
                queue.push(new_event);
            }
        }
    }
    return counter.counter_low_ * counter.counter_high_;
}

int64_t solve_2(std::vector<std::string> inp) {
    std::ofstream f("output.dot");
    f << "digraph {" << std::endl;
    f << "rankdit=TB" << std::endl;
    for (auto const& line : inp) {
        auto items = aoc::string::split(line, ' ');
        std::string src{items[0].cbegin() + 1, items[0].cend()};
        switch (items.at(0).at(0)) {
            case 'b': {
                src = "broadcaster";
                break;
            }
            case '%':
            case '&': {
                break;
            }
            default: {
                assert(false);
                break;
            }
        }

        for (std::size_t i{2}; i < items.size(); i++) {
            std::string dst = items.at(i);
            dst.erase(std::remove_if(dst.begin(), dst.end(), [](auto const chr) { return chr == ','; }), dst.end());
            f << src << " -> " << dst << std::endl;
        }
    }
    f << "}" << std::endl;
    f.close();

    // From inspecting the graph created above; it's 4 nodes that needs to send
    // a high pulse to ql which then sends to the target of interest.
    Modules modules = create_modules(inp);
    std::unordered_map<std::string, std::int64_t> steps_for_input{
        {"ss", 0},
        {"fz", 0},
        {"fh", 0},
        {"mf", 0},
    };

    std::queue<Event> queue{};
    for (std::size_t i{0}; i < 1000000u; i++) {
        queue.push(Event{"aptly", Pulse::Low, "broadcaster"});

        while (!queue.empty()) {
            auto const event = queue.front();
            queue.pop();

            for (auto& [src, steps] : steps_for_input) {
                if (steps == 0 && event.src == src && event.pulse == Pulse::High && event.dst == "ql") {
                    steps = static_cast<std::int64_t>(i + 1u);
                }
            }

            if (std::all_of(steps_for_input.cbegin(), steps_for_input.cend(),
                            [](auto const& pair) { return pair.second != 0; })) {
                std::vector<std::int64_t> values{};

                std::transform(steps_for_input.cbegin(), steps_for_input.cend(), std::back_inserter(values),
                               [](auto const& pair) { return pair.second; });

                return aoc::math::lcm(values);
            }

            auto const new_events = modules[event.dst]->step(event);
            for (auto const& new_event : new_events) {
                queue.push(new_event);
            }
        }
    }

    return 0;
}

void samples() {
    auto bm = BroadcastModule("a");
    bm.subscribe("b");
    bm.subscribe("c");

    auto out = bm.step(Event{"", Pulse::Low, "a"});
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::Low);
    assert(out.at(0).dst == "b");
    assert(out.at(1).src == "a");
    assert(out.at(1).pulse == Pulse::Low);
    assert(out.at(1).dst == "c");

    out = bm.step(Event{"", Pulse::High, "a"});
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::High);
    assert(out.at(0).dst == "b");
    assert(out.at(1).src == "a");
    assert(out.at(1).pulse == Pulse::High);
    assert(out.at(1).dst == "c");

    auto ffm = FlipFlopModule("a");
    ffm.subscribe("b");
    ffm.subscribe("c");

    out = ffm.step(Event{"", Pulse::Low, "a"});
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::High);
    assert(out.at(0).dst == "b");
    assert(out.at(1).src == "a");
    assert(out.at(1).pulse == Pulse::High);
    assert(out.at(1).dst == "c");

    out = ffm.step(Event{"", Pulse::Low, "a"});
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::Low);
    assert(out.at(0).dst == "b");
    assert(out.at(1).src == "a");
    assert(out.at(1).pulse == Pulse::Low);
    assert(out.at(1).dst == "c");

    out = ffm.step(Event{"", Pulse::High, "a"});
    assert(out.size() == 0u);

    out = ffm.step(Event{"", Pulse::Low, "a"});
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::High);
    assert(out.at(0).dst == "b");
    assert(out.at(1).src == "a");
    assert(out.at(1).pulse == Pulse::High);
    assert(out.at(1).dst == "c");

    auto cm = ConjunctionModule("a");
    cm.subscribe("d");
    cm.register_input("b");
    cm.register_input("c");

    out = cm.step(Event{"b", Pulse::Low, "a"});
    assert(out.size() == 1u);
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::High);
    assert(out.at(0).dst == "d");

    out = cm.step(Event{"c", Pulse::Low, "a"});
    assert(out.size() == 1u);
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::High);
    assert(out.at(0).dst == "d");

    out = cm.step(Event{"b", Pulse::High, "a"});
    assert(out.size() == 1u);
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::High);
    assert(out.at(0).dst == "d");

    out = cm.step(Event{"c", Pulse::High, "a"});
    assert(out.size() == 1u);
    assert(out.at(0).src == "a");
    assert(out.at(0).pulse == Pulse::Low);
    assert(out.at(0).dst == "d");

    auto sample = aoc::utils::read_input(AOC_SAMPLE_INPUT);
    assert(solve_1(sample) == 32000000);

    sample = aoc::utils::read_input("day20-sample-1.input");
    assert(solve_1(sample) == 11687500);
}

};  // namespace aoc::y2023::d20

int main(int argc, char** argv) {
    auto input = aoc::utils::read_input(AOC_INPUT);

    auto solve_1_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part1 = aoc::y2023::d20::solve_1(inp);
        std::cout << "part 1: " << part1 << std::endl;
    };
    auto solve_2_wrapper = [](std::vector<std::string> const& inp) -> void {
        auto part2 = aoc::y2023::d20::solve_2(inp);
        std::cout << "part 2: " << part2 << std::endl;
    };

    return aoc::run(argc, argv, aoc::y2023::d20::samples, solve_1_wrapper, solve_2_wrapper, input);
}
