/*
AOC benchmarking, it's a wrapper for running hyperfine on part1 1 and part1 2 individually

TODO: Fix handling of when entry already exists, prompt user for y/n to replace, or flag and rerun?
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

func runBenchmark(target string) string {
	part1 := "\"" + target + " --part=1\""
	part2 := "\"" + target + " --part=2\""

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
	return string(benchOut)
}

type benchmarkData struct {
	year       int
	day        int
	part_valid [2]bool
	mean       [2]float64
	variance   [2]float64
	times_min  [2]float64
	times_max  [2]float64
}

func newBenchmarkData(benchOut string) *benchmarkData {
	data := benchmarkData{}

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

	part := 0
	for _, line := range strings.Split(benchOut, "\n") {
		// alternatively i can use FindAllStringSubmatch
		match := benchmark_re.FindStringSubmatch(line)
		if len(match) == 4 {
			fmt.Println("Parsing", match)
			part, _ = strconv.Atoi(match[1])
			binary := filepath.Base(match[2])
			filename_pattern := `(\d+)_day(\d+)`
			filename_re := regexp.MustCompile(filename_pattern)
			match = filename_re.FindStringSubmatch(binary)
			data.year, _ = strconv.Atoi(match[1])
			data.day, _ = strconv.Atoi(match[2])
			data.part_valid[part-1] = true
			continue
		}

		match = time_re.FindStringSubmatch(line)
		if len(match) > 0 {
			fmt.Println("Parsing", match)
			match = float_re.FindAllString(match[0], -1)
			data.mean[part-1], _ = strconv.ParseFloat(match[0], 64)
			data.variance[part-1], _ = strconv.ParseFloat(match[1], 64)
			continue
		}

		match = range_re.FindStringSubmatch(line)
		if len(match) > 0 {
			fmt.Println("Parsing", match)
			match = float_re.FindAllString(match[0], -1)
			data.times_min[part-1], _ = strconv.ParseFloat(match[0], 64)
			data.times_max[part-1], _ = strconv.ParseFloat(match[1], 64)
			continue
		}
	}
	return &data
}

func validate_benchmark(benchmark *benchmarkData) bool {
	for i := range 2 {
		if !benchmark.part_valid[i] {
			continue
		}
		cond := &benchmark.part_valid[i]
		*cond = *cond && benchmark.mean[i] > 0
		*cond = *cond && benchmark.times_min[i] > 0
		*cond = *cond && benchmark.times_max[i] > 0
	}
	return benchmark.part_valid[0] || benchmark.part_valid[1]
}

func store_benchmark(db_path string, benchmark *benchmarkData) {
	db, err := sql.Open("sqlite3", db_path)
	if err != nil {
		log.Fatal("Failed to connect to database:", err)
	}
	defer db.Close()

	fmt.Println("Connected to database: ", db_path)
	stmt, err := db.Prepare("INSERT INTO entries(year, day, part, mean_ms, variance_ms, min_ms, max_ms) VALUES(?, ?, ?, ?, ?, ?, ?)")
	if err != nil {
		log.Fatalf("Failed to prepare statement: %v", err)
	}
	defer stmt.Close()

	for part_i := range 2 {
		if !benchmark.part_valid[part_i] {
			continue
		}

		fmt.Printf("writing: year:%d day:%d part:%d mean:%f\n", benchmark.year, benchmark.day, part_i+1, benchmark.mean[part_i])
		_, err = stmt.Exec(benchmark.year, benchmark.day, part_i+1, benchmark.mean[part_i],
			benchmark.variance[part_i],
			benchmark.times_min[part_i],
			benchmark.times_max[part_i])
		if err != nil {
			// If one part fails, I want it to continue and try to write the other one.
			log.Printf("Failed to execute insert: %v\n", err)
		}
	}
}

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

	benchOut := runBenchmark(*target)
	data := newBenchmarkData(benchOut)
	valid := validate_benchmark(data)
	if !valid {
		panic("Something went wrong for both part 1 and part 2")
	}

	store_benchmark(*db_path, data)
}
