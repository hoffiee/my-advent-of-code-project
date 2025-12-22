
def register_subcommand(subparsers):
    parser = subparsers.add_parser("format", help="")
    # parser.set_defaults(func=run)

def run(args):
    raise NotImplementedError("implement this feature")
    print(f"Running setup")
