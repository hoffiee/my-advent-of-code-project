import os
import subprocess


def ctest_test(args=None, forward_args=None) -> int:
    build_path = os.path.join("build/debug")
    if args.release:
        build_path = os.path.join("build/release")
    if not os.path.exists(build_path):
        cmake_setup(args, forward_args)
    result = subprocess.run(["ctest"], cwd=build_path, check=True)
    return result.returncode


def register_subcommand(subparsers):
    parser = subparsers.add_parser("test", help="TODO: Run tests")
    parser.add_argument(
        "--release", action="store_true", help="Test in release mode"
    )
    parser.add_argument("--debug", action="store_true", help="Test in debug mode")
    parser.set_defaults(func=ctest_test)


def run(args):
    ctest_test(args, None)
