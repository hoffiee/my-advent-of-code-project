"""
TODO: Implement bench specific target
TODO: implement bench visualize
"""

def register_subcommand(subparsers):
    parser = subparsers.add_parser("bench", help="")
    # parser.set_defaults(func=run)

def run(args):
    raise NotImplementedError("implement this feature")
    print(f"Running setup")
