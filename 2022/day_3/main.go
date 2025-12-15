package main

import (
	"bufio"
	"fmt"
	"os"
)

func partTwo(scanner *bufio.Scanner) uint32 {
	if scanner == nil {
		return 0
	}

	var rv uint32 = 0

	first := ""
	second := ""
	third := ""
	for scanner.Scan() {
		first = scanner.Text()

		scanner.Scan()
		second = scanner.Text()
		scanner.Scan()
		third = scanner.Text()

		items := make(map[rune]int, max(len(first), len(second), len(third)))
		for k := range items {
			items[k] = 0
		}

		for _, v := range first {
			if items[v] == 0 {
				items[v] = 1
			}
		}

		for _, v := range second {
			if items[v] == 1 {
				items[v] = 2
			}
		}

		for _, v := range third {
			if items[v] == 2 {
				items[v] = 3
			}
		}

		for k, v := range items {
			if v == 3 {
				if k > 96 {
					rv += uint32(k - 96)
				} else {
					rv += uint32(k - 64 + 26)
				}

				items[k] = 4
			}
		}
	}

	return rv
}

func partOne(scanner *bufio.Scanner) uint32 {
	if scanner == nil {
		return 0
	}

	var rv uint32 = 0

	line := ""

	for scanner.Scan() {
		line = scanner.Text()

		firstCompartment := line[:len(line)/2]
		secondCompartment := line[len(line)/2:]

		items := make(map[rune]int, len(line)/2)
		for k := range items {
			items[k] = 0
		}

		for _, v := range firstCompartment {
			items[v] = 1
		}

		for _, v := range secondCompartment {
			if items[v] == 1 {
				if v > 96 {
					rv += uint32(v - 96)
				} else {
					rv += uint32(v - 64 + 26)
				}

				items[v] = 2
			}
		}
	}

	return rv
}

func main() {
	// file, err := os.Open("data/test.txt")
	file, err := os.Open("data/input.txt")

	if err != nil {
		panic(err)
	}

	scanner := bufio.NewScanner(file)
	fmt.Printf("Part one: %d\n", partOne(scanner))

	_, err = file.Seek(0, 0)
	if err != nil {
		panic(err)
	}

	scanner = bufio.NewScanner(file)
	fmt.Printf("Part two: %d", partTwo(scanner))

	err = file.Close()
	if err != nil {
		panic(err)
	}
}
