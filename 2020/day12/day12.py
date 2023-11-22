import math
import numpy as np


def read_and_parse_lines(filename: str) -> list[str]:
    with open(filename, "r") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    return out


class Ship:
    def __init__(self) -> None:
        self.x: float = 0.0
        self.y: float = 0.0
        self.theta: float = 0.0

    def step(self, steps: int) -> None:
        self.x += steps * math.cos(self.theta * math.pi / 180)
        self.y += steps * math.sin(self.theta * math.pi / 180)

    def move_ship(self, dir: str, change: float) -> None:
        if dir == "N":
            self.y += change
        elif dir == "W":
            self.x -= change
        elif dir == "S":
            self.y -= change
        elif dir == "E":
            self.x += change

    def set_direction(self, dir: str, change: int) -> None:
        if dir == "L":
            self.theta += change
        elif dir == "R":
            self.theta -= change

    def step_in_direction(self, dir: str, steps: int) -> None:
        if dir == "F":
            self.step(steps)
        elif dir in ["N", "S", "E", "W"]:
            self.move_ship(dir, steps)
        elif dir in ["L", "R"]:
            self.set_direction(dir, steps)

    def get_position(self) -> tuple[float, float, float]:
        return self.x, self.y, self.theta


class WPShip(Ship):
    def __init__(self, wpx: float, wpy: float) -> None:
        Ship.__init__(self)
        self.wpx: float = wpx
        self.wpy: float = wpy
        self.update_wptheta()

    def update_wptheta(self) -> None:
        self.wptheta = np.arctan2(self.wpy, self.wpx)

    def step(self, steps: int) -> None:
        self.x += self.wpx * steps
        self.y += self.wpy * steps

    def move_wp(self, dir: str, change: float) -> None:
        if dir == "N":
            self.wpy += change
        elif dir == "W":
            self.wpx -= change
        elif dir == "S":
            self.wpy -= change
        elif dir == "E":
            self.wpx += change
        self.update_wptheta()

    def rotate_wp(self, dir: str, change: float) -> None:
        l = math.sqrt(self.wpx**2 + self.wpy**2)
        if dir == "L":
            self.wptheta += change * math.pi / 180
        elif dir == "R":
            self.wptheta -= change * math.pi / 180
        self.wpx = l * math.cos(self.wptheta)
        self.wpy = l * math.sin(self.wptheta)

    def step_in_direction(self, dir: str, steps: int) -> None:
        if dir == "F":
            self.step(steps)
        elif dir in ["N", "S", "E", "W"]:
            self.move_wp(dir, steps)
        elif dir in ["L", "R"]:
            self.rotate_wp(dir, steps)

    def print_ship_status(self) -> None:
        print(f"location: ({self.x}, {self.y}), wp: ({self.wpx},{self.wpy})")


def sol1(lines: list[str]) -> float:
    s: Ship = Ship()
    for l in lines:
        s.step_in_direction(l[0], int(l[1:]))
    x, y, _ = s.get_position()
    return round(abs(x) + abs(y))


def sol2(lines: list[str]) -> float:
    s = WPShip(10, 1)
    for l in lines:
        s.step_in_direction(l[0], int(l[1:]))
    x, y, _ = s.get_position()
    return round(abs(x) + abs(y))


def main() -> None:
    sam = read_and_parse_lines("day12-sample.input")
    inp = read_and_parse_lines("day12.input")

    print(f"sample 1: {sol1(sam)}\tcorrect: 25")
    print(f"solut. 1: {sol1(inp)}\tcorrect: 1589")
    print(f"sample 1: {sol2(sam)}\tcorrect: 286")
    print(f"solut. 2: {sol2(inp)}\tcorrect: 23960")


if __name__ == "__main__":
    main()
