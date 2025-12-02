use std::fs::File;
use std::io::{BufReader, BufRead};

fn read_input_file(path: &str) -> std::io::Result<Vec<String>> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);
    reader.lines().collect()
}


fn invalid_id(id: i64) -> bool {
    let id = id.to_string();
    if id.len() == 1 || id.len() % 2 != 0 {
        return false
    }

    let mid: usize = id.chars().count() / 2;
    let (left, right) = id.split_at(mid);

    left == right
}

fn repeated_sequence(rem: &str, cand: &str) -> bool {
    if rem.len() < cand.len() {
        return false
    }

    if rem.len() == cand.len() {
        return rem == cand
    }

    let size = cand.len();
    for chunk in rem.as_bytes().chunks(size) {

        let slice = std::str::from_utf8(chunk).expect("invalid utf-8");

        if slice != cand {
            let reduced_rem = &rem[0..1];
            let combined = format!("{}{}", cand, reduced_rem);
            return repeated_sequence(&rem[1..], &combined);
        }
    }

    true
}

fn invalid_id2(id: i64) -> bool {
    let id = id.to_string();
    if id.len() == 1 {
        return false
    }

    repeated_sequence(&id[1..], &id[0..1])
}


fn solve_1(input: &Vec<String>) -> i64 {
    let mut sum: i64 = 0;

    for line in input[0].split(",") {

        let (first_id, last_id) = line.split_once("-").unwrap();

        assert!(first_id.chars().next().unwrap() != '0');
        assert!(last_id.chars().next().unwrap() != '0');

        let first_id = first_id.parse::<i64>().expect("Failed to parse first id");
        let last_id = last_id.parse::<i64>().expect("Failed to parse last id");

        for id in first_id..=last_id {

            if invalid_id(id) {
                sum += id;
            }
        }
    }

    sum
}

fn solve_2(input: &Vec<String>) -> i64 {
    let mut sum: i64 = 0;

    for line in input[0].split(",") {

        let (first_id, last_id) = line.split_once("-").unwrap();

        assert!(first_id.chars().next().unwrap() != '0');
        assert!(last_id.chars().next().unwrap() != '0');

        let first_id = first_id.parse::<i64>().expect("Failed to parse first id");
        let last_id = last_id.parse::<i64>().expect("Failed to parse last id");

        for id in first_id..=last_id {
            if invalid_id2(id) {
                sum += id;
            }
        }
    }

    sum
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day02-sample.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert!(sample_part_1 == 1227775554);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert!(sample_part_2 == 4174379265);

    let lines = read_input_file("day02.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let part_1 = solve_1(&lines);
    println!("part 1: {}", part_1);
    assert!(part_1 == 24043483400);

    let part_2 = solve_2(&lines);
    println!("part 2: {}", part_2);
    assert!(part_2 == 38262920235);

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
    fn test_invalid_id() {
        assert!(invalid_id(11));
        assert!(invalid_id(22));
        assert!(invalid_id(1010));
        assert!(invalid_id(1188511885));
        assert!(invalid_id(55));
        assert!(invalid_id(6464));
        assert!(invalid_id(123123));
    }

    #[test]
    fn test_valid_id() {
        assert!(!invalid_id(12));
        assert!(!invalid_id(101));
        assert!(!invalid_id(111));
        assert!(!invalid_id(13));
        assert!(!invalid_id(123));
    }

    #[test]
    fn test_invalid_id2() {
        assert!(invalid_id2(11));
        assert!(invalid_id2(22));
        assert!(invalid_id2(99));
        assert!(invalid_id2(111));
        assert!(invalid_id2(1111111));
        assert!(invalid_id2(1188511885));
        assert!(invalid_id2(12341234));
        assert!(invalid_id2(123123123));
        assert!(invalid_id2(1212121212));
    }

    #[test]
    fn test_valid_id2() {
        assert!(!invalid_id2(12));
        assert!(!invalid_id2(101));
        assert!(!invalid_id2(13));
        assert!(!invalid_id2(123));
        assert!(!invalid_id2(824824821));
    }

    #[test]
    fn solve_1_test_1() {
        let lines  = vec![
            "11-22".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 11+22);
    }

    #[test]
    fn solve_1_test_2() {
        let lines  = vec![
            "95-115".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 99);
    }

    #[test]
    fn solve_1_test_3() {
        let lines  = vec![
            "1188511880-1188511890".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 1188511885);
    }

    #[test]
    fn solve_1_test_4() {
        let lines  = vec![
            "222220-222224".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 222222);
    }

    #[test]
    fn solve_1_test_5() {
        let lines  = vec![
            "1698522-1698528".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 0);
    }

    #[test]
    fn solve_1_test_6() {
        let lines  = vec![
            "446443-446449".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 446446);
    }

    #[test]
    fn solve_1_test_7() {
        let lines  = vec![
            "38593856-38593862".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 38593859);
    }

    #[test]
    fn solve_1_test_8() {
        let lines  = vec![
            "565653-565659,824824821-824824827,2121212118-2121212124".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 0);
    }

    #[test]
    #[should_panic]
    fn solve_1_test_9() {
        let lines  = vec![
            "01-10".to_string()
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 0);
    }


    #[test]
    fn solve_2_test_1() {
        let lines  = vec![
            "11-22".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 11+22);
    }

    #[test]
    fn solve_2_test_2() {
        let lines  = vec![
            "95-115".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 99+111);
    }

    #[test]
    fn solve_2_test_3() {
        let lines  = vec![
            "998-1012".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 999+1010);
    }

    #[test]
    fn solve_2_test_4() {
        let lines  = vec![
            "1188511880-1188511890".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 1188511885);
    }

    #[test]
    fn solve_2_test_5() {
        let lines  = vec![
            "222220-222224".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 222222);
    }

    #[test]
    fn solve_2_test_6() {
        let lines  = vec![
            "1698522-1698528".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 0);
    }

    #[test]
    fn solve_2_test_7() {
        let lines  = vec![
            "446443-446449".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 446446);
    }

    #[test]
    fn solve_2_test_8() {
        let lines  = vec![
            "38593856-38593862".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 38593859);
    }

    #[test]
    fn solve_2_test_9() {
        let lines  = vec![
            "565653-565659".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 565656);
    }

    #[test]
    fn solve_2_test_10() {
        let lines  = vec![
            "824824821-824824827".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 824824824);
    }

    #[test]
    fn solve_2_test_11() {
        let lines  = vec![
            "2121212118-2121212124".to_string()
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 2121212121);
    }

}
