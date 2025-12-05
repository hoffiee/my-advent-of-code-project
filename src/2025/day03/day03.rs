use aoc_runner::aoc_run;
use aoc_utils::*;

fn find_max(battery_slice: &str) -> (i64, usize) {
    battery_slice
        .bytes()
        .enumerate()
        .fold((0i64, 1usize), |(max, idx), (i, b)| {
            let digit = (b - b'0') as i64;
            if digit > max {
                (digit, i + 1)
            } else {
                (max, idx)
            }
        })
}

fn solver(line: &str, battery_size: usize) -> i64 {
    let mut acc: i64 = 0;
    let mut start: usize = 0;
    for offset in 0..battery_size {
        let (val, next_distance) = find_max(&line[start..line.len() - (battery_size - offset - 1)]);
        start += next_distance;
        acc = 10 * acc + val;
    }
    acc
}

fn solve_1(input: &Vec<String>) -> i64 {
    input.iter().map(|s| solver(s, 2)).sum()
}

fn solve_2(input: &Vec<String>) -> i64 {
    input.iter().map(|s| solver(s, 12)).sum()
}

fn samples() {
    let lines = read_input_file("day03-sample.input");
    // lines.iter().for_each(|x| println!("{}", x));

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert!(sample_part_1 == 357);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert!(sample_part_2 == 3121910778619);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day03.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 17613);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        assert_eq!(ans, 175304218462560);
        println!("part2: {}", ans);
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
        let lines = vec!["987654321111111".to_string()];
        let res = solve_1(&lines);
        assert_eq!(res, 98);
    }

    #[test]
    fn solve_1_test_2() {
        let lines = vec!["811111111111119".to_string()];
        let res = solve_1(&lines);
        assert_eq!(res, 89);
    }

    #[test]
    fn solve_1_test_3() {
        let lines = vec!["234234234234278".to_string()];
        let res = solve_1(&lines);
        assert_eq!(res, 78);
    }

    #[test]
    fn solve_1_test_4() {
        let lines = vec!["818181911112111".to_string()];
        let res = solve_1(&lines);
        assert_eq!(res, 92);
    }

    #[test]
    fn solve_2_test_1() {
        let lines = vec!["987654321111111".to_string()];
        let res = solve_2(&lines);
        assert_eq!(res, 987654321111);
    }

    #[test]
    fn solve_2_test_2() {
        let lines = vec!["811111111111119".to_string()];
        let res = solve_2(&lines);
        assert_eq!(res, 811111111119);
    }

    #[test]
    fn solve_2_test_3() {
        let lines = vec!["234234234234278".to_string()];
        let res = solve_2(&lines);
        assert_eq!(res, 434234234278);
    }

    #[test]
    fn solve_2_test_4() {
        let lines = vec!["818181911112111".to_string()];
        let res = solve_2(&lines);
        assert_eq!(res, 888911112111);
    }
}
