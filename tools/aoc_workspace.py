import sys
import argparse
import subprocess
import os


def build(args, forward_args):
    if args.release or args.debug:
        assert False, "Not supported yet!"
    build_dir = os.path.join("build")
    subprocess.run(["ninja", *args.targets], cwd=build_dir, check=True)


def format(args, forward_args):
    print("Not supported yet.")
    return
    if not any([args.cpp, args.python, args.go]):
        args.cpp = True
        args.python = True
        args.go = True


def lint(args, forward_args):
    print("Not supported yet.")
    return


def event_status(args, forward_args):
    import tools.event_status as ev
    ev.eventStatus()


def setup_day(args, forward_args):
    print(args, forward_args)
    from tools.setup_day import SetupTemplateDay
    SetupTemplateDay(forward_args)


def used_file_extensions(args, forward_args):
    """
    Python variant of the cmake alternative that I had before.
    find src -type f
        | grep -vE '\(CMakeLists.txt\)'
        | cut -d"." -f2 # cut at delimeter . and print second field
        | sort | uniq -c | sort -nr
    )
    """
    from collections import Counter

    extensions = []
    for dirpath, dirnames, filenames in os.walk("src"):
        for file in filenames:
            _, ext = os.path.splitext(file)
            extensions.append(ext)
    counts = Counter(extensions)
    for ext, count in counts.most_common():
        print(f"{count:>4} | {ext}")


def main():
    parser = argparse.ArgumentParser(
        prog="aoc workspace run entrypoint",
        description="Intended to be an entrypoint for various activities",
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    parser_build = subparsers.add_parser("build", help="build command")
    parser_build.add_argument(
        "--release", action="store_true", help="Build in release mode"
    )
    parser_build.add_argument(
        "--debug", action="store_true", help="Build in debug mode"
    )
    parser_build.add_argument("targets", nargs="+", help="List of targets to build")
    parser_build.set_defaults(func=build)

    parser_format = subparsers.add_parser("format", help="format command")
    parser_format.add_argument("--cpp", action="store_true", help="format C++")
    parser_format.add_argument("--python", action="store_true", help="format Python")
    parser_format.add_argument("--go", action="store_true", help="format Go")
    parser_format.set_defaults(func=format)

    parser_setup_day = subparsers.add_parser("setup_day", add_help=False)
    parser_setup_day.set_defaults(func=setup_day)


    parser_setup_build = subparsers.add_parser(
        "used_file_extensions",
        help="Summarizes and displays amount of files for each extension",
    )
    parser_setup_build.set_defaults(func=used_file_extensions)

    args, forward_args = parser.parse_known_args()
    args.func(args, forward_args)


if __name__ == "__main__":
    main()
