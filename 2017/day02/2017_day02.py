filename = "day02.input"

if __name__ == "__main__":
    with open(filename, "r", encoding="utf8") as f:
        m = [[int(x) for x in line.split()] for line in f]

    test_list = [[5, 1, 9, 5], [7, 5, 3], [2, 4, 6, 8]]

    checksum = 0

    for obj in m:
        checksum += max(obj) - min(obj)

    print(checksum)
