#!/usr/bin/env python3

"""This test is intended to run all solutions, and as all are implemented in
such a way that they'll assert if they are incorrect, it's enough to kind of
just run all solutions and see if any exists with a non-zero exit code.
"""

# TODO: fails when one of the targets fails

import subprocess
import sys
from argparse import Namespace
sys.path.insert(0, subprocess.check_output(['git', 'rev-parse', '--show-toplevel']).decode().strip())

from tools.cmake_utils import cmake_build, cmake_fetch_targets

args = Namespace(debug=True, release=False, targets=["all"])
targets = cmake_fetch_targets(args, None)

disabled = [
    "2020_day15-py-run",  # slow, takes too long
    "2022_day14-run",  # Broken
    "2022_day18-run",  # Broken
    "2022_day21-py-run",  # Fix so it runs the parts separately
    "2024_day17-run",  #  Fix as it's not behaving as expected
    "2024_day21-run",  # Get's segmentation fault with --release
    "2024_day22-run",  # Fix address fault
    "2024_day24-run",  # Fix shift exponent fault
    "2017_day07-py-run",  # intermittent? Didn't fail when I ran it myself but failed once through this job
    "2019_day14-run",  # Not complete
    "2023_day19-run",  # Not complete
]

targets_to_run = []
for target in targets:
    if target.endswith("-run") and target not in disabled:
        targets_to_run.append(target)
targets_to_run = sorted(targets_to_run)

args.targets = [*targets_to_run]
cmake_build(args, None)

args.debug = False
args.release = True
cmake_build(args, None)
