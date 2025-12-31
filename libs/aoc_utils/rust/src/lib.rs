use std::fs::File;
use std::collections::HashMap;
use std::io::{BufRead, BufReader};

pub fn read_input_file(path: &str) -> Vec<String> {
    let file = match File::open(path) {
        Ok(ok) => ok,
        Err(e) => panic!("IO error opening {}: {}", path, e),
    };
    let reader = BufReader::new(file);
    let out: Vec<String> = reader
        .lines()
        .map(|line| line.unwrap_or_else(|e| panic!("Read error in {}: {}", path, e)))
        .collect();

    assert!(out.len() > 0, "No content in the file");
    out
}

pub fn split_by_empty_lines(lines: &[String]) -> Vec<Vec<String>> {
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

#[derive(Debug, Clone, PartialEq, Eq, Hash, Copy)]
pub struct Point2d {
    pub x: i64,
    pub y: i64,
}

pub fn extract_points_from_map<T: Default>(input: &Vec<String>, symbols: &Vec<char>) -> HashMap<char, HashMap<Point2d, T>> {
    let mut out = HashMap::new();
    for y in 0..input.len() {
        for x in 0..input[0].len() {
            for symbol in symbols {
                if input[y].chars().nth(x as usize).unwrap() == *symbol {
                    out.entry(*symbol).or_insert_with(HashMap::new).entry(Point2d{x: x as i64, y: y as i64}).or_default();
                }
            }
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn smoke() {
        assert!(true);
    }

    #[test]
    fn test_extract_points_from_map() {
        let inp = vec![
            "...S...".to_string(),
            "...^...".to_string(),
            ".^...^.".to_string(),
            ".......".to_string(),
        ];

        let res = extract_points_from_map::<bool>(&inp, &vec!['S', '^']);
        println!("{:?}", res);
        assert_eq!(res.len(), 2);
        assert!(res.contains_key(&'S'));
        assert!(res.contains_key(&'^'));

        assert_eq!(res.get(&'S').unwrap().len(), 1);
        assert_eq!(res.get(&'^').unwrap().len(), 3);

        assert!(res.get(&'S').unwrap().contains_key(&Point2d{x:3, y:0}));
        assert!(res.get(&'^').unwrap().contains_key(&Point2d{x:3, y:1}));
        assert!(res.get(&'^').unwrap().contains_key(&Point2d{x:1, y:2}));
        assert!(res.get(&'^').unwrap().contains_key(&Point2d{x:5, y:2}));
        assert_eq!(res.get(&'.'), None);
    }


}
