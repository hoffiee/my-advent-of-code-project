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


def plot(part_df, logarithmic=False):
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
    if logarithmic:
        fig.update_yaxes(type="log", row=1, col=1)

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
    fig.update_yaxes(
        title_text=f"runtime {'(logarithmic) ' if logarithmic else ''}[ms]",
        row=1,
        col=1,
    )
    fig.update_yaxes(title_text="accumulated runtime [s]", row=2, col=1)
    fig.update_layout(title_text="Advent of Code runtimes")
    fig.show()


def biggest_contributor(year):
    conn = sqlite3.connect("bench.db")
    query = "SELECT * FROM entries"
    if year:
        query += " WHERE year == " + str(year)
    df = pd.read_sql_query(query, conn)
    conn.close()

    total_runtime_ms: float = df["mean_ms"].sum()
    biggest_contributors = df.sort_values(by="mean_ms", ascending=False).head(5)

    print("Top 5 contributors of runtime and their impact in percentage")
    for _, row in biggest_contributors.iterrows():
        print(
            f"{int(row['year'])}_day{int(row['day'])}\tpart {int(row['part'])}"
            + f"\t{int(row['mean_ms'])} ms {int(row['mean_ms']/total_runtime_ms*100.0)}%"
        )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-y",
        "--year",
        type=int,
        choices=range(2015, 2026),
        metavar="[2015-2024]",
        help="Specify year (optional)",
    )
    parser.add_argument(
        "--contributor",
        action="store_true",
        help="Check the 5 solutions that takes the most time.",
    )
    parser.add_argument(
        "--log",
        action="store_true",
        help="Use Logarithmic scale for individual runtime",
    )
    args = parser.parse_args()

    if args.contributor:
        biggest_contributor(args.year)
    else:
        df = get_data(args.year)
        plot(df, args.log)


if __name__ == "__main__":
    main()
