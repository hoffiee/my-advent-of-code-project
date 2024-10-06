from collections import defaultdict


def distance(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return abs(x2 - x1) + abs(y2 - y1)


def get_closest(points, point):
    candidates = [distance(point, p1) for p1 in points]
    candidates_sorted = sorted(candidates)
    if candidates_sorted[0] == candidates_sorted[1]:
        return "."
    return str(candidates.index(candidates_sorted[0]))


def calculate_distance(points, point):
    candidates = [distance(point, p1) for p1 in points]
    if sum(candidates) < 10000:
        return "#"
    return "."


def preprocess(data):
    points = []
    grid = {}

    xlim = [float("inf"), float("-inf")]
    ylim = [float("inf"), float("-inf")]
    for it in data:
        x, y = map(int, it.split(", "))
        xlim[0] = min(xlim[0], x)
        xlim[1] = max(xlim[1], x)
        ylim[0] = min(ylim[0], y)
        ylim[1] = max(ylim[1], y)
        points.append((x, y))

    x_offset = xlim[0]
    y_offset = ylim[0]
    offsets = (x_offset, y_offset)

    outer_points = []
    for point1 in points:
        smallest_x: bool = True
        largest_x: bool = True
        smallest_y: bool = True
        largest_y: bool = True

        for point2 in points:
            if point1 == point2:
                continue

            smallest_x = smallest_x and point1[0] <= point2[0]
            largest_x = largest_x and point1[0] >= point2[0]
            smallest_y = smallest_y and point1[1] <= point2[1]
            largest_y = largest_y and point1[1] >= point2[1]

        if smallest_x or largest_x or smallest_y or largest_y:
            outer_points.append(point1)

    x_dim = xlim[1] - xlim[0] + 1
    y_dim = ylim[1] - ylim[0] + 1
    dims = (x_dim, y_dim)

    grid = []
    for y in range(y_dim):
        grid.append(["."] * x_dim)

    for i, point in enumerate(points):
        x, y = point
        grid[y - y_offset][x - x_offset] = str(i)

    return grid, points, dims, offsets


def sol1(grid, points, offsets, dims):
    x_dim, y_dim = dims
    x_offset, y_offset = offsets

    # populate grid
    count = defaultdict(int)
    for y in range(y_dim):
        for x in range(x_dim):
            if grid[y][x] != ".":
                continue
            grid[y][x] = get_closest(points, (x + x_offset, y + y_offset))
            count[grid[y][x]] += 1
    print(f"sol1: {max(count.values())+1}")


def sol2(grid, points, offsets, dims):
    x_dim, y_dim = dims
    x_offset, y_offset = offsets

    count = defaultdict(int)
    for y in range(y_dim):
        for x in range(x_dim):
            # We want to include the point in the count, so set check that for distances too
            grid[y][x] = calculate_distance(points, (x + x_offset, y + y_offset))
            count[grid[y][x]] += 1
    print(f'sol2: {count["#"]}')


def main() -> None:
    for filename in ["day06-sample.input", "day06.input"]:
        with open(filename, "r", encoding="utf8") as file:
            lines = file.read().splitlines()

            print(f"file: {filename}")
            grid, points, dims, offsets = preprocess(lines)
            sol1(grid.copy(), points.copy(), offsets, dims)
            sol2(grid.copy(), points.copy(), offsets, dims)


if __name__ == "__main__":
    main()
