"""

This setups the workspace and enables various things that's necessary to run it. Inteded to be run once after cloning.


# Activate globally (add to ~/.bashrc)
eval "$(register-python-argcomplete entrypoint.py)"

# Or per-session
eval "$(register-python-argcomplete ./entrypoint.py)"

# Add to ~/.zshrc
register-python-argcomplete entrypoint.py >> ~/.zshrc

"""


def register_subcommand(subparsers):
    parser = subparsers.add_parser("setup", help="TODO")
    # parser.set_defaults(func=run)


def run(args):
    raise NotImplementedError("implement this feature")
    print(f"Running setup")
