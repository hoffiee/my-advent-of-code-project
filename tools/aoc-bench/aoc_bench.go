/*
 * AOC benchmarking, it's a wrapper for running hyperfine on part1 1 and part1 2 individually
 */
package main

import (
	"fmt"
	"os"
	"os/exec"
)

func main() {

	if len(os.Args) < 2 {
		panic("Must provide a binary to the benchmark")
	}

	binary := os.Args[1]
	fmt.Println("Benchmarking: ", binary)
	fmt.Println("\tNote that you have to make sure that the binary is correct and works as expected!")

	part1 := "\"" + binary + " --part=1\""
	part2 := "\"" + binary + " --part=2\""

	// I only got this working when using bash -c and then sending in the
	// entire thing as a one liner, there's probably better ways to do this.
	benchCmd := exec.Command("bash", "-c", "hyperfine --warmup 3 "+part1+" "+part2)
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
}
