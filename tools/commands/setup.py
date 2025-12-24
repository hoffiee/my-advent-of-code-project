"""
This setups the workspace and enables various things that's necessary to run
it. Inteded to be run once after cloning.

It also includes some smaller setup stuff for individual days etc.

# Activate globally (add to ~/.bashrc)
eval "$(register-python-argcomplete entrypoint.py)"

# Or per-session
eval "$(register-python-argcomplete ./entrypoint.py)"

# Add to ~/.zshrc
register-python-argcomplete entrypoint.py >> ~/.zshrc

"""

from tools.cmake_utils import cmake_setup



def register_subcommand(subparsers):
    parser = subparsers.add_parser(
        "setup",
        description="TODO setup method for setting up this repo",
        help="TODO setup method for setting up this repo"
    )

    # parser_setup_day = subparsers.add_parser("setup_day")
    # parser_setup_day.set_defaults(func=setup_day)

    # parser_setup_build = parser.add_parser("setup", help="Setup build system")
    # parser.set_defaults(func=cmake_setup)

    # parser.set_defaults(func=run)


def run(args):
    cmake_setup(args, None)
