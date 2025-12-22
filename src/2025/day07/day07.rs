use std::collections::HashMap;

use aoc_runner::aoc_run;
use aoc_utils::*;

// #[derive(Debug, Clone, PartialEq, Eq, Hash, Copy)]
// struct Point {
//     x: i32,
//     y: i32,
// }
//
// #[derive(Debug, Clone, PartialEq, Eq, Hash, Copy)]
// struct Point(pub Point2d);
//
type Point = Point2d;

trait ValidPoint {
    fn is_valid(&self, dim: &Point) -> bool;
    fn next(&self, dim: &Point) -> Option<Point>;
}

impl ValidPoint for Point {
    fn is_valid(&self, dim: &Point) -> bool {
        if (self.x < 0) || (dim.x <= self.x) {
            return false;
        }
        if (self.y < 0) || (dim.y <= self.y) {
            return false;
        }
        true
    }

    fn next(&self, dim: &Point) -> Option<Point> {
        let cand = Point {
            x: self.x,
            y: self.y + 1,
        };
        if cand.is_valid(dim) { Some(cand) } else { None }
    }
}

fn parse_input(input: &Vec<String>) -> (HashMap<Point, i64>, Point, Point) {
    let dim = Point {
        x: input[0].len() as i64,
        y: input.len() as i64,
    };

    let points = extract_points_from_map::<i64>(&input, &vec!['S', '^']);
    assert!(points.len() == 2);

    let start = points.get(&'S')
        .and_then(|inner| inner.keys().next().copied())
        .expect("Expected a starting point from S");
    assert!(start.x != 0);

    let splits = points.get(&'^').unwrap().clone();
    assert!(splits.len() > 0);

    (splits, dim, start)
}

fn propagate(
    beams: &mut HashMap<Point, bool>,
    splits: &HashMap<Point, i64>,
    point: &Point,
    dim: &Point,
) {
    if beams.contains_key(&point) {
        return;
    }

    if splits.contains_key(&point) {
        // TODO Implement a left/right function for Point
        let left_point = Point {
            x: point.x - 1,
            y: point.y,
        };
        let right_point = Point {
            x: point.x + 1,
            y: point.y,
        };

        if left_point.is_valid(&dim) {
            propagate(beams, &splits, &left_point, &dim);
            beams.insert(left_point, true);
        };
        if right_point.is_valid(&dim) {
            propagate(beams, &splits, &right_point, &dim);
            beams.insert(left_point, true);
        }
    } else {
        if let Some(np) = point.next(&dim) {
            propagate(beams, &splits, &np, &dim);
        }
    }
}

fn quantum_propagate(
    beams: &mut HashMap<Point, i64>,
    splits: &HashMap<Point, i64>,
    point: &Point,
    dim: &Point,
) -> i64 {
    if beams.contains_key(&point) {
        return *beams.get(&point).unwrap();
    }

    if splits.contains_key(&point) {
        let left_point = Point {
            x: point.x - 1,
            y: point.y,
        };
        let right_point = Point {
            x: point.x + 1,
            y: point.y,
        };

        let mut sum = 0;
        if left_point.is_valid(&dim) {
            let left_nr_paths = quantum_propagate(beams, &splits, &left_point, &dim);
            beams.insert(left_point, left_nr_paths);
            sum += left_nr_paths;
        };
        if right_point.is_valid(&dim) {
            let right_nr_paths = quantum_propagate(beams, &splits, &right_point, &dim);
            beams.insert(right_point, right_nr_paths);
            sum += right_nr_paths;
        }
        sum
    } else {
        if let Some(np) = point.next(&dim) {
            quantum_propagate(beams, &splits, &np, &dim)
        } else {
            1
        }
    }
}

fn solve_1(input: &Vec<String>) -> i64 {
    let (splits, dim, start) = parse_input(input);

    let mut beams: HashMap<Point, bool> = HashMap::new();
    propagate(&mut beams, &splits, &start, &dim);

    beams.len() as i64
}

fn solve_2(input: &Vec<String>) -> i64 {
    let (splits, dim, start) = parse_input(input);

    let mut beams: HashMap<Point, i64> = HashMap::new();
    let paths = quantum_propagate(&mut beams, &splits, &start, &dim);

    paths
}

fn samples() {
    let lines = read_input_file("day07-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 21);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 40);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day07.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 1581);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 73007003089792);
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
    fn solve_2_test_1() {
        let lines = vec![
            ".S.".to_string(),
            "...".to_string(),
            ".^.".to_string(),
            "...".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 2);
    }

    #[test]
    fn solve_2_test_2() {
        let lines = vec![
            ".S.".to_string(),
            "...".to_string(),
            ".^.".to_string(),
            "...".to_string(),
            "^.^".to_string(),
            "...".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 2);
    }

    #[test]
    fn solve_2_test_3() {
        let lines = vec![
            "..S..".to_string(),
            ".....".to_string(),
            "..^..".to_string(),
            ".....".to_string(),
            ".^.^.".to_string(),
            ".....".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 4);
    }

    #[test]
    fn solve_2_test_4() {
        let lines = vec![
            "..S..".to_string(),
            ".....".to_string(),
            "..^..".to_string(),
            ".....".to_string(),
            ".^.^.".to_string(),
            ".....".to_string(),
            "..^..".to_string(),
            ".....".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 6);
    }

    #[test]
    fn solve_2_test_5() {
        let lines = vec![
            "...S..".to_string(),
            "......".to_string(),
            "...^..".to_string(),
            "......".to_string(),
            "..^.^.".to_string(),
            "......".to_string(),
            ".^....".to_string(),
            "......".to_string(),
            "...^..".to_string(),
            "......".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 7);
    }

    #[test]
    fn solve_2_test_6() {
        let lines = vec![
            "...S...".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            ".^.^.^.".to_string(),
            ".......".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 8);
    }

    #[test]
    fn solve_2_test_7() {
        let lines = vec![
            "...S...".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            ".^.^.^.".to_string(),
            ".......".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 8);
    }

    #[test]
    fn solve_2_test_8() {
        let lines = vec![
            "...S...".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            ".^...^.".to_string(),
            ".......".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 6);
    }

    #[test]
    fn solve_2_test_9() {
        let lines = vec![
            "...S...".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 6);
    }

    #[test]
    fn solve_2_test_10() {
        let lines = vec![
            "...S...".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            ".^.^.^.".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 14);
    }

    #[test]
    fn solve_2_test_11() {
        let lines = vec![
            "...S...".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            ".^.^.^.".to_string(),
            ".......".to_string(),
            "..^.^..".to_string(),
            ".......".to_string(),
            "...^...".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 20);
    }
}
