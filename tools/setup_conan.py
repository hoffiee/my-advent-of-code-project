import os
import subprocess

from tools.toolchain_utils import remove_file_if_exists


def _setup_conan(build_type: str) -> None:
    cmd = (
        f"conan install . -s build_type={build_type} --build=missing "
        f"--output-folder=build/{build_type.lower()}".split()
    )
    print(cmd)
    subprocess.run(cmd, check=True)


def setup_conan(args=None, forward_args=None) -> None:
    print("setup_conan")

    _setup_conan("Debug")
    _setup_conan("Release")
    remove_file_if_exists("CMakeUserPresets.json")
