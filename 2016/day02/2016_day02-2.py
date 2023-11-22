#!usr/bin/env Python
# -*- coding: utf-8 -*-
import math

# Examples
ex_1 = ["ULL", "RRDDD", "LURDL", "UUUUD"]
ex_1 = [
    ["U", "L", "L"],
    ["R", "R", "D", "D", "D"],
    ["L", "U", "R", "D", "L"],
    ["U", "U", "U", "U", "D"],
]


# fix this one later
def get_data():
    with open("input.txt") as textFile:
        m = [list(x.split(",")) for x in textFile]
        # for x in textFile:
        #   m = x

    # print(type(m[0][0]))
    # print(m[0][0])

    out = []
    for r in range(len(m)):
        out.append([])
        for c in range(len(m[r][0])):
            out[r].append(m[r][0][c])

    # print(out[0])
    out[0].pop(len(out[0]) - 1)
    # print(out[0])

    return out


class keypad:
    def __init__(self):
        self.curr_pos = [1, 1]  # [r,c]
        self.numbers = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

    def move(self, ch):
        # move up
        if (ch == "U") and (self.curr_pos[0] > 0):
            self.curr_pos = [self.curr_pos[0] - 1, self.curr_pos[1]]
        # move down
        elif (ch == "D") and (self.curr_pos[0] < 2):
            self.curr_pos = [self.curr_pos[0] + 1, self.curr_pos[1]]
        # Move right
        elif (ch == "R") and (self.curr_pos[1] < 2):
            self.curr_pos = [self.curr_pos[0], self.curr_pos[1] + 1]
        # Move left
        elif (ch == "L") and (self.curr_pos[1] > 0):
            self.curr_pos = [self.curr_pos[0], self.curr_pos[1] - 1]

    def current_number(self):
        return self.numbers[self.curr_pos[0]][self.curr_pos[1]]

    def sequence(self, inp):
        for i in range(len(inp)):
            self.move(inp[i])
            # print(self.current_number())

    def multiple_sequences(self, inp):
        for i in range(len(inp)):
            self.sequence(inp[i])
            print(
                self.current_number(),
            )
        print("")

    def reset(self):
        self.curr_pos = [1, 1]


if __name__ == "__main__":
    k = keypad()
    k.multiple_sequences(ex_1)
    k.reset()

    data = get_data()

    k.multiple_sequences(data)
