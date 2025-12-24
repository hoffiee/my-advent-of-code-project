# parser_setup_aoc_fetch = subparsers.add_parser(
#     "build_aoc_fetch", help="Builds Go binaries and installs them."
# )
# parser_setup_aoc_fetch.set_defaults(func=setup_aoc_fetch)


def register_subcommand(subparsers):
    parser = subparsers.add_parser("fetch", help="TODO")
    # parser.set_defaults(func=run)


def run(args):
    raise NotImplementedError("implement this feature")
    print(f"Running setup")
