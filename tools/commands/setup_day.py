def setup_day(args, forward_args):
    print(args, forward_args)
    from tools.setup_day import SetupTemplateDay

    SetupTemplateDay(forward_args)


def register_subcommand(subparsers):
    parser = subparsers.add_parser(
        "setup_day", description="Setup an template day", help="Setup an template day"
    )


def run(args):
    raise NotImplementedError("implement this feature")
    print(f"Running setup")
