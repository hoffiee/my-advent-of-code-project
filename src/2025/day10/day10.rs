use regex::Regex;
use std::collections::VecDeque;

// TODO: Ensure sudo apt-get install coinor-cbc coinor-libcbc-dev is checked from Cmake for this
// target!
use good_lp::{Expression, Solution, SolverModel, constraint, default_solver, variable, variables};

use aoc_runner::aoc_run;
use aoc_utils::*;

fn parse_input(line: &String) -> (String, Vec<Vec<i64>>, String) {
    let re_light_state = Regex::new(r"\[(.*?)\]").unwrap();
    let re_buttons = Regex::new(r"\(([0-9,\s]+)\)").unwrap();
    let re_joltage = Regex::new(r"\{(.*?)\}").unwrap();

    let light_states = match re_light_state.captures(line) {
        Some(caps) => caps[1].to_string(),
        None => panic!("Failed to capture light state"),
    };
    assert!(light_states.len() > 0);

    let joltage_req = match re_joltage.captures(line) {
        Some(caps) => caps[1].to_string(),
        None => panic!("Failed to capture light state"),
    };
    assert!(joltage_req.len() > 0);

    let mut buttons = Vec::new();
    for cap in re_buttons.captures_iter(line) {
        let group_str = &cap[1];
        let numbers: Vec<i64> = group_str
            .split(",")
            .filter_map(|s| s.trim().parse().ok())
            .collect();
        buttons.push(numbers);
    }
    assert!(buttons.len() > 0);
    let buttons = buttons;

    (light_states, buttons, joltage_req)
}

// TODO: Change to representing the state as a integer instead and do XOR?
fn press(state: &mut Vec<bool>, button: &Vec<i64>) {
    for ind in button {
        state[*ind as usize] = !state[*ind as usize];
    }
}

fn solve_1(input: &Vec<String>) -> i64 {
    let mut sum = 0;

    for line in input {
        let (light_states, buttons, _) = parse_input(line);

        // BFS search, will find the first that reaches the correct state?
        // TODO Optimization, can I cache this somehow? currently 9!!! seconds.. As of writing this
        // it's the 3 longest runtime and takes 10% of the total runtime of all tasks since I've
        // done since 2015...
        // TODO: Optimization: Can I parallelize the outer loop to reduce runtime?
        let state: Vec<bool> = vec![false; light_states.len()];
        let state_target: Vec<bool> = light_states.chars().map(|c| matches!(c, '#')).collect();
        // seems that the state fits within an integer
        assert!(state_target.len() < 32);

        let mut queue: VecDeque<(Vec<bool>, Vec<i64>, i64)> = VecDeque::new();

        for button in &buttons {
            queue.push_back((state.clone(), button.clone(), 1));
        }

        while !queue.is_empty() {
            if let Some((mut curr_state, button_press, mut presses)) = queue.pop_front() {
                press(&mut curr_state, &button_press);
                if curr_state == state_target {
                    sum += presses;
                    break;
                }
                presses += 1;
                for button in &buttons {
                    queue.push_back((curr_state.clone(), button.clone(), presses));
                }
            }
        }
    }

    sum
}

fn solve_2(input: &Vec<String>) -> i64 {
    let mut sum = 0;

    for line in input {
        let (_, buttons, joltage_req) = parse_input(line);
        let state_target: Vec<i64> = joltage_req
            .split(',')
            .map(|s| s.trim().parse::<i64>().unwrap())
            .collect();

        let mut vars = variables!();
        let mut xvec = vec![];
        for _ in 0..buttons.len() {
            let xi = vars.add(variable().integer().min(0));
            xvec.push(xi);
        }

        // TODO: See if I can refactor it somehow
        // https://github.com/rust-or/good_lp/blob/main/tests/resource_allocation_problem.rs
        let mut constraints = vec![];
        let mut expr_vec: Vec<Expression> = vec![0.0.into(); state_target.len()];
        for (i, button) in buttons.iter().enumerate() {
            for light in button {
                expr_vec[*light as usize] += xvec[i];
            }
        }
        for (i, light_target) in state_target.iter().enumerate() {
            constraints.push(constraint!(expr_vec[i].clone() == *light_target as f64));
        }

        let mut cost: Expression = 0.0.into();
        for xi in &xvec {
            cost += xi;
        }

        let model = vars
            .minimise(cost)
            .using(default_solver)
            .with_all(constraints.iter().cloned());

        let solution = model.solve().unwrap();

        let mut clicks = 0;
        for i in 0..xvec.len() {
            clicks += solution.value(xvec[i]) as i64;
        }
        sum += clicks;
    }

    sum
}

fn samples() {
    // TODO Set assert that output from this file is non-empty
    let lines = read_input_file("day10-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 7);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 33);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day10.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 390);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 14677);
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
    fn solve_1_test_1() {
        let inp: Vec<String> = vec!["[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}".to_string()];
        let ans = solve_1(&inp);
        assert_eq!(ans, 2);
    }

    #[test]
    fn solve_1_test_2() {
        let inp: Vec<String> =
            vec!["[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}".to_string()];
        let ans = solve_1(&inp);
        assert_eq!(ans, 3);
    }

    #[test]
    fn solve_1_test_3() {
        let inp: Vec<String> =
            vec!["[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}".to_string()];
        let ans = solve_1(&inp);
        assert_eq!(ans, 2);
    }

    #[test]
    fn solve_2_test_1() {
        let inp: Vec<String> = vec!["[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}".to_string()];
        let ans = solve_2(&inp);
        assert_eq!(ans, 10);
    }

    #[test]
    fn solve_2_test_2() {
        let inp: Vec<String> =
            vec!["[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}".to_string()];
        let ans = solve_2(&inp);
        assert_eq!(ans, 12);
    }

    #[test]
    fn solve_2_test_3() {
        let inp: Vec<String> =
            vec!["[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}".to_string()];
        let ans = solve_2(&inp);
        assert_eq!(ans, 11);
    }
}
