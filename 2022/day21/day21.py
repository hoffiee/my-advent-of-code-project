# This goes through the dict of monkeys and their expressions, it then
# recursively forms a string that can be parsed by sympy, which then solves
# for x
import sympy


def expr(sys_eq, monkey: str) -> str:
    # humn is the input variable
    if monkey == "humn":
        return "x"
    m = sys_eq[monkey]
    if len(m) == 1:
        return f"{m[0]}"
    return f"({expr(sys_eq, m[0])} {m[1]} {expr(sys_eq, m[2])})"


def sol2(sys_eq) -> None:
    lhs = expr(sys_eq, sys_eq["root"][0])
    rhs = expr(sys_eq, sys_eq["root"][2])

    lhs_expr = sympy.parse_expr(lhs)
    rhs_expr = sympy.parse_expr(rhs)

    eq = sympy.Eq(lhs_expr, rhs_expr)

    print(sympy.solve(eq)[0])


def main() -> None:
    for file in ["day21-sample.input", "day21.input"]:
        f = open(file, "r", encoding="utf8")
        lines = f.readlines()
        sys_eq = {}
        for line in lines:
            content = line.split()
            if len(content) == 2:
                sys_eq[content[0]] = [int(content[1])]
            else:
                sys_eq[content[0]] = (content[1], content[2], content[3])
        sol2(sys_eq)


if __name__ == "__main__":
    main()
