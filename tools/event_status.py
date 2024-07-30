import datetime as dt
from typing import Final


def main() -> None:
    events_stars = {
        2023: 27,
        2022: 26,
        2021: 10,
        2020: 22,
        2019: 10,
        2018: 10,
        2017: 10,
        2016: 11,
        2015: 14,
    }
    targets_stars = {
        2023: 10,
        2022: 10,
        2021: 10,
        2020: 10,
        2019: 10,
        2018: 10,
        2017: 10,
        2016: 10,
        2015: 10,
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
    for k, v in goal.items():
        if v > 0:
            print(f"\t{k}: {v}")

    today = dt.datetime.today()
    endofyear = dt.datetime(today.year, 12, 31)
    print(f"in {(endofyear - today).days} days before the end of this year")


if __name__ == "__main__":
    main()
