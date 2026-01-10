import datetime as dt


def tasks_per_year(year: int) -> int:
    """Puzzles from 2025 is only 12 days"""
    if year >= 2025:
        return 24
    return 50


def eventStatus() -> None:
    events_stars = {
        2025: 24,
        2024: 50,
        2023: 44,
        2022: 30,
        2021: 30,
        2020: 30,
        2019: 26,
        2018: 20,
        2017: 20,
        2016: 21,
        2015: 30,
    }
    targets_stars = {
        2025: 24,
        2024: 50,
        2023: 50,
        2022: 30,
        2021: 30,
        2020: 30,
        2019: 30,
        2018: 30,
        2017: 30,
        2016: 30,
        2015: 30,
    }

    start_year: int = min(events_stars.keys())
    last_year: int = max(events_stars.keys())
    years: int = last_year - start_year + 1

    goal = {}
    for key in set([*events_stars.keys(), *targets_stars.keys()]):
        goal[key] = max(targets_stars.get(key, 0) - events_stars.get(key, 0), 0)

    out: str = f"Going on for {years} years"

    total_amount_of_stars: int = sum(
        [tasks_per_year(year) for year in range(start_year, last_year + 1)]
    )
    out += f" (available stars: {total_amount_of_stars})\n"
    out += f"Got a total of {sum(events_stars.values())} stars, "
    out += f"got {events_stars.get(last_year)} stars in year {max(events_stars.items())[0]}\n"
    out += (
        f"total of {sum(targets_stars.values()) - sum(events_stars.values())} stars left to complete to reach targets"
        + f" ({sum(targets_stars.values()) - sum(events_stars.values())} in total)"
    )
    print(out)

    print(f"Stars left to complete: {sum(goal.values())}")
    for key in sorted(goal.keys(), reverse=True):
        if goal[key] > 0:
            print(f"\t{key}: {goal[key]}")

    today = dt.datetime.today()
    endofyear = dt.datetime(today.year, 12, 31)
    print(f"in {(endofyear - today).days} days before the end of this year")


def register_subcommand(subparsers):
    parser = subparsers.add_parser(
        "status",
        description="Displays star targets and status",
        help="Displays star targets and status",
    )


def run(args):
    eventStatus()
