/**
 * Third attempt of Go :)
 */
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
)

const (
	rows = 6
	cols = 25
)

func parse(line string) [][rows][cols]int {
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

func multiply(layer [rows][cols]int) {
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
	fmt.Println("Results: ", digit_1_count*digit_2_count)
}

func solve1(layers [][rows][cols]int) {
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
	multiply(layers[min_layer])
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

func main() {
	// https://gosamples.dev/read-file/
	// file, err := os.Open("day08-sample.input")
	file, err := os.Open("day08.input")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	var part int
	flag.IntVar(&part, "part", 0, "part")
	flag.Parse()

	for scanner.Scan() {
		line := scanner.Text()
		layers := parse(line)

		if part == 0 || part == 1 {
			solve1(layers)
		}
		if part == 0 || part == 2 {
			solve2(layers)
		}
	}
}
