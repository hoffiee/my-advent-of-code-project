from tools.cmake_utils import cmake_setup, cmake_build
import subprocess
import os


def format(args, forward_args):
    if not any([args.cpp, args.python, args.go]):
        args.cpp = True
        args.python = True
        args.go = True
        args.rust = True

    build_path = os.path.join("build/debug")
    if not os.path.exists(build_path):
        cmake_setup(args, forward_args)
    # TODO: This one formats everything now.. Fix
    subprocess.run(["ninja", "format"], cwd=build_path, check=True)


def register_subcommand(subparsers):
    parser = subparsers.add_parser(
        "format", description="Format files", help="format files"
    )

    parser.add_argument("--cpp", action="store_true", help="Format C++")
    parser.add_argument("--python", action="store_true", help="Format Python")
    parser.add_argument("--go", action="store_true", help="Format Go")
    parser.add_argument("--rust", action="store_true", help="Format rust")


def run(args):
    format(args, None)
