import subprocess

from tools.setup_conan import setup_conan
from tools.toolchain_utils import remove_dir_if_exists


def _setup_cmake(preset: str) -> None:
    cmd = f"cmake --preset {preset}".split()
    print(cmd)
    subprocess.run(cmd, check=True)


def setup_cmake(args=None, forward_args=None):
    print("setup_cmake")
    remove_dir_if_exists("build")
    setup_conan()
    _setup_cmake("debug")
    _setup_cmake("release")
