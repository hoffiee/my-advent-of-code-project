import argparse
import sys


def aoc_runner(prechecks, sol1, sol2, data) -> None:
    parser = argparse.ArgumentParser(description="aoc-runner-py")

    parser.add_argument("-s", "--samples", action="store_true", help="run prechecks")
    parser.add_argument("-a", "--all", action="store_true", help="run everything")
    parser.add_argument(
        "-p", "--part", type=int, choices=[1, 2], help="run specific part [1,2]"
    )
    args = parser.parse_args()

    if len(sys.argv) - 1 == 0:
        args.samples = True

    if args.all:
        args.samples = True
        args.part = None

    args.part_1 = False
    args.part_2 = False
    match args.part:
        case 1:
            args.part_1 = True
        case 2:
            args.part_2 = True
        case _:
            args.part_1 = True
            args.part_2 = True

    if args.samples:
        prechecks()
        print("checks done")

    if args.part_1:
        sol1(data)

    if args.part_2:
        sol2(data)
