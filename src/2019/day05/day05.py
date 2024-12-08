"""
https://adventofcode.com/2019/day/5

Day 5 continues on
https://adventofcode.com/2019/day/2
"""

from collections import defaultdict
from icecream import ic


attempts_1 = [
    (0, ""),
    (13294380, "correct"),
]

attempts_2 = [
    (0, ""),
    (11460760, "correct"),
]


# Move to utils?
def suggest_solution(attempts, inp):
    for value, msg in attempts:
        if inp == value:
            print(f"{value}\t<-- {msg}")
            return
    print(inp)


class IntcodeComputer:
    def __init__(self, data):
        self.address = defaultdict(int)
        self.current_iteration = 0
        self.running = True
        self.output = 0
        self.input = 0
        self.debug = False
        ic(data)

        data_list = data.split(",")
        for i, value in enumerate(data_list):
            self.address[i] = int(value)

    def set_input(self, value):
        self.input = value

    def get_output(self):
        return self.output

    def run(self) -> bool:
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
        self.address[dst] = self.input
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


def sol1(data):
    comp = IntcodeComputer(data[0])
    comp.set_input(1)
    comp.run()
    return comp.get_output()


def sol2(data):
    comp = IntcodeComputer(data[0])
    comp.set_input(5)
    comp.run()
    return comp.get_output()


def test_equal_position_mode():
    ic.disable()
    comp = IntcodeComputer("3,9,8,9,10,9,4,9,99,-1,8")
    comp.set_input(8)
    while comp.step():
        pass
    assert comp.get_output() == 1

    comp = IntcodeComputer("3,9,8,9,10,9,4,9,99,-1,8")
    comp.set_input(7)
    while comp.step():
        pass
    assert comp.get_output() == 0

    comp = IntcodeComputer("3,9,8,9,10,9,4,9,99,-1,8")
    comp.set_input(9)
    while comp.step():
        pass
    assert comp.get_output() == 0


def test_equal_immediate_mode():
    ic.disable()
    comp = IntcodeComputer("3,3,1108,-1,8,3,4,3,99")
    comp.set_input(8)
    comp.run()
    assert comp.get_output() == 1

    comp = IntcodeComputer("3,3,1108,-1,8,3,4,3,99")
    comp.set_input(7)
    comp.run()
    assert comp.get_output() == 0

    comp = IntcodeComputer("3,3,1108,-1,8,3,4,3,99")
    comp.set_input(9)
    comp.run()
    assert comp.get_output() == 0


def test_less_than_position_mode():
    ic.disable()
    comp = IntcodeComputer("3,9,7,9,10,9,4,9,99,-1,8")
    comp.set_input(7)
    comp.run()
    assert comp.get_output() == 1

    comp = IntcodeComputer("3,9,7,9,10,9,4,9,99,-1,8")
    comp.set_input(8)
    comp.run()
    assert comp.get_output() == 0

    comp = IntcodeComputer("3,9,7,9,10,9,4,9,99,-1,8")
    comp.set_input(9)
    comp.run()
    assert comp.get_output() == 0


def test_less_than_immediate_mode():
    ic.disable()
    comp = IntcodeComputer("3,3,1107,-1,8,3,4,3,99")
    comp.set_input(7)
    comp.run()
    assert comp.get_output() == 1

    comp = IntcodeComputer("3,3,1107,-1,8,3,4,3,99")
    comp.set_input(8)
    comp.run()
    assert comp.get_output() == 0

    comp = IntcodeComputer("3,3,1107,-1,8,3,4,3,99")
    comp.set_input(9)
    comp.run()
    assert comp.get_output() == 0


def test_jump_position_mode():
    ic.disable()
    comp = IntcodeComputer("3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9")
    comp.set_input(0)
    comp.run()
    assert comp.get_output() == 0

    comp = IntcodeComputer("3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9")
    comp.set_input(1)
    comp.run()
    assert comp.get_output() == 1


def test_jump_immediate_mode():
    ic.disable()
    comp = IntcodeComputer("3,3,1105,-1,9,1101,0,0,12,4,12,99,1")
    comp.set_input(0)
    comp.run()
    assert comp.get_output() == 0

    comp = IntcodeComputer("3,3,1105,-1,9,1101,0,0,12,4,12,99,1")
    comp.set_input(1)
    comp.run()
    assert comp.get_output() == 1


def test_larger_example():
    ic.disable()
    comp = IntcodeComputer(
        "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
        "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,"
        "999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"
    )
    comp.set_input(7)
    comp.run()
    assert comp.get_output() == 999

    comp = IntcodeComputer(
        "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
        "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,"
        "999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"
    )
    comp.set_input(8)
    comp.run()
    assert comp.get_output() == 1000

    comp = IntcodeComputer(
        "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
        "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,"
        "999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"
    )
    comp.set_input(9)
    comp.run()
    assert comp.get_output() == 1001


def main() -> None:
    test_equal_position_mode()
    test_equal_immediate_mode()
    test_less_than_position_mode()
    test_less_than_immediate_mode()
    test_jump_position_mode()
    test_jump_immediate_mode()
    test_larger_example()

    for filename in ["day05-sample.input", "day05.input"]:
        with open(filename, "r", encoding="utf8") as file:
            lines = file.read().splitlines()
            suggest_solution(attempts_1, sol1(lines))
            suggest_solution(attempts_2, sol2(lines))


if __name__ == "__main__":
    main()
