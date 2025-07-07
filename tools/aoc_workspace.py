import sys
import argparse
import subprocess
import os

from tools.cmake_utils import setup_cmake


def build(args, forward_args):
    build_path = os.path.join("build/debug")
    if args.release:
        build_path = os.path.join("build/release")
    if not os.path.exists(build_path):
        setup_cmake(args, forward_args)

    subprocess.run(["ninja", *args.targets], cwd=build_path, check=True)


def format(args, forward_args):
    if not any([args.cpp, args.python, args.go]):
        args.cpp = True
        args.python = True
        args.go = True

    build_path = os.path.join("build/debug")
    if not os.path.exists(build_path):
        setup_cmake(args, forward_args)
    subprocess.run(["ninja", "format"], cwd=build_path, check=True)


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

    parser_event_status = subparsers.add_parser(
        "status", help="Shows the status on completed starts and targets"
    )
    parser_event_status.set_defaults(func=event_status)

    parser_setup_build = subparsers.add_parser("setup", help="Setup build system")
    parser_setup_build.set_defaults(func=setup_cmake)

    parser_setup_build = subparsers.add_parser(
        "used_file_extensions",
        help="Summarizes and displays amount of files for each extension",
    )
    parser_setup_build.set_defaults(func=used_file_extensions)

    args, forward_args = parser.parse_known_args()
    args.func(args, forward_args)


if __name__ == "__main__":
    main()
