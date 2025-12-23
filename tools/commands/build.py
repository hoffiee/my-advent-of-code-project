from tools.cmake_utils import cmake_setup, cmake_build


def register_subcommand(subparsers):
    parser = subparsers.add_parser("build", help="build command")
    parser.add_argument("--release", action="store_true", help="Build in release mode")
    parser.add_argument("targets", nargs="+", help="List of targets to build")


def run(args):
    cmake_build(args, None)
