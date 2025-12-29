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

targets_to_run = []
for target in targets:
    if target.endswith("-run"):
        targets_to_run.append(target)
targets_to_run = sorted(targets_to_run)

args.targets = [*targets_to_run]
cmake_build(args, None)
