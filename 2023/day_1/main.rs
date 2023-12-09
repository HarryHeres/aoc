use std::fs::{self, File};
use std::io::{BufRead, BufReader, Seek, SeekFrom};

fn part_1(reader: &mut BufReader<File>) -> u32 {
    let mut first: u32 = 0;
    let mut last: u32 = 0;
    let mut sum: u32 = 0;

    const RADIX: u32 = 10;

    for line in reader.lines() {
        for char in line.unwrap().chars() {
            match char {
                '1'..='9' => {
                    if first == 0 {
                        first = match char.to_digit(RADIX) {
                            Some(x) => x,
                            None => continue,
                        };
                    }
                    last = match char.to_digit(RADIX) {
                        Some(x) => x,
                        None => continue,
                    };
                }
                _ => continue,
            }
        }

        sum += first * RADIX + last;
        first = 0;
        last = 0;
    }

    return sum;
}

fn part_2(reader: &mut BufReader<File>) -> u32 {
    let options: [(&str, u32); 18] = [
        ("1", 1),
        ("2", 2),
        ("3", 3),
        ("4", 4),
        ("5", 5),
        ("6", 6),
        ("7", 7),
        ("8", 8),
        ("9", 9),
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
    ];

    let result: u32 = reader
        .lines()
        .map(|line| line.unwrap())
        .map(|line| {
            let mut first: u32 = 0;
            let mut last: u32 = 0;
            let mut found = false;

            for i in 0..line.len() {
                let substring = &line[0 + i..line.len()];

                for j in 0..options.len() {
                    if substring.starts_with(options[j].0) {
                        first = options[j].1;
                        found = true;
                        break;
                    }
                }

                if found == true {
                    break;
                };
            }

            found = false;
            for i in 0..line.len() {
                let substring = &line[0..line.len() - i];

                for j in 0..options.len() {
                    if substring.ends_with(options[j].0) {
                        last = options[j].1;
                        found = true;
                        break;
                    }
                }

                if found == true {
                    break;
                }
            }

            return first * 10 + last;
        })
        .sum::<u32>();

    return result;
}

fn main() {
    let file: File =
        fs::File::open("input.txt").expect("File could not have been opened for reading");
    let mut reader: BufReader<fs::File> = BufReader::new(file);

    println!("Digit sum: {}", part_1(&mut reader));
    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");
    println!("Word sum: {}", part_2(&mut reader));
}
