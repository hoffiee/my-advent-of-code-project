#!/usr/bin/env python3

import subprocess
import sys
sys.path.insert(0, subprocess.check_output(['git', 'rev-parse', '--show-toplevel']).decode().strip())

from argparse import Namespace


from tools.cmake_utils import cmake_build


args = Namespace(debug=True, release=False, targets=["all"])
res = cmake_build(args)
assert res == 0

args = Namespace(debug=False, release=True, targets=["all"])
res = cmake_build(args)
assert res == 0

print("All targets built succesfully")
