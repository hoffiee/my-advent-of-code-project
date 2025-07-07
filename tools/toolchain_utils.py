import os
import shutil


def remove_file_if_exists(file_path) -> None:
    if os.path.exists(file_path):
        os.remove(file_path)


def remove_dir_if_exists(dir_path) -> None:
    if not os.path.isdir(dir_path):
        return
    shutil.rmtree(dir_path)
