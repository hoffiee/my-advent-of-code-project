use std::collections::HashMap;
use std::collections::VecDeque;

use aoc_runner::aoc_run;
use aoc_utils::*;

type Nodes = HashMap<String, bool>;
type Graph = HashMap<String, Nodes>;

fn parse_graph(input: &Vec<String>) -> Graph {
    let mut graph: Graph = HashMap::new();
    for line in input {
        if let Some((node, outputs)) = line.split_once(":") {
            let outputs: HashMap<String, bool> = outputs
                .trim()
                .split_whitespace()
                .map(|s| (s.to_string(), false))
                .collect();
            graph.insert(node.to_string(), outputs);
        }
    }
    graph
}

fn neighbours<'a>(graph: &'a Graph, name: &String) -> Option<&'a Nodes> {
    if graph.contains_key(name) {
        return graph.get(name);
    }
    None
}

fn paths_between(graph: &Graph, src: &String, dst: &String) -> i64 {
    let mut path_count = 0;
    let mut queue: VecDeque<String> = VecDeque::new();
    queue.push_back(src.clone());

    while !queue.is_empty() {
        let v = queue.pop_front().unwrap();

        if v == *dst {
            path_count += 1;
        }
        // Assume no cycles
        if let Some(neighbours) = neighbours(&graph, &v) {
            for (n, _) in neighbours {
                queue.push_back(n.clone());
            }
        }
    }

    path_count
}

fn step(
    graph: &Graph,
    cache: &mut HashMap<(String, bool, bool), i64>,
    curr: &String,
    mut visited_fft: bool,
    mut visited_dac: bool,
) -> i64 {
    if curr == "out" {
        if visited_fft && visited_dac {
            return 1;
        }
        return 0;
    }

    if curr == "fft" {
        visited_fft = true;
    }
    if curr == "dac" {
        visited_dac = true;
    }

    let cache_key = (curr.clone(), visited_fft, visited_dac);
    if cache.contains_key(&cache_key) {
        return *cache.get(&cache_key).unwrap();
    }

    let mut paths = 0;
    if let Some(neighbours) = neighbours(&graph, &curr) {
        for (n, _) in neighbours {
            paths += step(&graph, cache, &n, visited_fft, visited_dac);
        }
    }
    cache.insert(cache_key, paths);

    paths
}

fn solve_1(input: &Vec<String>) -> i64 {
    let graph = parse_graph(input);
    paths_between(&graph, &"you".to_string(), &"out".to_string())
}

fn solve_2(input: &Vec<String>) -> i64 {
    let graph = parse_graph(input);
    let mut cache: HashMap<(String, bool, bool), i64> = HashMap::new();
    step(&graph, &mut cache, &"svr".to_string(), false, false)
}

fn samples() {
    let lines = read_input_file("day11-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 5);

    let lines = read_input_file("day11-sample-1.input");
    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 2);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day11.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 652);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 362956369749210);
    };

    aoc_run(samples, solve_1_wrapper, solve_2_wrapper, lines)
}

#[cfg(test)]
mod tests {

    #[test]
    fn smoke() {
        assert!(true);
    }
}
