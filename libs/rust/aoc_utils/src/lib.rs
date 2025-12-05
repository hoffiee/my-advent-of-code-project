use std::fs::File;
use std::io::{BufReader, BufRead};

pub fn read_input_file(path: &str) -> Vec<String> {
    let file = match File::open(path) {
        Ok(ok) => ok,
        Err(e) => panic!("IO error opening {}: {}", path, e),
    };
    let reader = BufReader::new(file);
    reader.lines()
        .map(|line| line.unwrap_or_else(|e| panic!("Read error in {}: {}", path, e)))
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn smoke() {
        assert!(true);
    }
}
