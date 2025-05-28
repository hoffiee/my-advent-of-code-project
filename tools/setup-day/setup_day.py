import argparse
import os
from jinja2 import Environment, FileSystemLoader, StrictUndefined


def puzzle_inputs(year_in, day_in):
    """
    Create the dir and empty files, don't modify the file if it already exists
    """
    assert len(year_in) == 1
    assert len(day_in) == 1

    year = str(year_in[0])
    day = str(day_in[0])

    aoc_inputs_path = os.path.join("aoc-puzzle-inputs", year)
    input_path = os.path.join("aoc-puzzle-inputs", year, f"day{day}.input")
    sample_path = os.path.join("aoc-puzzle-inputs", year, f"day{day}-sample.input")

    os.makedirs(aoc_inputs_path, exist_ok=True)
    open(input_path, "a").close()
    open(sample_path, "a").close()


def create_year(year_in):
    """
    If year[in] doesn't exist, this will create a new directory in `src/` and
    setup a new CMakeLists.txt
    """
    assert len(year_in) == 1
    year = str(year_in[0])

    path = os.path.join("src", year)
    if not os.path.exists(path):
        print(f"create {path} and append to src/CMakeLists.txt")
        os.makedirs(path)

        env = Environment(
            loader=FileSystemLoader("tools/setup-day/templates"),
            undefined=StrictUndefined,
        )
        template = env.get_template("year.CMakeLists.txt.jinja")
        rendered_content = template.render(year=year)

        output_path = os.path.join("src", year, "CMakeLists.txt")
        with open(output_path, "w", encoding="utf-8") as f:
            f.write(rendered_content)

        with open(os.path.join("src", "CMakeLists.txt"), "a", encoding="utf-8") as f:
            f.write(f"\nadd_subdirectory({year})\n")


def create_day_cpp(year, day):
    cmakelists_path = os.path.join("src", year, f"day{day}", "CMakeLists.txt")
    if not os.path.exists(cmakelists_path):
        print(f"create {cmakelists_path}")
        env = Environment(
            loader=FileSystemLoader("tools/setup-day/templates"),
            undefined=StrictUndefined,
        )
        template = env.get_template("day.CMakeLists.txt.jinja")
        rendered_content = template.render(year=year, lang="cpp")

        with open(cmakelists_path, "w", encoding="utf-8") as f:
            f.write(rendered_content)

    cpp_path = os.path.join("src", year, f"day{day}", f"day{day}.cpp")
    print(f"create {cpp_path}")
    if not os.path.exists(cpp_path):
        env = Environment(
            loader=FileSystemLoader("tools/setup-day/templates"),
            undefined=StrictUndefined,
        )
        template = env.get_template("day.cpp.jinja")
        rendered_content = template.render(
            day_int=int(day), day=day, year=year, lang="cpp"
        )
        with open(cpp_path, "w", encoding="utf-8") as f:
            f.write(rendered_content)


def _create_day_python(day):
    # Not implemented yet
    assert False


def create_day(year_in, day_in, lang_in):
    """
    Creates a new dir for the day unless it already exists.
    """
    assert len(year_in) == 1
    assert len(day_in) == 1
    assert len(lang_in) == 1
    year = str(year_in[0])
    day = f"{int(day_in[0]):02d}"
    lang = str(lang_in[0])

    path = os.path.join("src", year, f"day{day}")
    if not os.path.exists(path):
        print(f"create {path} and append to src/{year}/CMakeLists.txt")
        os.makedirs(path)

        with open(
            os.path.join("src", year, "CMakeLists.txt"), "a", encoding="utf-8"
        ) as f:
            f.write(f"\nadd_subdirectory(day{day})\n")

    match lang:
        case "cpp":
            create_day_cpp(year, day)
        case "py":
            create_day_python(year, day)
        case _:
            assert False


def main():
    parser = argparse.ArgumentParser(description="Setup template for a new day")
    parser.add_argument(
        "year",
        nargs=1,
        type=int,
        choices=range(2015, 2026),
        metavar="YEAR",
        help="Year 2014",
    )
    parser.add_argument(
        "day", nargs=1, type=int, choices=range(1, 26), metavar="DAY", help="day"
    )
    parser.add_argument("lang", nargs=1, type=str, choices=["cpp"], help="language")
    args = parser.parse_args()

    create_year(args.year)
    create_day(args.year, args.day, args.lang)
    puzzle_inputs(args.year, args.day)


if __name__ == "__main__":
    main()
