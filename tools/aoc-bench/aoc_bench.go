/*
* AOC benchmarking, it's a wrapper for running hyperfine on part1 1 and part1 2 individually

TODO: Error handling!, or we just validate after parsing and bail out
TODO: Fix handling of when entry already exists, prompt user for y/n to replace, or flag and rerun?
TODO: Refactor into something readable too.
TODO: extend db schema to include more info
*/
package main

import (
	"database/sql"
	"flag"
	"fmt"
	_ "github.com/mattn/go-sqlite3" // Import SQLite driver
	"log"
	"os/exec"
	"path/filepath"
	"regexp"
	"strconv"
	"strings"
)

func main() {
	db_path := flag.String("db", "./bench.db", "defines the path to a sqlite database")
	target := flag.String("target", "", "target to benchmark")
	// overwrite := flag.String("overwrite", "false", "TODO overwrite current entry")
	flag.Parse()
	if *target == "" {
		panic("No target provided")
	}

	fmt.Println("Benchmarking: ", *target)
	fmt.Println("\tNote that you have to make sure that the binary is correct and works as expected!")

	part1 := "\"" + *target + " --part=1\""
	part2 := "\"" + *target + " --part=2\""

	// I only got this working when using bash -c and then sending in the
	// entire thing as a one liner, there's probably better ways to do this.
	benchCmd := exec.Command("bash", "-c", "hyperfine -umillisecond --warmup 3 "+part1+" "+part2)
	benchOut, err := benchCmd.CombinedOutput()
	if err != nil {
		switch e := err.(type) {
		case *exec.Error:
			fmt.Println("failed executing:", err)
		case *exec.ExitError:
			fmt.Println("command exit rc =", e.ExitCode())
		default:
			panic(err)
		}
	}
	fmt.Println(string(benchOut))

	lines := strings.Split(string(benchOut), "\n")

	benchmark_pattern := `Benchmark (\d+): (.*) --part=(\d+)`
	benchmark_re := regexp.MustCompile(benchmark_pattern)

	float_pattern := `[-+]?\d*\.\d+|\d+`
	float_re := regexp.MustCompile(float_pattern)

	//   Time (mean ± σ):       0.9 ms ±   0.1 ms    [User: 0.4 ms, System: 0.7 ms]
	time_pattern := `Time \(mean.*`
	time_re := regexp.MustCompile(time_pattern)

	// Range (min … max):     0.7 ms …   1.3 ms    2250 runs
	range_pattern := `Range \(min.*`
	range_re := regexp.MustCompile(range_pattern)

	var year, day, part int = 0, 0, 0
	var mean [2]float64
	var variance [2]float64
	var times_min [2]float64
	var times_max [2]float64

	for _, line := range lines {
		// alternatively i can use FindAllStringSubmatch
		match := benchmark_re.FindStringSubmatch(line)
		if len(match) == 4 {
			part, _ = strconv.Atoi(match[1])
			binary := filepath.Base(match[2])
			filename_pattern := `(\d+)_day(\d+)`
			filename_re := regexp.MustCompile(filename_pattern)
			match = filename_re.FindStringSubmatch(binary)
			year, _ = strconv.Atoi(match[1])
			day, _ = strconv.Atoi(match[2])
			continue
		}

		match = time_re.FindStringSubmatch(line)
		if len(match) > 0 {
			match = float_re.FindAllString(match[0], -1)
			mean[part-1], _ = strconv.ParseFloat(match[0], 64)
			variance[part-1], _ = strconv.ParseFloat(match[1], 64)
			continue
		}

		match = range_re.FindStringSubmatch(line)
		if len(match) > 0 {
			match = float_re.FindAllString(match[0], -1)
			times_min[part-1], _ = strconv.ParseFloat(match[0], 64)
			times_max[part-1], _ = strconv.ParseFloat(match[1], 64)
			continue
		}
	}

	// Rethink this check, maybe create struct and have a validate method.
	if mean[0] == 0 || mean[1] == 0 || variance[0] == 0 || variance[1] == 0 || times_min[0] == 0 || times_min[1] == 0 || times_max[0] == 0 || times_max[1] == 0 {
		panic("Parsing isn't working as expected")
	}

	// Send to database
	db, err := sql.Open("sqlite3", *db_path)
	if err != nil {
		log.Fatal("Failed to connect to database:", err)
	}
	defer db.Close()

	fmt.Println("Connected to database: ", *db_path)
	stmt, err := db.Prepare("INSERT INTO entries(year, day, part, milliseconds) VALUES(?, ?, ?, ?)")
	if err != nil {
		log.Fatalf("Failed to prepare statement: %v", err)
	}
	defer stmt.Close()

	for part_i := range 2 {
		fmt.Printf("writing: year:%d day:%d part:%d mean:%f\n", year, day, part_i+1, mean[part_i])
		_, err = stmt.Exec(year, day, part_i+1, mean[part_i])
		if err != nil {
			log.Fatalf("Failed to execute insert: %v", err)
		}
	}
}
