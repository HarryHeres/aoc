package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func partTwo(scanner *bufio.Scanner) int32 {
	if scanner == nil {
		return 0
	}

	max := []int32{0, 0, 0}

	var currSum int32 = 0
	line := ""
	for scanner.Scan() {
		line = scanner.Text()

		if len(line) == 0 {
			for i := range len(max) {
				if max[i] < currSum {
					for j := len(max) - 1; j > i; j-- {
						max[j] = max[j-1]
					}

					max[i] = currSum
					break
				}
			}

			currSum = 0
		} else {
			val, err := strconv.ParseInt(line, 10, 32)
			if err != nil {
				panic(err)
			}

			currSum += int32(val)
		}
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	return max[0] + max[1] + max[2]
}

func partOne(scanner *bufio.Scanner) int32 {
	if scanner == nil {
		return 0
	}

	var maxSum int32 = 0

	var currSum int32 = 0
	line := ""
	for scanner.Scan() {
		line = scanner.Text()

		if len(line) == 0 {
			if maxSum < currSum {
				maxSum = currSum
			}
			currSum = 0
		} else {
			val, err := strconv.ParseInt(line, 10, 32)
			if err != nil {
				panic(err)
			}

			currSum += int32(val)
		}
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	return maxSum
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
