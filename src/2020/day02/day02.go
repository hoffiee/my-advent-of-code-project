/**
 * Second attempt, lets' see if this ends up a bit neater
 */
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
)

func main() {
	// https://gosamples.dev/read-file/
	// file, err := os.Open("day02-sample.input")
	file, err := os.Open("day02.input")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	valid1 := 0
	valid2 := 0

	for scanner.Scan() {
		line := scanner.Text()
		var a, b int
		var password string
		var letter rune
		_, err := fmt.Sscanf(line, "%d-%d %c: %s", &a, &b, &letter, &password)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(line, a, b, string(letter), password)

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

	var part int
	flag.IntVar(&part, "part", 0, "part")
	flag.Parse()

	if part == 0 || part == 1 {
		fmt.Println(valid1)
	}
	if part == 0 || part == 2 {
		fmt.Println(valid2)
	}
}
