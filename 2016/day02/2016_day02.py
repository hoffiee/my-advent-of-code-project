#!usr/bin/env Python
# -*- coding: utf-8 -*-


# Examples
ex_1 = [
    ["U", "L", "L"],
    ["R", "R", "D", "D", "D"],
    ["L", "U", "R", "D", "L"],
    ["U", "U", "U", "U", "D"],
]


# fix this one later
def get_data():
    with open("day02.input", encoding="utf8") as textFile:
        m = [list(x.split(",")) for x in textFile]

    out = []
    for obj in m:
        out.append([])
        for obj_to_append in obj[0]:
            out[-1].append(obj_to_append)

    out[0].pop(len(out[0]) - 1)

    return out


class keypad:
    def __init__(self):
        self.curr_pos = [1, 1]  # [r,c]
        self.numbers = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

    def move(self, ch):
        if (ch == "U") and (self.curr_pos[0] > 0):
            self.curr_pos = [self.curr_pos[0] - 1, self.curr_pos[1]]
        elif (ch == "D") and (self.curr_pos[0] < 2):
            self.curr_pos = [self.curr_pos[0] + 1, self.curr_pos[1]]
        elif (ch == "R") and (self.curr_pos[1] < 2):
            self.curr_pos = [self.curr_pos[0], self.curr_pos[1] + 1]
        elif (ch == "L") and (self.curr_pos[1] > 0):
            self.curr_pos = [self.curr_pos[0], self.curr_pos[1] - 1]

    def current_number(self):
        return self.numbers[self.curr_pos[0]][self.curr_pos[1]]

    def sequence(self, inp):
        for obj in inp:
            self.move(obj)

    def multiple_sequences(self, inp):
        for obj in inp:
            self.sequence(obj)
            print(self.current_number(), end="")
        print("")

    def reset(self):
        self.curr_pos = [1, 1]


if __name__ == "__main__":
    k = keypad()
    k.multiple_sequences(ex_1)
    k.reset()

    data = get_data()

    k.multiple_sequences(data)
