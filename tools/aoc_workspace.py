import sys
import argparse
import subprocess
import os

from tools.cmake_utils import cmake_setup, cmake_build

# from tools.go_utils import setup_aoc_fetch


def lint(args, forward_args):
    print("Not supported yet.")
    return


def ctest_test(args=None, forward_args=None) -> int:
    build_path = os.path.join("build/debug")
    if args.release:
        build_path = os.path.join("build/release")
    if not os.path.exists(build_path):
        cmake_setup(args, forward_args)
    result = subprocess.run(["ctest"], cwd=build_path, check=True)
    return result.returncode


def setup_day(args, forward_args):
    print(args, forward_args)
    from tools.setup_day import SetupTemplateDay

    SetupTemplateDay(forward_args)


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
    parser_build.set_defaults(func=cmake_build)

    parser_setup_day = subparsers.add_parser("setup_day", add_help=False)
    parser_setup_day.set_defaults(func=setup_day)

    parser_setup_build = subparsers.add_parser("setup", help="Setup build system")
    parser_setup_build.set_defaults(func=cmake_setup)

    parser_test = subparsers.add_parser("test", help="TODO")
    parser_test.add_argument(
        "--release", action="store_true", help="Test in release mode"
    )
    parser_test.add_argument("--debug", action="store_true", help="Test in debug mode")
    parser_test.set_defaults(func=ctest_test)

    # parser_setup_aoc_fetch = subparsers.add_parser(
    #     "build_aoc_fetch", help="Builds Go binaries and installs them."
    # )
    # parser_setup_aoc_fetch.set_defaults(func=setup_aoc_fetch)

    args, forward_args = parser.parse_known_args()
    args.func(args, forward_args)


if __name__ == "__main__":
    main()
