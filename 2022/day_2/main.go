package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func partTwo(scanner *bufio.Scanner) uint32 {
	if scanner == nil {
		return 0
	}

	var rv uint32 = 0

	line := ""

	for scanner.Scan() {
		line = scanner.Text()
		round := strings.Split(line, " ")

		switch round[0] {
		case "A":
			switch round[1] {
			case "X":
				rv += 0 + 3
			case "Y":
				rv += 3 + 1
			case "Z":
				rv += 6 + 2
			}
		case "B":
			switch round[1] {
			case "X":
				rv += 0 + 1
			case "Y":
				rv += 3 + 2
			case "Z":
				rv += 6 + 3
			}
		case "C":
			switch round[1] {
			case "X":
				rv += 0 + 2
			case "Y":
				rv += 3 + 3
			case "Z":
				rv += 6 + 1
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
		round := strings.Split(line, " ")

		switch round[1] {
		case "X":
			rv++
		case "Y":
			rv += 2
		case "Z":
			rv += 3
		}

		switch {
		case round[0] == "A" && round[1] == "X":
			rv += 3
		case round[0] == "B" && round[1] == "Y":
			rv += 3
		case round[0] == "C" && round[1] == "Z":
			rv += 3
		case round[0] == "A" && round[1] == "Y":
			rv += 6
		case round[0] == "B" && round[1] == "Z":
			rv += 6
		case round[0] == "C" && round[1] == "X":
			rv += 6
		default:
			{
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
