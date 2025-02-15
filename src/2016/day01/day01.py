import sys

from libs.python.aoc_runner import aoc_runner

# Examples
ex_1 = ["R2", "L3"]
ex_2 = ["R2", "R2", "R2"]
ex_3 = ["R5", "L5", "R5", "R3"]
real_case_str = "R3, L5, R1, R2, L5, R2, R3, L2, L5, R5, L4, L3, R5, L1, R3, R4, R1, L3, R3, L2, L5, L2, R4, R5, R5, L4, L3, L3, R4, R4, R5, L5, L3, R2, R2, L3, L4, L5, R1, R3, L3, R2, L3, R5, L194, L2, L5, R2, R1, R1, L1, L5, L4, R4, R2, R2, L4, L1, R2, R53, R3, L5, R72, R2, L5, R3, L4, R187, L4, L5, L2, R1, R3, R5, L4, L4, R2, R5, L5, L4, L3, R5, L2, R1, R1, R4, L1, R2, L3, R5, L4, R2, L3, R1, L4, R4, L1, L2, R3, L1, L1, R4, R3, L4, R2, R5, L2, L3, L3, L1, R3, R5, R2, R3, R1, R2, L1, L4, L5, L2, R4, R5, L2, R4, R4, L3, R2, R1, L4, R3, L3, L4, L3, L1, R3, L2, R2, L4, L4, L5, R3, R5, R3, L2, R5, L2, L1, L5, L1, R2, R4, L5, R2, L4, L5, L4, L5, L2, L5, L4, R5, R3, R2, R2, L3, R3, L2, L5"
real_case = real_case_str.split(", ")

NORTH = 0
EAST = 1
SOUTH = 2
WEST = 3


class person:
    def __init__(self):  # Like xy axis.
        self.pos_x = 0  #   +   North   |   -   South
        self.pos_y = 0  #   +   West    |   -   East
        self.dir = 0  # 0 North, 1 West, 2 South, 3 East

    def move(self, inp):
        # Determine direction
        if inp[0] == "R":
            self.dir = (self.dir + 1) % 4
        elif inp[0] == "L":
            self.dir = (self.dir - 1) % 4

        # print(self.dir)

        # Add steps in that directions
        if self.dir == NORTH:
            # print("move: ", int(inp[1]), "in dir: ", self.dir)
            self.pos_y += int(inp[1:])  # NORTH
        elif self.dir == WEST:
            # print("move: ", int(inp[1]), "in dir: ", self.dir)
            self.pos_x += int(inp[1:])  # WEST
        elif self.dir == SOUTH:
            # print("move: ", int(inp[1]), "in dir: ", self.dir)
            self.pos_y -= int(inp[1:])  # SOUTH
        elif self.dir == EAST:
            # print("move: ", int(inp[1]), "in dir: ", self.dir)
            self.pos_x -= int(inp[1:])  # EAST

    def handle_input(self, inp):
        for obj in inp:
            self.move(obj)

    def length_to_origo(self):
        return abs(self.pos_x) + abs(self.pos_y)


def read_data():
    with open("day01.input", encoding="utf8") as textFile:
        for x in textFile:
            m_str = x
        m = m_str.replace("\n", "").split(", ")

    return m


def samples():
    test1 = person()
    test1.handle_input(ex_1)
    assert test1.length_to_origo() == 5

    test2 = person()
    test2.handle_input(ex_2)
    assert test2.length_to_origo() == 2

    test3 = person()
    test3.handle_input(ex_3)
    assert test3.length_to_origo() == 12


def sol1(inp):
    bill = person()
    bill.handle_input(inp)
    return bill.length_to_origo()


def sol2(inp):
    pass


if __name__ == "__main__":
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            real_case,
        )
    )
