/**
 * Don't know my way around Go but here's one of my first attempts in Go.
 */
package main

import (
	"aoc/aoc_runner"
	"aoc/aoc_utils"
	"fmt"
	"strconv"
)

func solve1(entries []int) int {
	if entries == nil {
		panic("input nil")
	}

	for i := 0; i < len(entries); i++ {
		for j := i; j < len(entries); j++ {
			if i == j {
				continue
			}
			if entries[i]+entries[j] == 2020 {
				return entries[i] * entries[j]
			}
		}
	}
	return 0
}

func solve2(entries []int) int {
	if entries == nil {
		panic("input nil")
	}

	// Another approach is to just return like this.
	for i := 0; i < len(entries); i++ {
		for j := i; j < len(entries); j++ {
			for k := j; k < len(entries); k++ {
				if i == j || i == k || j == k {
					continue
				}
				if entries[i]+entries[j]+entries[k] == 2020 {
					return entries[i] * entries[j] * entries[k]
				}
			}
		}
	}
	return 0
}

func parse(input []string) []int {
	entries := make([]int, len(input))
	for i := 0; i < len(input); i++ {
		val, err := strconv.Atoi(input[i])
		if err != nil {
			continue
		}
		entries[i] = val
	}
	return entries
}

func samples() {
	input := aoc_utils.ReadInput("day01-sample.input")
	entries := parse(input)
	res := solve1(entries)
	if res != 514579 {
		panic("invalid results")
	}

	res = solve2(entries)
	if res != 241861950 {
		panic("invalid results")
	}
}

func solve_1(input []string) {
	entries := parse(input)
	res := solve1(entries)
	fmt.Println("Part 1:", res)
	if res != 1009899 {
		panic("invalid results")
	}
}

func solve_2(input []string) {
	entries := parse(input)
	res := solve2(entries)
	fmt.Println("Part 2:", res)
	if res != 44211152 {
		panic("invalid results")
	}
}

func main() {
	input := aoc_utils.ReadInput("day01.input")
	aoc_runner.Run(samples, solve_1, solve_2, input)
}
