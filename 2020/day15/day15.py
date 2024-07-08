def update(td, turn, num):
    n = td.get(num)

    if n:
        # does not exist
        td.update({num: turn})
    elif len(n) == 1:
        # only one item exist, append item.
        td[num].append(turn)
    elif len(n) == 2:
        # two exists, remove first and append
        td[num].append(turn)
        td[num].pop()

    return td


def sol1(l, turns):
    td = {}
    for i in range(1, turns + 1):
        # print(f"turn: {i}")

        if i <= len(l):
            td.update({l[i - 1]: [i]})
            last_num = l[i - 1]
        else:
            n = td.get(last_num)
            # print(f"{last_num}: {n}")

            if n == None:
                # first time, new number is 0
                new_n = 0
            elif len(n) == 1:
                # first time, new number is 0
                new_n = 0
            elif len(n) == 2:
                # second time, new number is difference
                new_n = td[last_num][1] - td[last_num][0]
            # print(f"new number is: {new_n}")

            curr = td.get(new_n)
            if curr == None:
                td.update({new_n: [i]})
            elif len(curr) == 1:
                td[new_n].append(i)
            elif len(curr) == 2:
                td[new_n].append(i)
                td[new_n].pop(0)

            last_num = new_n

            if i == turns:
                return new_n


def main() -> None:
    sam = [0, 3, 6]
    prob = [2, 1, 10, 11, 0, 6]

    print(f"sample 1: {sol1(sam, 2020)}\tcorrect: 436")
    print(f"solut. 1: {sol1(prob, 2020)}\tcorrect: 232")
    print(f"solut. 2: {sol1(prob, 30000000)}\tcorrect: [1892917, inf]")


if __name__ == "__main__":
    main()
