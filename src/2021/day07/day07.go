/*
Another Go attempt

part 1: Find the median position
part 2: Find the average position
*/
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
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

func solve1(positions []int) {
	position := findMedian(positions)
	fmt.Println("position:", position)
	cost := 0
	for _, val := range positions {
		addition := AbsDiff(val, position)
		cost += addition
	}
	fmt.Println(cost)
}

func solve2(positions []int) {
	position := findAverage(positions)
	fmt.Println("position:", position)

	cost := 0
	for _, val := range positions {
		addition := AbsDiff(val, position)
		cost += addition * (addition + 1) / 2
	}
	fmt.Println(cost)
}

func main() {
	file, err := os.Open("day07.input")
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
			solve1(input)
		}
		if part == 0 || part == 2 {
			solve2(input)
		}
	}
}
