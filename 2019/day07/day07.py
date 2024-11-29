"""
https://adventofcode.com/2019/day/5

Day 5 continues on
https://adventofcode.com/2019/day/2
"""

from collections import defaultdict
import itertools
from icecream import ic


attempts_1 = [
    (0, ""),
    (14902, "correct!"),
]

attempts_2 = [
    (0, ""),
]

# Move to utils?
def suggest_solution(attempts, inp):
    for value, msg in attempts:
        if inp == value:
            print(f"{value}\t<-- {msg}")
            return
    print(inp)


class IntcodeComputer:
    def __init__(self, data, feedback_mode = False):
        self.address = defaultdict(int)
        self.current_iteration = 0
        self.feedback_mode = feedback_mode
        self.running = True
        self.output = 0
        self.input = []
        self.debug = False

        data_list = data.split(",")
        for i, value in enumerate(data_list):
            self.address[i] = int(value)

    def set_input(self, value):
        self.halt = False
        self.input.append(value)

    def get_output(self):
        return self.output

    def run(self) -> bool:
        if self.feedback_mode and self.halt:
            return False
        while self.step():
            pass
        return True

    def step(self) -> bool:
        if not self.running:
            return self.running

        instruction = str(self.address[self.current_iteration]).zfill(5)
        params_mode = instruction[0:3]
        opcode = int(instruction[-2:])

        if opcode == 99:
            self.running = False
            return self.running

        match opcode:
            case 1:
                self._add(params_mode)
            case 2:
                self._multiply(params_mode)
            case 3:
                self._input(params_mode)
            case 4:
                self._output(params_mode)
                self.halt = True
            case 5:
                self._jump_if_true(params_mode)
            case 6:
                self._jump_if_false(params_mode)
            case 7:
                self._less_than(params_mode)
            case 8:
                self._equals(params_mode)
            case 99:
                self.running = False
            case _:
                assert False

        return self.running

    def print_memory(self):
        print(f"input: {self.input}")
        print(f"output: {self.output}")
        keys = sorted(self.address.keys())
        for key in keys:
            print(f"0x{key}: {self.address[key]}")

    def _get_value(self, value, param_mode):
        match int(param_mode):
            case 0:
                return int(self.address[value])
            case 1:
                return value
            case _:
                assert False

    def _add(self, params_mode):
        src1 = self._get_value(self.address[self.current_iteration + 1], params_mode[2])
        src2 = self._get_value(self.address[self.current_iteration + 2], params_mode[1])
        dst = self.address[self.current_iteration + 3]
        self.address[dst] = src1 + src2
        if self.debug:
            print(
                f"instr: {self.current_iteration} _add[{params_mode}] src1:{src1} src2:{src2} dst{dst}"
            )
        if self.current_iteration != dst:
            self.current_iteration += 4

    def _multiply(self, params_mode):
        src1 = self._get_value(self.address[self.current_iteration + 1], params_mode[2])
        src2 = self._get_value(self.address[self.current_iteration + 2], params_mode[1])
        dst = self.address[self.current_iteration + 3]
        self.address[dst] = src1 * src2
        if self.debug:
            print(
                f"instr: {self.current_iteration} _multiply[{params_mode}] src1:{src1} src2:{src2} dst{dst}"
            )
        if self.current_iteration != dst:
            self.current_iteration += 4

    def _equals(self, params_mode):
        src1 = self._get_value(self.address[self.current_iteration + 1], params_mode[2])
        src2 = self._get_value(self.address[self.current_iteration + 2], params_mode[1])
        dst = self.address[self.current_iteration + 3]
        self.address[dst] = int(src1 == src2)
        if self.debug:
            print(
                f"instr: {self.current_iteration} _equals[{params_mode}] src1:{src1} src2:{src2} dst{dst}"
            )
        if self.current_iteration != dst:
            self.current_iteration += 4

    def _less_than(self, params_mode):
        src1 = self._get_value(self.address[self.current_iteration + 1], params_mode[2])
        src2 = self._get_value(self.address[self.current_iteration + 2], params_mode[1])
        dst = self.address[self.current_iteration + 3]
        self.address[dst] = int(src1 < src2)
        if self.debug:
            print(
                f"instr: {self.current_iteration} _less_than[{params_mode}] src1:{src1} src2:{src2} dst{dst}"
            )
        if self.current_iteration != dst:
            self.current_iteration += 4

    def _jump_if_false(self, params_mode):
        arg1 = self._get_value(self.address[self.current_iteration + 1], params_mode[2])
        if arg1 != 0:
            self.current_iteration += 3
            return
        arg2 = self._get_value(self.address[self.current_iteration + 2], params_mode[1])
        if self.debug:
            print(
                f"instr: {self.current_iteration} _jump_if_false[{params_mode}] arg1:{arg1} arg2:{arg2}"
            )
        self.current_iteration = arg2

    def _jump_if_true(self, params_mode):
        arg1 = self._get_value(self.address[self.current_iteration + 1], params_mode[2])
        if arg1 == 0:
            self.current_iteration += 3
            return
        arg2 = self._get_value(self.address[self.current_iteration + 2], params_mode[1])
        if self.debug:
            print(
                f"instr: {self.current_iteration} _jump_if_true[{params_mode}] arg1:{arg1} arg2:{arg2}"
            )
        self.current_iteration = arg2

    def _input(self, params_mode):
        dst = self.address[self.current_iteration + 1]
        self.address[dst] = self.input.pop(0)
        if self.debug:
            print(f"instr: {self.current_iteration} _input[{params_mode}] dst:{dst}")
        self.current_iteration += 2

    def _output(self, params_mode):
        self.output = self._get_value(
            self.address[self.current_iteration + 1], params_mode[2]
        )
        if self.debug:
            print(
                f"instr: {self.current_iteration} _output[{params_mode}] "
                f"src:{self.current_iteration + 1} output:{self.output}"
            )
        self.current_iteration += 2


class Amplifier:
    def __init__(self, program, phase, inp):
        self.program = program
        self.gains = defaultdict(int)
        self._calculate_outputs(phase, inp)

    def _calculate_outputs(self, phase, inp):
        comp = IntcodeComputer(self.program)
        comp.set_input(phase)
        comp.set_input(inp)
        comp.run()
        self.gain = comp.get_output()
        ic(phase, self.program, comp.get_output())


class Amplifiers:
    def __init__(self, program):
        self.max_gain = 0
        self.program = program

        available_configurations = list(itertools.permutations([0,1,2,3,4]))
        ic(available_configurations)

        for config in available_configurations:

            A1 = Amplifier(program, config[0], 0)
            A2 = Amplifier(program, config[1], A1.gain)
            A3 = Amplifier(program, config[2], A2.gain)
            A4 = Amplifier(program, config[3], A3.gain)
            A5 = Amplifier(program, config[4], A4.gain)
            if A5.gain > self.max_gain:
                self.max_gain = A5.gain


class FeedbackAmplifier:
    def __init__(self, program, phase):
        self.program = program
        # self.gains = defaultdict(int)
        self.comp = IntcodeComputer(self.program, True)
        self.comp.set_input(phase)

    def step(self, inp):
        self.comp.set_input(inp)
        self.comp.run()
        self.gain = self.comp.get_output()
        # ic(phase, self.program, comp.get_output())


class FeedbackSystem:
    def __init__(self, program, config):
        self.max_gain = 0
        self.program = program
        self.config = config

        self.A1 = FeedbackAmplifier(program, config[0])
        self.A2 = FeedbackAmplifier(program, config[1])
        self.A3 = FeedbackAmplifier(program, config[2])
        self.A4 = FeedbackAmplifier(program, config[3])
        self.A5 = FeedbackAmplifier(program, config[4])

        self.A1.step(0)
        self.A2.step(self.A1.gain)
        self.A3.step(self.A2.gain)
        self.A4.step(self.A3.gain)
        self.A5.step(self.A4.gain)

        # feedback
        i = 0
        while i < 10:
            self.A1.step(self.max_gain)
            self.A2.step(self.A1.gain)
            self.A3.step(self.A2.gain)
            self.A4.step(self.A3.gain)
            self.A5.step(self.A4.gain)
            ic(self.A5.gain)
            i += 1
            self.max_gain += self.A5.gain


def sol1(data):
    amps = Amplifiers(data)
    return amps.max_gain


def sol2(data):
    ic(data)

def test_example_43210():
    ic.disable()
    program = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0"
    amps = Amplifiers(program)
    assert amps.max_gain == 43210

def test_example_54321():
    ic.disable()
    program = "3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0"
    amps = Amplifiers(program)
    assert amps.max_gain == 54321

def test_example_65210():
    ic.disable()
    program = "3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0"
    amps = Amplifiers(program)
    assert amps.max_gain == 65210


def test_example_feedback_98765():
    ic.enable()
    f = FeedbackSystem(
        "3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5",
        [9,8,7,6,5]
    )

    ic(f.max_gain)
    assert f.max_gain == 139629729




def main() -> None:
    test_example_43210()
    test_example_54321()
    test_example_65210()
    test_example_feedback_98765()

    for filename in ["day07.input"]:
        with open(filename, "r", encoding="utf8") as file:
            lines = file.read()
            suggest_solution(attempts_1, sol1(lines))
            # suggest_solution(attempts_2, sol2(lines))


if __name__ == "__main__":
    main()
