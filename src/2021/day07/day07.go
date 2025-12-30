/*
Another Go attempt

part 1: Find the median position
part 2: Find the average position
*/
package main

import (
	"aoc/aoc_runner"
	"aoc/aoc_utils"
	"fmt"
	"log"
	"sort"
	"strconv"
	"strings"
)

func parse(input string) []int {
	entries := strings.Split(input, ",")
	out := make([]int, len(entries))
	for i, digit := range entries {
		value, err := strconv.Atoi(digit)
		if err != nil {
			log.Fatal(err)
		}
		out[i] = value
	}
	return out
}

func findMedian(positions []int) int {
	sort.Ints(positions)

	length := len(positions)
	if length == 0 {
		return 0
	}

	if length%2 != 0 {
		return positions[length/2]
	}
	return (positions[(length/2)-1] + positions[length/2]) / 2
}

func findAverage(positions []int) int {
	length := len(positions)
	out := 0
	for _, val := range positions {
		out += val
	}
	// Get the wrong one without the subtraction of 1e-10
	return int(float64(out)/float64(length) + 0.5 - 1e-10)
}

func AbsDiff(x, y int) int {
	if x < y {
		return y - x
	}
	return x - y
}

func solve1(positions []int) int {
	position := findMedian(positions)
	cost := 0
	for _, val := range positions {
		addition := AbsDiff(val, position)
		cost += addition
	}
	return cost
}

func solve2(positions []int) int {
	position := findAverage(positions)

	cost := 0
	for _, val := range positions {
		addition := AbsDiff(val, position)
		cost += addition * (addition + 1) / 2
	}
	return cost
}

func samples() {
	input := aoc_utils.ReadInput("day07-sample.input")
	positions := parse(input[0])
	res := solve1(positions)
	if res != 37 {
		panic("wrong answer")
	}

	res = solve2(positions)
	if res != 168 {
		panic("wrong answer")
	}

}
func solve_1(input []string) {
	positions := parse(input[0])
	res := solve1(positions)
	fmt.Println("Part 1:", res)
	if res != 326132 {
		panic("wrong answer")
	}
}
func solve_2(input []string) {
	positions := parse(input[0])
	res := solve2(positions)
	fmt.Println("Part 2:", res)
	if res != 88612508 {
		panic("wrong answer")
	}
}

func main() {
	input := aoc_utils.ReadInput("day07.input")
	aoc_runner.Run(samples, solve_1, solve_2, input)
}
