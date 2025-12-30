package aoc_runner

import (
	"flag"
)

func Run(samples func(), part1 func([]string), part2 func([]string), input []string) {
	var part int
	flag.IntVar(&part, "part", 0, "part")
	flag.Parse()

	switch part  {
	case 1:
		part1(input);
		break
	case 2:
		part2(input);
		break
	default:
		samples();
		part1(input);
		part2(input);
		break
	}
}
