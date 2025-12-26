#!/usr/bin/env python3

"""
This is intended to replace the `source tools/activate` so that I can setup a
proper `entr` workflow.
"""

import os
import argparse
import subprocess
import importlib.util
import sys
from pathlib import Path

# PYTHON_ARGCOMPLETE_OK
import argcomplete  # Enables tab completion

sys.path.insert(0, subprocess.check_output(['git', 'rev-parse', '--show-toplevel']).decode().strip())

def load_module_from_file(file_path):
    """Dynamically import a Python module from a file path."""
    module_name = Path(file_path).stem
    spec = importlib.util.spec_from_file_location(module_name, file_path)
    if spec is None:
        return None
    module = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = module
    spec.loader.exec_module(module)
    return module

def main():
    parser = argparse.ArgumentParser(description="Advent of code commands")
    subparsers = parser.add_subparsers(dest='command', help='Available tools')

    tools_dir = Path("tools/commands")
    if not tools_dir.exists():
        print("Error: 'tools/' directory not found.", file=sys.stderr)
        sys.exit(1)

    # Scan for Python scripts and register their subcommands
    for py_file in tools_dir.glob("*.py"):
        try:
            module = load_module_from_file(py_file)
            if hasattr(module, 'register_subcommand'):
                module.register_subcommand(subparsers)
                # print(f"Registered subcommand from {py_file.name}")
        except Exception as e:
            print(f"Warning: Failed to load {py_file.name}: {e}", file=sys.stderr)

    if not subparsers.choices:
        parser.print_help()
        sys.exit(1)

    # Enable autocompletion for dynamic subcommands
    argcomplete.autocomplete(parser)

    args = parser.parse_args()

    # TODO: alternative way to run it
    # args, forward_args = parser.parse_known_args()
    # args.func(args, forward_args)

    # Execute the selected tool
    if args.command:
        module = load_module_from_file(tools_dir / f"{args.command}.py")
        if hasattr(module, 'run'):
            module.run(args)
        else:
            print(f"Error: {args.command} has no 'run' function.", file=sys.stderr)
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
