import re


def cmp_list(a, b):
    """compare 2 lists, is there a better way to do this?"""
    return all(i == j for i, j in zip(a, b))


def solution(data):
    configurations = [data.copy()]
    memory = data.copy()

    while True:
        tmp = max(memory)
        ind = memory.index(tmp)
        nr_of_memory_banks = len(memory)
        memory[ind] = 0

        while tmp > 0:
            ind = (ind + 1) % nr_of_memory_banks
            memory[ind] += 1
            tmp -= 1

        for i, configuration in enumerate(configurations):
            if cmp_list(memory, configuration):
                print(f"redistribution cycles: {len(configurations)}")
                print(f"cycles in loop: {len(configurations) - i}")
                return

        configurations.append(memory.copy())


def main() -> None:
    for filename in ["day06-sample.input", "day06.input"]:
        with open(filename, "r", encoding="utf8") as file:
            line = file.readline()
            memory_banks = list(map(int, re.findall(r"\d+", line)))
            solution(memory_banks)


if __name__ == "__main__":
    main()
