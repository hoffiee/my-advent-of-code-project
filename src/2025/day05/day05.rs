use std::ops::RangeInclusive;

use aoc_utils::*;

fn split_on_empty(input: &Vec<String>) -> Vec<Vec<String>> {
    input.into_iter().fold(Vec::new(), |mut acc, s| {
        if s.is_empty() {
            acc.push(Vec::new());
        } else if let Some(last) = acc.last_mut() {
            last.push(s.clone());
        } else {
            acc.push(vec![s.clone()]);
        }
        acc
    }).into_iter().filter(|group| !group.is_empty()).collect()
}

fn parse_range(s: &str) -> RangeInclusive<i64> {
    let parts: Vec<i64> = s.split('-')
        .map(|p| p.parse::<i64>().unwrap())
        .collect();
    assert_eq!(parts.len(), 2, "Must result in 2 parts");
    parts[0]..=parts[1]
}

fn range_len(range: &RangeInclusive<i64>) -> i64 {
    if range.is_empty() {
        return 0
    }
    *range.end() - *range.start() + 1
}

fn solve_1(input: &Vec<String>) -> i64 {
    let split = split_on_empty(input);
    assert_eq!(split.len(), 2);

    let valid_ids: Vec<RangeInclusive<i64>> = split[0].iter().map(|s| parse_range(&s)).collect();

    split[1].iter()
        .map(|s| {
            let id = s.parse::<i64>().unwrap();
            for range in &valid_ids {
                if range.contains(&id) {
                    return 1
                }
            }
            0
        }).sum()
}

fn solve_2(input: &Vec<String>) -> i64 {
    let split = split_on_empty(input);
    assert_eq!(split.len(), 2);

    let mut valid_ids: Vec<RangeInclusive<i64>> = split[0].iter().map(|s| parse_range(&s)).collect();
    valid_ids.sort_unstable_by_key(|r| *r.start());

    let mut merged_ranges: Vec<RangeInclusive<i64>> = Vec::new();

    for cand_range in valid_ids {

        if merged_ranges.is_empty() {
            merged_ranges.push(cand_range);
            continue;
        }

        let cand_first = *cand_range.start();
        let mut modified = false;
        let range = merged_ranges.last_mut().unwrap();
        if range.contains(&cand_first) {
            let first = *range.start();
            let cand_last = *cand_range.end();
            let new_last = cand_last.max(*range.end());
            *range = first..=new_last;

            modified = true;
        }

        if !modified {
            merged_ranges.push(cand_range);
        }
    }

    merged_ranges.iter().fold(0, |acc, range| acc + range_len(&range))
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day05-sample.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert!(sample_part_1 == 3);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert!(sample_part_2 == 14);

    let lines = read_input_file("day05.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let part_1 = solve_1(&lines);
    println!("part 1: {}", part_1);
    assert!(part_1 == 735);

    let part_2 = solve_2(&lines);
    println!("part 2: {}", part_2);
    assert!(part_2 == 344306344403172);

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
    fn solve_2_test_1() {
        let lines  = vec![
            "1-5".to_string(),
            "6-10".to_string(),
            "".to_string(),
            "1".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 10);
    }

    #[test]
    fn solve_2_test_2() {
        let lines  = vec![
            "1-5".to_string(),
            "3-7".to_string(),
            "".to_string(),
            "1".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 7);
    }

    #[test]
    fn solve_2_test_3() {
        let lines  = vec![
            "1-4".to_string(),
            "6-10".to_string(),
            "3-7".to_string(),
            "".to_string(),
            "1".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 10);
    }
    #[test]
    fn solve_2_test_4() {
        let lines  = vec![
            "1-10".to_string(),
            "1-8".to_string(),
            "".to_string(),
            "1".to_string(),
        ];
        let res = solve_2(&lines);
        assert_eq!(res, 10);
    }
}
