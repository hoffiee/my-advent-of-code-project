def register_subcommand(subparsers):
    parser = subparsers.add_parser("lint", description="Lint", help="TODO: Lint")
    parser.add_argument("--cpp", action="store_true", help="Lint C++")
    parser.add_argument("--python", action="store_true", help="Lint Python")
    parser.add_argument("--go", action="store_true", help="Lint Go")
    parser.add_argument("--rust", action="store_true", help="Lint rust")


def run(args):
    print("Not supported yet.")
    raise NotImplementedError("implement this feature")
