package main

import (
	"bufio"
	"fmt"
	"os"
)

func partTwo(scanner *bufio.Scanner) uint32 {
	return 0
}

func partOne(scanner *bufio.Scanner) uint32 {
	if scanner == nil {
		return 0
	}

	var rv uint32 = 0

	line := ""

	for scanner.Scan() {
		line = scanner.Text()

		firstCompartment := line[0 : len(line)/2]
		secondCompartment := line[len(line)/2 : len(line)]

		items := make(map[rune]int, len(line)/2)
		for k, _ := range items {
			items[k] = 0
		}

		for _, v := range firstCompartment {
			items[v] = 1
		}
	}

	return rv
}

func main() {
	file, err := os.Open("data/test.txt")
	// file, err := os.Open("data/input.txt")

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
