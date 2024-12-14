import datetime as dt
from typing import Final


def main() -> None:
    events_stars = {
        2024: 28,
        2023: 27,
        2022: 26,
        2021: 16,
        2020: 22,
        2019: 14,
        2018: 14,
        2017: 14,
        2016: 15,
        2015: 14,
    }
    targets_stars = {
        2024: 14,
        2023: 14,
        2022: 14,
        2021: 14,
        2020: 14,
        2019: 14,
        2018: 14,
        2017: 14,
        2016: 14,
        2015: 14,
    }

    TASKS_PER_YEAR: Final[int] = 50

    start_year: int = min(events_stars.keys())
    last_year: int = max(events_stars.keys())
    years: int = last_year - start_year + 1

    goal = {}
    for key in set([*events_stars.keys(), *targets_stars.keys()]):
        goal[key] = max(targets_stars.get(key, 0) - events_stars.get(key, 0), 0)

    out: str = f"Going on for {years} years\n"
    out += f"Completed {sum(events_stars.values())} tasks\n"
    out += f"completed {max(events_stars.values())} stars in year {max(events_stars.items())[0]}\n"
    out += (
        f"total of {TASKS_PER_YEAR*years - sum(events_stars.values())} left to complete"
    )
    print(out)

    print("Tasks left to complete")
    for key in sorted(goal.keys()):
        if goal[key] > 0:
            print(f"\t{key}: {goal[key]}")

    today = dt.datetime.today()
    endofyear = dt.datetime(today.year, 12, 31)
    print(f"in {(endofyear - today).days} days before the end of this year")


if __name__ == "__main__":
    main()
