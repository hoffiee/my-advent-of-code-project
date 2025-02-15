"""
Run from root of repo `python3 tools/bench-visualize.py`
"""

import sqlite3
import argparse
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots


def get_data(year):
    conn = sqlite3.connect("bench.db")
    query = "SELECT * FROM entries WHERE "
    if year:
        query += "year == " + str(year) + " AND "
    query += "part == "

    part1_df = pd.read_sql_query(query + "1", conn)
    part2_df = pd.read_sql_query(query + "2", conn)
    conn.close()

    part1_df["entry"] = (
        part1_df["year"].astype(str) + "_day" + part1_df["day"].astype(str).str.zfill(2)
    )
    part2_df["entry"] = (
        part2_df["year"].astype(str) + "_day" + part2_df["day"].astype(str).str.zfill(2)
    )

    part_df = pd.merge(part1_df, part2_df, on="entry", suffixes=("_1", "_2"))
    part_df.sort_values(by="entry", inplace=True)

    return part_df


def plot(part_df):
    fig = make_subplots(rows=2, cols=1, shared_xaxes=False)
    fig.add_trace(
        go.Bar(x=part_df["entry"], y=part_df["mean_ms_1"], name="part 1"), row=1, col=1
    )

    fig.add_trace(
        go.Bar(x=part_df["entry"], y=part_df["mean_ms_2"], name="part 2"), row=1, col=1
    )

    fig.add_trace(
        go.Bar(
            x=part_df["entry"],
            y=part_df["mean_ms_1"] + part_df["mean_ms_2"],
            name="total",
        ),
        row=1,
        col=1,
    )

    fig.add_trace(
        go.Scatter(
            x=part_df["entry"],
            y=part_df["mean_ms_1"].cumsum() / 1000.0,
            mode="lines",
            name="part 1",
        ),
        row=2,
        col=1,
    )

    fig.add_trace(
        go.Scatter(
            x=part_df["entry"],
            y=part_df["mean_ms_2"].cumsum() / 1000.0,
            mode="lines",
            name="part 2",
        ),
        row=2,
        col=1,
    )

    fig.add_trace(
        go.Scatter(
            x=part_df["entry"],
            y=(part_df["mean_ms_1"] + part_df["mean_ms_2"]).cumsum() / 1000.0,
            mode="lines",
            name="total",
        ),
        row=2,
        col=1,
    )

    fig.update_xaxes(dtick=1, title_text="[day]", row=2, col=1)
    fig.update_xaxes(dtick=1, row=1, col=1)
    fig.update_yaxes(title_text="runtime [ms]", row=1, col=1)
    fig.update_yaxes(title_text="accumulated runtime [s]", row=2, col=1)
    fig.update_layout(title_text="Advent of Code runtimes")
    fig.show()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-y",
        "--year",
        type=int,
        choices=range(2015, 2025),
        metavar="[2015-2024]",
        help="Specify year (optional)",
    )
    args = parser.parse_args()

    df = get_data(args.year)
    plot(df)


if __name__ == "__main__":
    main()
