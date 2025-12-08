use std::cmp::Reverse;
use std::collections::BinaryHeap;
use std::collections::HashMap;
use std::str::FromStr;

use aoc_runner::aoc_run;
use aoc_utils::*;

#[derive(Debug, Clone, PartialEq, Eq, Hash, Copy, Ord, PartialOrd)]
struct Point {
    x: i64,
    y: i64,
    z: i64,
}

#[derive(Debug)]
struct ParsePointError;

impl std::fmt::Display for ParsePointError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "invalid point format")
    }
}

impl std::error::Error for ParsePointError {}

impl Point {
    fn distance(&self, other: &Point) -> i64 {
        let dx = self.x - other.x;
        let dy = self.y - other.y;
        let dz = self.z - other.z;

        let dx2 = dx * dx;
        let dy2 = dy * dy;
        let dz2 = dz * dz;

        // No need to square as we're only interested in relation between distances
        dx2 + dy2 + dz2
    }
}

impl FromStr for Point {
    type Err = ParsePointError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let trimmed = s.trim_matches(|c| c == '(' || c == ')');
        let parts: Vec<&str> = trimmed.split(',').collect();
        if parts.len() != 3 {
            return Err(ParsePointError);
        }
        let x = parts[0].parse().map_err(|_| ParsePointError)?;
        let y = parts[1].parse().map_err(|_| ParsePointError)?;
        let z = parts[2].parse().map_err(|_| ParsePointError)?;
        Ok(Point { x, y, z })
    }
}

fn count_occurrences(input: &HashMap<impl Eq + std::hash::Hash, i64>) -> Vec<(i64, i64)> {
    let mut counts = HashMap::new();
    for &value in input.values() {
        *counts.entry(value).or_insert(0) += 1;
    }

    let mut sorted: Vec<(i64, i64)> = counts.into_iter().collect();
    sorted.sort_by_key(|(_, d)| -*d);
    sorted
}

fn update_matching_values(map: &mut HashMap<Point, i64>, target: i64, new: i64) {
    for (_, value) in map.iter_mut() {
        if *value == target {
            *value = new;
        }
    }
}

fn min_tree_edges(points: &Vec<Point>) -> BinaryHeap<(Reverse<i64>, (Point, Point))> {
    let mut distances: BinaryHeap<(Reverse<i64>, (Point, Point))> = BinaryHeap::new();
    for i in 0..points.len() {
        for j in i..points.len() {
            if i == j {
                continue;
            }
            let dist = points[i].distance(&points[j]);
            distances.push((Reverse(dist), (points[i].clone(), points[j].clone())));
        }
    }
    distances
}

fn solve_1(input: &Vec<String>, nr_of_connections: usize) -> i64 {
    let points = input
        .iter()
        .map(|c| c.parse().unwrap())
        .collect::<Vec<Point>>();
    assert!(points.len() > 0);

    let mut distances = min_tree_edges(&points);

    let mut circuits: HashMap<Point, i64> = HashMap::new();
    let mut circuit_count = 0;
    for _ in 0..nr_of_connections {
        let (Reverse(_), (p1, p2)) = distances.pop().unwrap();

        if circuits.contains_key(&p1) && circuits.contains_key(&p2) {
            let circuit1: i64 = *circuits.get(&p1).unwrap();
            let circuit2: i64 = *circuits.get(&p2).unwrap();
            if circuit1 == circuit2 {
                continue;
            }
            update_matching_values(&mut circuits, circuit1, circuit2);
        } else if circuits.contains_key(&p1) {
            circuits.insert(p2.clone(), *circuits.get(&p1).unwrap());
        } else if circuits.contains_key(&p2) {
            circuits.insert(p1.clone(), *circuits.get(&p2).unwrap());
        } else {
            circuit_count += 1;
            circuits.insert(p1.clone(), circuit_count);
            circuits.insert(p2.clone(), circuit_count);
        }
    }

    let freq = count_occurrences(&circuits);
    assert!(freq.len() > 3);
    freq[0].1 * freq[1].1 * freq[2].1
}

fn solve_2(input: &Vec<String>) -> i64 {
    let points = input
        .iter()
        .map(|c| c.parse().unwrap())
        .collect::<Vec<Point>>();
    assert!(points.len() > 0);

    let mut distances = min_tree_edges(&points);

    let mut circuits: HashMap<Point, i64> = HashMap::new();
    let mut circuits_clusters: HashMap<i64, i64> = HashMap::new();
    circuits_clusters.insert(0, points.len() as i64);
    let mut circuit_count = 0;

    while let Some((Reverse(_), (p1, p2))) = distances.pop() {
        if circuits.contains_key(&p1) && circuits.contains_key(&p2) {
            let circuit1: i64 = *circuits.get(&p1).unwrap();
            let circuit2: i64 = *circuits.get(&p2).unwrap();
            if circuit1 == circuit2 {
                continue;
            }

            assert!(circuits_clusters.len() >= 2);

            update_matching_values(&mut circuits, circuit1, circuit2);
            circuits_clusters.remove(&circuit1);

            if circuits_clusters.len() == 1 {
                return p1.x * p2.x;
            }
        } else if circuits.contains_key(&p1) {
            circuits.insert(p2.clone(), *circuits.get(&p1).unwrap());
            *circuits_clusters.get_mut(&0).unwrap() -= 1;
        } else if circuits.contains_key(&p2) {
            circuits.insert(p1.clone(), *circuits.get(&p2).unwrap());
            *circuits_clusters.get_mut(&0).unwrap() -= 1;
        } else {
            circuit_count += 1;
            circuits_clusters.insert(circuit_count.clone(), 0);
            circuits.insert(p1.clone(), circuit_count);
            circuits.insert(p2.clone(), circuit_count);
            *circuits_clusters.get_mut(&0).unwrap() -= 2;
        }

        if circuits_clusters.contains_key(&0) && *circuits_clusters.get(&0).unwrap() == 0 {
            circuits_clusters.remove(&0);
            if circuits_clusters.len() == 1 {
                return p1.x * p2.x;
            }
        }
    }

    0
}

fn samples() {
    let lines = read_input_file("day08-sample.input");

    let sample_part_1 = solve_1(&lines, 10);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 40);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 25272);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day08.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines, 1000);
        println!("part1: {}", ans);
        assert_eq!(ans, 105952);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 975931446);
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
    fn test_point_parse() {
        let p: Point = "10,20,-30".parse().unwrap();

        assert_eq!(p.x, 10);
        assert_eq!(p.y, 20);
        assert_eq!(p.z, -30);
    }
}
