# This goes through the dict of monkeys and their expressions, it then
# recursively forms a string that can be parsed by sympy, which then solves
# for x
import sympy
import sys
from typing import Dict, Union, Tuple, List

from libs.aoc_runner.python import aoc_runner


def expr(sys_eq, monkey: str) -> str:
    # humn is the input variable
    if monkey == "humn":
        return "x"
    m = sys_eq[monkey]
    if len(m) == 1:
        return f"{m[0]}"
    return f"({expr(sys_eq, m[0])} {m[1]} {expr(sys_eq, m[2])})"


def sol2(lines) -> None:
    sys_eq: Dict[str, Union[Tuple[str, str, str], List[int]]] = {}
    for line in lines:
        content = line.split()
        if len(content) == 2:
            sys_eq[content[0]] = [int(content[1])]
        else:
            sys_eq[content[0]] = (content[1], content[2], content[3])

    lhs = expr(sys_eq, sys_eq["root"][0])
    rhs = expr(sys_eq, sys_eq["root"][2])

    lhs_expr = sympy.parse_expr(lhs)
    rhs_expr = sympy.parse_expr(rhs)

    eq = sympy.Eq(lhs_expr, rhs_expr)

    print(sympy.solve(eq)[0])
    return sympy.solve(eq)[0]


def main() -> None:
    for filename in ["day21-sample.input", "day21.input"]:
        with open(filename, "r", encoding="utf8") as f:
            lines = f.readlines()
            sol2(lines)


def samples():
    with open("day21-sample.input", "r", encoding="utf8") as f:
        sample = list(map(str.rstrip, f.readlines()))
    assert sol2(sample) == 301


if __name__ == "__main__":
    with open("day21.input", "r", encoding="utf8") as f:
        inp = list(map(str.rstrip, f.readlines()))
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {0}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
