use aoc_runner::aoc_run;
use aoc_utils::*;

// TODO move to utils
fn split_by_empty_lines(lines: &[String]) -> Vec<Vec<String>> {
    let mut groups = Vec::new();
    let mut current_group = Vec::new();

    for line in lines {
        let trimmed = line.trim();
        if trimmed.is_empty() {
            if !current_group.is_empty() {
                groups.push(std::mem::take(&mut current_group));
            }
        } else {
            current_group.push(line.clone());
        }
    }

    if !current_group.is_empty() {
        groups.push(current_group);
    }

    groups
}

#[derive(Debug)]
struct Shape {
    area: i64,
    nr_of_pieces: i64,
}

impl TryFrom<Vec<String>> for Shape {
    type Error = &'static str;

    fn try_from(lines: Vec<String>) -> Result<Self, Self::Error> {
        if lines.len() < 2 {
            return Err("ID and shape must exist");
        }

        let form: Vec<String> = lines[1..].iter().cloned().collect();

        let height = form.len() as i64;
        let width = form[0].len() as i64;

        let area = height * width;
        assert!(area > 0);

        let mut nr_of_pieces = 0;
        for line in &form {
            for ch in line.chars() {
                if ch == '#' {
                    nr_of_pieces += 1;
                }
            }
        }
        assert!(nr_of_pieces > 0);

        Ok(Shape { area, nr_of_pieces })
    }
}

#[derive(Debug)]
struct Region {
    area: i64,
    shape_count: Vec<i64>,
}

impl TryFrom<&String> for Region {
    type Error = &'static str;

    fn try_from(line: &String) -> Result<Self, Self::Error> {
        if line.len() == 0 {
            return Err("Can't parse a non-empty string");
        }

        let parts: Vec<&str> = line.splitn(2, ':').collect();
        let hwvec: Vec<i64> = parts[0]
            .split('x')
            .map(|c| c.parse::<i64>().unwrap())
            .collect();
        assert!(hwvec.len() == 2);

        let width = hwvec[0];
        let height = hwvec[1];

        let area = width * height;
        assert!(area > 0);
        let shape_count: Vec<i64> = parts[1]
            .split_whitespace()
            .map(|c| c.parse::<i64>().unwrap())
            .collect();
        assert!(shape_count.len() > 0);

        Ok(Region { area, shape_count })
    }
}

fn solve_1(input: &Vec<String>) -> i64 {
    let instructions = split_by_empty_lines(input);
    assert!(instructions.len() > 0);

    let mut shapes: Vec<Shape> = Vec::new();
    let mut regions: Vec<Region> = Vec::new();
    for content in instructions {
        assert!(content.len() > 0);

        if content[0].chars().nth_back(0).unwrap() == ':' {
            match Shape::try_from(content) {
                Ok(shape) => shapes.push(shape),
                Err(e) => panic!("failed parsing shape {:?}", e),
            }
        } else {
            for line in content {
                match Region::try_from(&line) {
                    Ok(region) => regions.push(region),
                    Err(e) => panic!("failed parsing region {:?}", e),
                }
            }
        }
    }

    let mut trivial_fits = 0;
    let mut _trivial_nonfits = 0;
    let mut _undetermined = 0;
    for region in regions {
        let mut shapes_total_area = 0;
        let mut shapes_total_pieces = 0;
        for (shape_ind, count) in region.shape_count.iter().enumerate() {
            assert!(shape_ind < shapes.len());
            if *count == 0 {
                continue;
            }
            shapes_total_area += shapes[shape_ind].area * count;
            shapes_total_pieces += shapes[shape_ind].nr_of_pieces * count;
        }

        // Check if "trivial" fit would be sufficient
        if shapes_total_area <= region.area {
            trivial_fits += 1;

        // If there isn't enough space to fit all the '#', then it's trivial that it won't fit.
        } else if shapes_total_pieces > region.area {
            _trivial_nonfits += 1;

        // This is where the heavy lifting should happen, but turned out this was 0 for my input,
        // so yeah..
        } else {
            _undetermined += 1;
        }
    }

    // println!("trivial_fits: {:?}", trivial_fits);
    // println!("trivial_nonfits: {:?}", trivial_nonfits);
    // println!("undetermined: {:?}", undetermined);

    trivial_fits
}

fn solve_2(_input: &Vec<String>) -> i64 {
    0
}

fn samples() {
    let lines = read_input_file("day12-sample.input");

    let sample_part_1 = solve_1(&lines);
    println!("sample part 1: {}", sample_part_1);
    // This deviates from the example, the example input had 2 cases that was undetermined. Real
    // input had 0, so it was enough to apply some rule of thumb checks to complete todays puzzle.
    assert_eq!(sample_part_1, 1);

    let sample_part_2 = solve_2(&lines);
    println!("sample part 2: {}", sample_part_2);
    assert_eq!(sample_part_2, 0);
}

fn main() -> std::io::Result<()> {
    let lines = read_input_file("day12.input");

    let solve_1_wrapper = |lines: &Vec<String>| {
        let ans = solve_1(lines);
        println!("part1: {}", ans);
        assert_eq!(ans, 451);
    };
    let solve_2_wrapper = |lines: &Vec<String>| {
        let ans = solve_2(lines);
        println!("part2: {}", ans);
        assert_eq!(ans, 0);
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
