/**
 * Don't know my way around Go but here's one of my first attempts in Go.
 */
package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func solve1(entries []int) {
	if entries == nil {
		panic("input nil")
	}

	// one alternative to break nested loops is by setting a label and break
	fmt.Println("Part one")
searching1:
	for i := 0; i < len(entries); i++ {
		for j := i; j < len(entries); j++ {
			if i == j {
				continue
			}
			if entries[i]+entries[j] == 2020 {
				fmt.Println("\tfound", entries[i], entries[j])
				fmt.Println("\tanswer", entries[i]*entries[j])
				break searching1
			}
		}
	}
}

func solve2(entries []int) {
	if entries == nil {
		panic("input nil")
	}

	fmt.Println("Part two")
	// Another approach is to just return like this.
	for i := 0; i < len(entries); i++ {
		for j := i; j < len(entries); j++ {
			for k := j; k < len(entries); k++ {
				if i == j || i == k || j == k {
					continue
				}
				if entries[i]+entries[j]+entries[k] == 2020 {
					fmt.Println("\tfound", entries[i], entries[j], entries[k])
					fmt.Println("\tanswer", entries[i]*entries[j]*entries[k])
					return
				}
			}
		}
	}
}

func main() {
	// https://gosamples.dev/read-file/
	data, err := os.ReadFile("day01-sample.input")
	// data, err := os.ReadFile("day01.input")
	if err != nil {
		log.Fatal(err)
	}
	// https://stackoverflow.com/questions/9862443/golang-is-there-a-better-way-read-a-file-of-integers-into-an-array
	// https://zetcode.com/golang/readfile/
	content := strings.Split(string(data), "\n")

	// I don't know parsing well enough yet to avoid getting one last line of
	// what I assume is the EOF or newline or something
	entries := make([]int, len(content)-1)
	for i := 0; i < len(content); i++ {
		val, err := strconv.Atoi(content[i])
		if err != nil {
			continue
		}
		entries[i] = val
	}

	var part int
	flag.IntVar(&part, "part", 0, "part")
	flag.Parse()

	if part == 0 || part == 1 {
		solve1(entries)
	}
	if part == 0 || part == 2 {
		solve2(entries)
	}
}
