use std::fs::File;
use std::io::{BufReader, BufRead};

fn read_input_file(path: &str) -> std::io::Result<Vec<String>> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);
    reader.lines().collect()
}

fn get_number_from_string(s: &str) -> Option<i64> {
    let digits: String = s.chars().filter(|c| c.is_ascii_digit()).collect();
    if digits.is_empty() {
        None
    }
    else {
        digits.parse::<i64>().ok()
    }
}

fn wrap(n: i64) -> i64 {
    let modulus = 100;
    ((n % modulus) + modulus) % modulus
}

fn solve_1(input: &Vec<String>) -> i64 {
    let mut dial = 50;
    let mut count = 0;

    for line in input {
        let dir = line.chars().next().unwrap();
        let num = get_number_from_string(line).unwrap();

        match dir {
            'L' => dial = wrap(dial - num),
            'R' => dial = wrap(dial + num),
            _ => panic!(),
        }

        if dial == 0 {
            count += 1
        }
    }

    count
}

fn solve_2(input: &Vec<String>) -> i64 {
    let mut dial = 50;
    let mut count = 0;

    for line in input {
        let dir = line.chars().next().unwrap();
        let num = get_number_from_string(line).unwrap();

        let rotations = num / 100 as i64;
        count += rotations;

        let wrapped_num = wrap(num);
        let new_dial = match dir {
            'L' => dial - wrapped_num,
            'R' => dial + wrapped_num,
            _ => panic!(),
        };

        // Avoid counting the 0 if we already stand on it, it's accounted for in the previous
        // instruction
        if dial != 0 && (new_dial <= 0 || 99 < new_dial) {
            count += 1;
        }

        dial = wrap(new_dial);
    }

    count
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day01-sample.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert!(sample_part_1 == 3);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert!(sample_part_2 == 6);

    let lines = read_input_file("day01.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let part_1 = solve_1(&lines);
    println!("part 1: {}", part_1);
    assert!(part_1 == 1105);

    let part_2 = solve_2(&lines);
    println!("part 2: {}", part_2);
    assert!(part_2 == 6599);

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn smoke() {
        assert!(true);
    }

    #[test]
    fn test_wrap() {
        let out = wrap(0 - 1);
        assert_eq!(out, 99);

        let out = wrap(99 + 1);
        assert_eq!(out, 0);

        let out = wrap(0 - 5);
        assert_eq!(out, 95);

        let out = wrap(14 - 82);
        assert_eq!(out, 32);
    }

    #[test]
    fn solve_2_test_1() {
        let lines  = vec![
            "L50".to_string(),
            "L10".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1);
    }

    #[test]
    fn solve_2_test_2() {
        let lines  = vec![
            "R50".to_string(),
            "R99".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1);
    }

    #[test]
    fn solve_2_test_3() {
        let lines  = vec![
            "R40".to_string(),
            "R40".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1);
    }

    #[test]
    fn solve_2_test_4() {
        let lines  = vec![
            "L40".to_string(),
            "L40".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1);
    }

    #[test]
    fn solve_2_test_5() {
        let lines  = vec![
            "L50".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1);
    }

    #[test]
    fn solve_2_test_6() {
        let lines  = vec![
            "R50".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1);
    }

    #[test]
    fn solve_2_test_7() {
        let lines  = vec![
            "L250".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 3)
    }

    #[test]
    fn solve_2_test_8() {
        let lines  = vec![
            "R250".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 3)
    }

    #[test]
    fn solve_2_test_9() {
        let lines  = vec![
            "L50".to_string(),
            "L200".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 3)
    }

    #[test]
    fn solve_2_test_10() {
        let lines  = vec![
            "R50".to_string(),
            "R200".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 3)
    }

    #[test]
    fn solve_2_test_11() {
        let lines  = vec![
            "R200".to_string(),
            "R50".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 3)
    }

    #[test]
    fn solve_2_test_12() {
        let lines  = vec![
            "R200".to_string(),
            "L50".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 3)
    }

    #[test]
    fn solve_2_test_13() {
        let lines  = vec![
            "L150".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 2)
    }

    #[test]
    fn solve_2_test_14() {
        let lines  = vec![
            "R150".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 2)
    }
}
