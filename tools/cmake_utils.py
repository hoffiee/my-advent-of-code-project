import os
import subprocess

from typing import List

from tools.conan_utils import setup_conan
from tools.toolchain_utils import remove_dir_if_exists


def _setup_cmake(preset: str) -> None:
    cmd = f"cmake --preset {preset}".split()
    print(cmd)
    subprocess.run(cmd, check=True)


def cmake_setup(args=None, forward_args=None) -> None:
    print("cmake_setup")
    remove_dir_if_exists("build")
    setup_conan()
    _setup_cmake("debug")
    _setup_cmake("release")


def cmake_build(args=None, forward_args=None) -> int:
    build_path = os.path.join("build/debug")
    if args.release:
        build_path = os.path.join("build/release")
    if not os.path.exists(build_path):
        cmake_setup(args, forward_args)
    result = subprocess.run(["ninja", *args.targets], cwd=build_path, check=True)
    return result.returncode


def cmake_fetch_targets(args=None, forward_args=None) -> List[str]:
    build_path = os.path.join("build/debug")
    if args.release:
        build_path = os.path.join("build/release")
    if not os.path.exists(build_path):
        cmake_setup(args, forward_args)

    result = subprocess.check_output(
        ["ninja", "-t", "targets"], cwd=build_path, text=True
    ).splitlines()

    # Remove internal targets and remove : phony etc.
    result = [line.split(":")[0] for line in result if "CMakeFiles" not in line]

    return result
