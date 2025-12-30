/*
*
Another Go attempt.

Keep track of array where each index is the number of Fishes, so we won't have
to deal with a growing list of Fishes
*/
package main

import (
	"aoc/aoc_runner"
	"aoc/aoc_utils"
	"fmt"
	"log"
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

func solve(initial_fishes []int, steps int) int {
	fishes := Fishes{}
	for _, val := range initial_fishes {
		fishes[val] += 1
	}
	for _ = range steps {
		fishes = fishes.step()
	}
	// fmt.Printf("%d fishes after %d days\n", fishes.sum(), steps)
	return fishes.sum()
}

func samples() {
	input := aoc_utils.ReadInput("day06-sample.input")
	fishes := parse(input[0])
	res := solve(fishes, 80)
	if res != 5934 {
		panic("invalid results")
	}

	res = solve(fishes, 256)
	if res != 26984457539 {
		panic("invalid results")
	}

}
func solve_1(input []string) {
	// TODO Check valid length!
	fishes := parse(input[0])
	res := solve(fishes, 80)
	fmt.Println("Part 1:", res)
	if res != 365131 {
		panic("invalid results")
	}
}

func solve_2(input []string) {
	// TODO Check valid length!
	fishes := parse(input[0])
	res := solve(fishes, 256)
	fmt.Println("Part 2:", res)
	if res != 1650309278600 {
		panic("invalid results")
	}
}

func main() {
	input := aoc_utils.ReadInput("day06.input")
	aoc_runner.Run(samples, solve_1, solve_2, input)
}
