/**
* TODO refactor
*/
use std::fs::File;
use std::io::{BufReader, BufRead};

fn read_input_file(path: &str) -> std::io::Result<Vec<String>> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);
    reader.lines().collect()
}

fn valid_point(point: (i64, i64), dim: (i64, i64)) -> bool {
    let (rz, cz) = dim;
    let (r, c) = point;
    if r < 0 || rz <= r {
        return false
    }
    if c < 0 || cz <= c {
        return false
    }
    true
}

fn accessible(input: &Vec<Vec<char>>, dim: (i64, i64), point: (i64, i64)) -> bool {
    let (r, c) = point;

    let mut count = 0;
    for rc in -1..2 {
        for cc in -1..2 {
            if rc == 0 && cc == 0 {
                continue;
            }

            let rcand: i64 = r+rc;
            let ccand: i64 = c+cc;

            if !valid_point((rcand, ccand), dim) {
                continue;
            }

            if input[rcand as usize][ccand as usize] != '.' {
                count += 1;
            }
        }
    }

    count < 4
}

#[allow(dead_code)]
fn print_grid(grid: &Vec<Vec<char>>) {
    for line in grid {
        for ch in line {
            print!("{}", ch);
        }
        println!("");
    }
    println!("");
}

fn remove_rolls(grid: &mut Vec<Vec<char>>) {
    let rz = grid.len();
    let cz = grid[0].len();
    for r in 0..rz {
        for c in 0..cz {
            if grid[r][c] == 'x' {

                grid[r][c] = '.';
            }
        }
    }
}

fn solve_1(input: &Vec<String>) -> i64 {
    let rz = input.len();
    let cz = input[0].len();
    let dim = (rz as i64, cz as i64);

    let mut grid: Vec<Vec<char>> = vec![vec!['.'; rz]; cz];
    for r in 0..rz {
        for c in 0..cz {
            grid[r][c] = input[r].chars().nth(c).unwrap();
        }
    }

    let mut sum = 0;
    for r in 0..rz {
        for c in 0..cz {
            if grid[r][c] == '.' {
                continue;
            }
            if accessible(&grid, dim, (r as i64, c as i64)) {
                sum += 1
            }
        }
    }

    sum
}

fn solve_2(input: &Vec<String>) -> i64 {
    let rz = input.len();
    let cz = input[0].len();
    let dim = (rz as i64, cz as i64);

    let mut grid: Vec<Vec<char>> = vec![vec!['.'; rz]; cz];
    for r in 0..rz {
        for c in 0..cz {
            grid[r][c] = input[r].chars().nth(c).unwrap();
        }
    }

    let mut sum = 0;
    loop {
        let mut removed = 0;
        for r in 0..rz {
            for c in 0..cz {
                if grid[r][c] == '.' {
                    continue;
                }
                if accessible(&grid, dim, (r as i64, c as i64)) {
                    removed += 1;
                    grid[r][c] = 'x';
                }
            }
        }

        remove_rolls(&mut grid);
        // print_grid(&grid);
        sum += removed;

        if removed == 0 {
            break;
        }

    }

    sum
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day04-sample.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    assert!(sample_part_1 == 13);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert!(sample_part_2 == 43);

    let lines = read_input_file("day04.input")?;
    // lines.iter().for_each(|x| println!("{}", x));

    let part_1 = solve_1(&lines);
    println!("part 1: {}", part_1);
    assert!(part_1 == 1495);

    let part_2 = solve_2(&lines);
    println!("part 2: {}", part_2);
    assert!(part_2 == 8768);

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
    fn solve_1_test_1() {
        let lines  = vec![
            "@.@".to_string(),
            ".@.".to_string(),
            "@.@".to_string(),
        ];
        let res = solve_1(&lines);
        assert_eq!(res, 4);
    }
}
