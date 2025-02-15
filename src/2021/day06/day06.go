/*
*
Another Go attempt.

Keep track of array where each index is the number of Fishes, so we won't have
to deal with a growing list of Fishes
*/
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func parse(input string) []int {
	size := len(input)
	out := make([]int, (size+1)/2)
	for i, digit := range strings.Split(input, ",") {
		value, err := strconv.Atoi(digit)
		if err != nil {
			log.Fatal(err)
		}
		out[i] = value
	}
	return out
}

type Fishes [9]int

// Not sure what creating methods like this is called, but trying it out
func (f *Fishes) step() Fishes {
	out := Fishes{}
	for i, val := range f {
		// internal timer -> 0, reset and add new fish
		if i == 0 {
			out[6] = val
			out[8] = val
			continue
		}
		out[i-1] += val
	}
	return out
}

func (f *Fishes) sum() int {
	out := 0
	for _, val := range f {
		out += val
	}
	return out
}

func solve(initial_fishes []int, steps int) {
	fishes := Fishes{}
	for _, val := range initial_fishes {
		fishes[val] += 1
	}
	for _ = range steps {
		fishes = fishes.step()
	}
	fmt.Printf("%d fishes after %d days\n", fishes.sum(), steps)
}

func main() {
	// file, err := os.Open("day06-sample.input")
	file, err := os.Open("day06.input")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	var part int
	flag.IntVar(&part, "part", 0, "part")
	flag.Parse()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		input := parse(line)
		if part == 0 || part == 1 {
			solve(input, 80)
		}
		if part == 0 || part == 2 {
			solve(input, 256)
		}
	}
}
