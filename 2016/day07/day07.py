import re
import string


def is_abba(substr):
    return substr[0] == substr[3] and substr[1] == substr[2] and substr[0] != substr[1]


def is_aba(substr):
    return substr[0] == substr[2] and substr[0] != substr[1]


def check_condition(data, cond):
    for datum in data:
        if len(datum) < 4:
            return False
        for i in range(len(datum) - 3):
            if cond(datum[i : i + 4]):
                return True
    return False


def sol1(data):
    count = 0
    for datum in data:
        split = re.split(r"\[([^\]]+)\]", datum)
        ips = split[::2]
        hypernets = split[1::2]
        if check_condition(hypernets, is_abba):
            continue
        if check_condition(ips, is_abba):
            count += 1
    print(count)


def generate_candidates():
    out = {}
    for first in string.ascii_lowercase:
        for second in string.ascii_lowercase:
            aba = first + second + first
            # Filter out aaa,ccc,...
            if is_aba(aba):
                bab = second + first + second
                out[aba] = bab
    return out


def sol2(data):
    count = 0
    for datum in data:
        split = re.split(r"\[([^\]]+)\]", datum)
        ips = split[::2]
        hypernets = split[1::2]

        list_of_valid = generate_candidates()

        for cand_aba, cand_bab in list_of_valid.items():
            # Assumes that python doesn't execute the second check if the first fails. But I need to look that up to know.
            if any(ip.find(cand_aba) > -1 for ip in ips) and any(
                net.find(cand_bab) > -1 for net in hypernets
            ):
                count += 1
                break
    print(count)


def main() -> None:
    for filename in ["day07-sample.input", "day07.input"]:
        with open(filename, "r", encoding="utf8") as file:
            lines = file.read().splitlines()
            sol1(lines)
            sol2(lines)


if __name__ == "__main__":
    main()
