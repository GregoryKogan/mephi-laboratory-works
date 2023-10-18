import pathlib
from collections import defaultdict
import os
import subprocess


ALLOWED_SUFFIXES = [
    ".c",
    ".h",
    ".cpp",
    ".hpp",
    ".hh",
    ".py",
    ".sh",
    ".js",
    ".ts",
    ".html",
    ".css",
    ".md",
    ".vue",
]
MAX_DEPTH = 2


def count_lines_of_code_in_file(path: pathlib.Path) -> int:
    with open(path, "r") as f:
        lines = f.readlines()
    return len(lines)


def count_lines_of_code(paths: list, base_path: pathlib.Path) -> list:
    dirs = []
    for path in paths:
        parent_dirs = path.parents
        for directory in parent_dirs:
            if directory != base_path and base_path not in directory.parents:
                continue
            depth = len(directory.relative_to(base_path).parts)
            if directory not in [d["path"] for d in dirs]:
                dirs.append(
                    {"path": directory, "depth": depth, "lines": defaultdict(int)}
                )

    for file in paths:
        if file.suffix in ALLOWED_SUFFIXES:
            for directory in dirs:
                if directory["path"] in file.parents:
                    directory["lines"][file.suffix] += count_lines_of_code_in_file(file)

    dirs = list(filter(lambda x: x["depth"] <= MAX_DEPTH, dirs))
    dirs = list(filter(lambda x: sum(x["lines"].values()) > 0, dirs))
    dirs.sort(key=lambda x: x["depth"])

    return dirs


def get_all_files(path: pathlib.Path) -> list:
    os.chdir(path)
    list_of_files = subprocess.check_output("git ls-files", shell=True).splitlines()
    return [path.joinpath(pathlib.Path(file.decode("utf-8"))) for file in list_of_files]


def main():
    base_path = pathlib.Path(__file__).parent.parent
    paths = get_all_files(base_path)
    dirs = count_lines_of_code(paths, base_path)

    for directory in dirs:
        depth = directory["depth"]
        print(f"{depth * '|__'}{directory['path'].relative_to(base_path)}")
        for suffix, lines in sorted(directory["lines"].items()):
            print(f"|{depth * '  '}{suffix}: {lines}")
        print(f"|{depth * '  '}Total: {sum(directory['lines'].values())}")
        print("|")


if __name__ == "__main__":
    main()
