

use clap::Parser;


fn u8_range(s: &str) -> Result<u8, String> {
    let part: u8 = s.parse().map_err(|_| format!("'{}' isn't a valid part number", s))?;
    if part == 1 || part == 2 {
        Ok(part)
    } else {
        Err(format!("Part must be 1 or 2, got {}", part))
    }
}

#[derive(Parser, Debug)]
#[command(
    name = "YEAR_dayXX",
    about = "Usage: ./YEAR_dayXX [OPTIONS]\n\n Options",
    long_about = None,
)]
pub struct AocRunnerArgs {
    #[arg(short = 's', long = "sample")]
    pub sample: bool,

    #[arg(short = 'p', long = "part", value_parser = u8_range)]
    pub part: Option<u8>,
}

fn parse_args() -> AocRunnerArgs {
    AocRunnerArgs::parse()
}

pub fn aoc_run(solver_sample: impl FnOnce(),
    solver_1: impl FnOnce(&Vec<String>),
    solver_2: impl FnOnce(&Vec<String>),
    input: Vec<String>) -> std::io::Result<()> {

    let args = parse_args();

    let mut run_samples = args.sample;

    let (mut run_part_1, mut run_part_2) = match args.part {
        Some(1) => {
            (true, false)
        },
        Some(2) => {
            (false, true)
        },
        Some(0_u8) | Some(3_u8..=u8::MAX) => panic!("unreachable"),
        None => {
            (false, false)
        }
    };

    if !run_samples && !run_part_1 && !run_part_2 {
        run_samples = true;
        run_part_1 = true;
        run_part_2 = true;
    }

    if run_samples {
        solver_sample();
    }

    if run_part_1 {
        solver_1(&input);
    }

    if run_part_2 {
        solver_2(&input);
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn smoke() {
        assert!(true);
    }
}
