/**
 * Second attempt, lets' see if this ends up a bit neater
 */
package main

import (
	"aoc/aoc_runner"
	"aoc/aoc_utils"
	"fmt"
	"log"
)

func solver(input []string) (int, int) {
	valid1 := 0
	valid2 := 0

	for _, line := range input {
		var a, b int
		var password string
		var letter rune
		_, err := fmt.Sscanf(line, "%d-%d %c: %s", &a, &b, &letter, &password)
		if err != nil {
			log.Fatal(err)
		}

		usage_of_char := 0
		for _, char := range password {
			if char == letter {
				usage_of_char += 1
			}
		}
		if (a <= usage_of_char) && (usage_of_char <= b) {
			valid1++
		}

		count := 0
		if password[a-1] == byte(letter) {
			count++
		}
		if password[b-1] == byte(letter) {
			count++
		}
		if count == 1 {
			valid2++
		}

	}

	return valid1, valid2
}

func samples() {
	input := aoc_utils.ReadInput("day02-sample.input")
	res1, res2 := solver(input)
	if res1 != 2 {
		panic("invalid results")
	}
	if res2 != 1 {
		panic("invalid results")
	}
}

// TODO: Setup as lambdas instead?
func solve_1(input []string) {
	res, _ := solver(input)
	fmt.Println("Part 1:", res)
	if res != 645 {
		panic("invalid results")
	}
}

func solve_2(input []string) {
	_, res := solver(input)
	fmt.Println("Part 2:", res)
	if res != 737 {
		panic("invalid results")
	}
}

func main() {
	input := aoc_utils.ReadInput("day02.input")
	aoc_runner.Run(samples, solve_1, solve_2, input)
}
