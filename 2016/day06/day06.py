import collections


def sol1(data):
    out: str = ""
    for it in data:
        k, _ = collections.Counter(it).most_common(1)[0]
        out += k
    print(out)


def sol2(data):
    out: str = ""
    for it in data:
        d = dict(collections.Counter(it))
        out += min(d, key=d.get)
    print(out)


def main() -> None:
    for file in ["day06-sample.input", "day06.input"]:
        with open(file, "r", encoding="utf8") as file:
            lines = file.read().splitlines()

            # neat way of transposing data
            transposed = list(zip(*lines))

            sol1(transposed)
            sol2(transposed)


if __name__ == "__main__":
    main()
