import os
import subprocess
from collections import Counter


def used_file_extensions(args):
    """
    Python variant of the cmake alternative that I had before.
    """

    extensions = []
    for file in subprocess.check_output(["git", "ls-files"]).decode().splitlines():
        _, ext = os.path.splitext(file)
        extensions.append(ext)

    counts = Counter(extensions)
    for ext, count in counts.most_common():
        print(f"{count:>4} | {ext}")


def register_subcommand(subparsers):
    parser = subparsers.add_parser(
        "used_file_extensions",
        description="Summarizes and displays amount of files for each extension",
        help="Summarizes and displays amount of files for each extension",
    )


def run(args):
    used_file_extensions(args)
