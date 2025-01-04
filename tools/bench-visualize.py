"""
Run from root of repo `python3 tools/bench-visualize.py`
"""
import sqlite3
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots


conn = sqlite3.connect('bench.db')
part1 = "SELECT * FROM entries WHERE year == 2024 AND part == 1"
part2 = "SELECT * FROM entries WHERE year == 2024 AND part == 2"
part1_df = pd.read_sql_query(part1, conn)
part2_df = pd.read_sql_query(part2, conn)
conn.close()

print(part1_df)
print(f"total runtime part1: {part1_df['mean_ms'].sum()} ms")
print(part2_df)
print(f"total runtime part2: {part2_df['mean_ms'].sum()} ms")
print(part2_df["mean_ms"].cumsum())

fig = make_subplots(rows=2, cols=1, shared_xaxes=False)
fig.add_trace(
    go.Bar(
        x=part1_df["day"],
        y=part1_df["mean_ms"],
        name="part 1"
    ), row=1, col=1
)

fig.add_trace(
    go.Bar(
        x=part2_df["day"],
        y=part2_df["mean_ms"],
        name="part 2"
    ), row=1, col=1
)

fig.add_trace(
    go.Bar(
        x=part2_df["day"],
        y=part1_df["mean_ms"] + part2_df["mean_ms"],
        name="total"
    ), row=1, col=1
)

fig.add_trace(
    go.Scatter(
        x=part1_df["day"],
        y=part1_df["mean_ms"].cumsum()/1000.0,
        mode="lines",
        name="part 1",
    ), row=2, col=1
)

fig.add_trace(
    go.Scatter(
        x=part2_df["day"],
        y=part2_df["mean_ms"].cumsum()/100.0,
        mode="lines",
        name="part 2",
    ), row=2, col=1
)

fig.add_trace(
    go.Scatter(
        x=part2_df["day"],
        y=(part1_df["mean_ms"] + part2_df["mean_ms"]).cumsum()/1000.0,
        mode="lines",
        name="total",
    ), row=2, col=1
)

fig.update_xaxes(dtick=1, title_text="[day]", row=2, col=1)
fig.update_xaxes(dtick=1, row=1, col=1)
fig.update_yaxes(title_text="runtime [ms]", row=1, col=1)
fig.update_yaxes(title_text="accumulated runtime [s]", row=2, col=1)
fig.update_layout(title_text='Advent of Code 2024 runtimes')
fig.show()
