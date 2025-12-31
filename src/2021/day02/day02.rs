use aoc_runner::aoc_run;
use aoc_utils::*;

fn solve_1(input: &Vec<String>) -> i64 {
    let pos = input
        .iter()
        .map(|line| {
            let mut parts = line.split_whitespace();
            let word = parts.next().unwrap();
            let num = parts.next().unwrap().parse::<i64>().unwrap();
            (word, num)
        })
        .fold((0i64, 0i64), |acc, (w, n)| {
            match w.chars().next().unwrap() {
                'u' => (acc.0, acc.1 - n),
                'f' => (acc.0 + n, acc.1),
                'd' => (acc.0, acc.1 + n),
                _ => panic!("Invalid input"),
            }
        });
    pos.0 * pos.1
}

fn solve_2(input: &Vec<String>) -> i64 {
    let pos = input
        .iter()
        .map(|line| {
            let mut parts = line.split_whitespace();
            let word = parts.next().unwrap();
            let num = parts.next().unwrap().parse::<i64>().unwrap();
            (word, num)
        })
        .fold((0i64, 0i64, 0i64), |acc, (w, n)| {
            match w.chars().next().unwrap() {
                'u' => (acc.0, acc.1, acc.2 - n),
                'f' => (acc.0 + n, acc.1 + acc.2 * n, acc.2),
                'd' => (acc.0, acc.1, acc.2 + n),
                _ => panic!("Invalid input"),
            }
        });
    pos.0 * pos.1
}

fn samples() {
    let lines = read_input_file("day02-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert_eq!(sample_part_1, 150);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 900);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day02.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 1507611);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 1880593125);
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
