/**
 * Third attempt of Go :)
 */
package main

import (
	"aoc/aoc_runner"
	"aoc/aoc_utils"
	"fmt"
)

const (
	rows = 6
	cols = 25
)

func parse(lines []string) [][rows][cols]int {
	if len(lines) != 1 {
		panic("Should only be one line")
	}
	line := lines[0]
	size := len(line) / rows / cols
	layers := make([][rows][cols]int, size)
	for layer := range size {
		for row := range rows {
			for col := range cols {
				// Assumes all inputs are digits
				digit := int(line[rows*cols*layer+row*cols+col] - '0')
				layers[layer][row][col] = digit
			}
		}
	}
	return layers
}

func multiply(layer [rows][cols]int) int {
	digit_1_count := 0
	digit_2_count := 0
	for _, row := range layer {
		for _, col := range row {
			if col == 1 {
				digit_1_count += 1
			}
			if col == 2 {
				digit_2_count += 1
			}
		}
	}
	return digit_1_count * digit_2_count
}

func solve1(layers [][rows][cols]int) int {
	min_number_of_zeroes := rows * cols
	min_layer := 0
	for l, layer := range layers {
		number_of_zeroes := 0
		for _, row := range layer {
			for _, col := range row {
				// Assumes all inputs are digits
				if col == 0 {
					number_of_zeroes += 1
				}
			}
		}
		if number_of_zeroes < min_number_of_zeroes {
			min_number_of_zeroes = number_of_zeroes
			min_layer = l
		}
	}
	return multiply(layers[min_layer])
}

func solve2(layers [][rows][cols]int) {
	final_layer := [rows][cols]int{}
	for row := 0; row < rows; row++ {
		for col := 0; col < cols; col++ {
			final_layer[row][col] = 2
			for layer := 0; layer < len(layers); layer++ {
				if layers[layer][row][col] == 2 {
					continue
				}
				// Use the first encounter of colour
				final_layer[row][col] = layers[layer][row][col]
				break
			}
		}
	}

	for _, row := range final_layer {
		for _, col := range row {
			if col == 0 {
				fmt.Printf(" ")
			} else {
				fmt.Printf("%d", col)
			}
		}
		fmt.Printf("\n")
	}
}

func samples() {}

func solve_1(input []string) {
	layers := parse(input)
	res := solve1(layers)
	fmt.Println("Part 1:", res)
	// TODO Can I do my own assert that makes this a bit less verbose perhaps?
	if res != 2904 {
		panic("Wrong answer")
	}
}
func solve_2(input []string) {
	layers := parse(input)
	solve2(layers)
	fmt.Println("Part 2: See printout above")
}

func main() {
	input := aoc_utils.ReadInput("day08.input")
	aoc_runner.Run(samples, solve_1, solve_2, input)
}
