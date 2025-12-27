from collections import Counter
import os
import shlex
import subprocess


def get_shebang_language(file_path):
    try:
        with open(file_path, "rb") as f:
            line = f.readline().decode("utf-8", errors="ignore").strip()
        if line.startswith("#!"):
            shebang = shlex.split(line[2:])
            interpreter = shebang[0] if shebang else ""
            if "env" in interpreter:
                lang = shebang[1].lower() if len(shebang) > 1 else "unknown"
            else:
                lang = os.path.basename(interpreter).lower()
            lang_map = {
                "python3": ".py",
                "bash": ".sh",
            }
            return lang_map.get(lang.split("/")[0], lang)
        return None
    except Exception:
        return None


def used_file_extensions(args):
    """
    Python variant of the cmake alternative that I had before.
    """

    extensions = []
    for file in subprocess.check_output(["git", "ls-files"]).decode().splitlines():
        name, ext = os.path.splitext(file)
        if ext == "":
            if len(name) > 0 and name[0] == ".":
                # File is a .-file, skip it
                continue

            # Check if it is executable, then check what language through the shebang
            if os.access(file, os.X_OK):
                ext = get_shebang_language(file)

        extensions.append(ext)

    counts = Counter(extensions)
    for ext, count in counts.most_common():
        assert ext[0] == ".", (
            f"Extension {ext} doesn't start with a period, there's probably "
            + "some mapping missing in the shebang extraction"
        )
        print(f"{count:>4} | {ext}")


def register_subcommand(subparsers):
    parser = subparsers.add_parser(
        "used_file_extensions",
        description="Summarizes and displays amount of files for each extension",
        help="Summarizes and displays amount of files for each extension",
    )


def run(args):
    used_file_extensions(args)
