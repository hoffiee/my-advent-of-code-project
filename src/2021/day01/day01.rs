use aoc_runner::aoc_run;
use aoc_utils::*;

fn solve_1(input: &Vec<String>) -> i64 {
    input
        .iter()
        .map(|s| s.parse::<i64>().unwrap())
        .collect::<Vec<i64>>()
        .windows(2)
        .fold(0i64, |acc, w| acc + (w[0] < w[1]) as i64)
}

fn solve_2(input: &Vec<String>) -> i64 {
    input
        .iter()
        .map(|s| s.parse::<i64>().unwrap())
        .collect::<Vec<i64>>()
        .windows(4)
        .fold(0i64, |acc, w| acc + (w[0] < w[3]) as i64)
}

fn samples() {
    let lines = read_input_file("day01-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 7);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 5);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day01.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 1696);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 1737);
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
