use aoc_runner::aoc_run;
use aoc_utils::*;

fn transpose_strings(slice: &[String]) -> Vec<String> {
    if slice.is_empty() {
        return vec![];
    }
    let rows: Vec<Vec<char>> = slice.iter().map(|s| s.chars().collect()).collect();
    let cols: Vec<Vec<char>> = transpose(&rows);
    cols.into_iter()
        .map(|col| col.into_iter().collect())
        .collect()
}

fn transpose<T: Clone>(rows: &[Vec<T>]) -> Vec<Vec<T>> {
    if rows.is_empty() {
        return vec![];
    }
    let col_count = rows[0].len();
    (0..col_count)
        .map(|i| rows.iter().map(|row| row[i].clone()).collect())
        .collect()
}

fn solve_1(input: &Vec<String>) -> i64 {
    let num_numbers = input.len() - 1;

    let numbers = input[0..num_numbers]
        .iter()
        .flat_map(|s| {
            s.split_whitespace()
                .filter_map(|part| part.parse::<i64>().ok())
        })
        .collect::<Vec<i64>>();

    let num_cases = numbers.len() / num_numbers;

    let oper = input
        .last()
        .unwrap()
        .chars()
        .filter(|c| !c.is_whitespace())
        .collect::<Vec<char>>();
    assert_eq!(oper.len(), num_cases);

    let mut sum = 0;
    for i in 0..num_cases {
        let mut acc = numbers[i];
        for offset in 1..num_numbers {
            match oper[i] {
                '+' => acc += numbers[i + num_cases * offset],
                '*' => acc *= numbers[i + num_cases * offset],
                _ => panic!("Should only be +*"),
            }
        }
        sum += acc;
    }
    sum
}

fn solve_2(input: &Vec<String>) -> i64 {
    let mut numbers = transpose_strings(&input[0..input.len() - 1]);
    numbers.push(" ".to_string());
    let numbers = numbers;

    let oper = input
        .last()
        .unwrap()
        .chars()
        .filter(|c| !c.is_whitespace())
        .collect::<Vec<char>>();

    let mut sum = 0;
    let mut oper_i = 0;
    let mut acc = match oper[oper_i] {
        '+' => 0,
        '*' => 1,
        _ => panic!(),
    };
    for line in numbers {
        if line.trim().is_empty() {
            oper_i += 1;
            sum += acc;

            if oper_i >= oper.len() {
                continue;
            }

            acc = match oper[oper_i] {
                '+' => 0,
                '*' => 1,
                _ => panic!(),
            };
            continue;
        }

        match oper[oper_i] {
            '+' => acc += line.trim().parse::<i64>().unwrap(),
            '*' => acc *= line.trim().parse::<i64>().unwrap(),
            _ => panic!(),
        };
    }

    sum
}

fn samples() {
    let lines = read_input_file("day06-sample.input");
    // lines.iter().for_each(|x| println!("{}", x));

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert!(sample_part_1 == 4277556);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert!(sample_part_2 == 3263827);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day06.input");
    // lines.iter().for_each(|x| println!("{}", x));

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 5316572080628);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        assert_eq!(ans, 11299263623062);
        println!("part2: {}", ans);
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
