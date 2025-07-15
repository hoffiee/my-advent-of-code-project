import datetime as dt
from typing import Final


def eventStatus() -> None:
    events_stars = {
        2024: 50,
        2023: 44,
        2022: 26,
        2021: 20,
        2020: 23,
        2019: 20,
        2018: 20,
        2017: 20,
        2016: 21,
        2015: 30,
    }
    targets_stars = {
        2024: 50,
        2023: 30,
        2022: 30,
        2021: 30,
        2020: 30,
        2019: 30,
        2018: 30,
        2017: 30,
        2016: 30,
        2015: 30,
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

    print(f"Tasks left to complete: {sum(goal.values())}")
    for key in sorted(goal.keys()):
        if goal[key] > 0:
            print(f"\t{key}: {goal[key]}")

    today = dt.datetime.today()
    endofyear = dt.datetime(today.year, 12, 31)
    print(f"in {(endofyear - today).days} days before the end of this year")


__all__ = ["eventStatus"]

if __name__ == "__main__":
    eventStatus()
