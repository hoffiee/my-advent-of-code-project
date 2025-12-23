"""
TODO: Implement bench specific target
TODO: implement bench visualize
"""


def register_subcommand(subparsers):
    parser = subparsers.add_parser("bench", help="TODO")
    # parser.set_defaults(func=run)


def run(args):
    print(args)
    raise NotImplementedError("implement this feature")
    print(f"Running setup")
