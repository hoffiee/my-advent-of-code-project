use std::collections::HashMap;

use aoc_runner::aoc_run;
use aoc_utils::*;

// TODO Generalize and move utils
#[derive(Debug, Clone, PartialEq, Eq, Hash, Copy, PartialOrd, Ord)]
struct Point {
    x: i64,
    y: i64,
}

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
struct Rectangle {
    min: Point,
    max: Point,
}

impl Rectangle {
    fn new(p1: Point, p2: Point) -> Self {
        let lower_left = Point {
            x: std::cmp::min(p1.x, p2.x),
            y: std::cmp::min(p1.y, p2.y),
        };
        let upper_right = Point {
            x: std::cmp::max(p1.x, p2.x),
            y: std::cmp::max(p1.y, p2.y),
        };
        Self {
            min: lower_left,
            max: upper_right,
        }
    }

    fn area(&self) -> i64 {
        (self.max.x - self.min.x + 1) * (self.max.y - self.min.y + 1)
    }
}

fn parse_input(input: &Vec<String>) -> Vec<Point> {
    let mut points: Vec<Point> = Vec::new();
    for line in input {
        let xy: Vec<i64> = line
            .trim()
            .split(',')
            .map(|s| s.parse::<i64>().unwrap())
            .collect();
        assert_eq!(xy.len(), 2);

        points.push(Point { x: xy[0], y: xy[1] });
    }
    points
}

fn solve_1(input: &Vec<String>) -> i64 {
    let corners = parse_input(&input);
    assert!(corners.len() > 0);

    let mut largest = 0;
    for i in 0..corners.len() {
        for j in i..corners.len() {
            if i == j {
                continue;
            }

            let rect = Rectangle::new(corners[i], corners[j]);
            if rect.area() > largest {
                largest = rect.area();
            }
        }
    }

    largest
}

#[derive(Debug, Clone)]
struct Polygon {
    points: Vec<Point>,
}

impl Polygon {
    fn new(points: Vec<Point>) -> Self {
        let mut closed_points = points;

        // If it's not closed, add first point again to close it
        if !closed_points.is_empty() && closed_points[0] != *closed_points.last().unwrap() {
            closed_points.push(closed_points[0]);
        }
        Self {
            points: closed_points,
        }
    }

    fn contains(&self, r: &Rectangle) -> bool {
        let n = self.points.len();

        for i in 0..n {
            // Consider the line as a "box" where one dimension is only 1 wide
            let p1 = self.points[i];
            let p2 = self.points[(i + 1) % n];

            let xmin = std::cmp::min(p1.x, p2.x);
            let ymin = std::cmp::min(p1.y, p2.y);
            let xmax = std::cmp::max(p1.x, p2.x);
            let ymax = std::cmp::max(p1.y, p2.y);

            // So it converged to an Axis-aligned Bounding Box AABB collision check, if any line
            // intersects with the internals of the rectangle, then this rectangle is not entirely contained
            // within the polygon
            if r.min.x < xmax && r.max.x > xmin && r.min.y < ymax && r.max.y > ymin {
                return false;
            }
        }
        true
    }
}

fn solve_2(input: &Vec<String>) -> i64 {
    let corners = parse_input(&input);
    assert!(corners.len() > 0);

    let grid = Polygon::new(corners.clone());
    let mut grid_hash: HashMap<Point, bool> = HashMap::new();

    for corner in &corners {
        grid_hash.insert(corner.clone(), true);
    }

    let mut largest = 0;
    for i in 0..corners.len() {
        for j in i..corners.len() {
            if i == j {
                continue;
            }

            let rect = Rectangle::new(corners[i], corners[j]);

            if rect.area() <= largest {
                continue;
            }
            if !grid.contains(&rect) {
                continue;
            }

            largest = rect.area();
        }
    }

    largest
}

fn samples() {
    let lines = read_input_file("day09-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 50);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 24);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day09.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 4745816424);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 1351617690);
    };

    aoc_run(samples, solve_1_wrapper, solve_2_wrapper, lines)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn smoke() {
        assert!(true);
    }

    #[test]
    fn test_area() {
        let rect = Rectangle::new(Point { x: 2, y: 5 }, Point { x: 9, y: 7 });
        assert_eq!(rect.area(), 24);
    }

    #[test]
    fn test_solve_2_1() {
        let inp: Vec<String> = vec![
            "1,1".to_string(),
            "5,1".to_string(),
            "5,5".to_string(),
            "1,5".to_string(),
        ];
        let ans = solve_2(&inp);
        assert_eq!(ans, 25);
    }

    #[test]
    fn test_solve_2_2() {
        let inp: Vec<String> = vec![
            "1,1".to_string(),
            "5,1".to_string(),
            "5,3".to_string(),
            "3,3".to_string(),
            "3,5".to_string(),
            "1,5".to_string(),
        ];
        let ans = solve_2(&inp);
        assert_eq!(ans, 15);
    }

    #[test]
    fn test_solve_2_3() {
        let inp: Vec<String> = vec![
            "1,1".to_string(),
            "7,1".to_string(),
            "7,5".to_string(),
            "5,5".to_string(),
            "5,3".to_string(),
            "3,3".to_string(),
            "3,5".to_string(),
            "1,5".to_string(),
        ];
        let ans = solve_2(&inp);
        assert_eq!(ans, 15);
    }
}
