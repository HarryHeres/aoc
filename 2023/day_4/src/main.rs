use std::{
    fs::File,
    io::{BufRead, BufReader, Seek, SeekFrom},
};

fn part_2(reader: &mut BufReader<File>, line_count: usize) -> u32 {
    let mut counts: Vec<u32> = vec![1; line_count];
    let mut idx: usize = 0;

    let sum: u32 = reader
        .lines()
        .map(|line| line.unwrap())
        .map(|line| {
            let mut vec_winning: Vec<u32> = Vec::new();
            let mut vec_card: Vec<u32> = Vec::new();

            let temp: Vec<&str> = line.split(": ").collect();
            let temp: Vec<&str> = temp[1].split(" | ").collect();

            for i in 0..=1 {
                match i {
                    0 => {
                        vec_winning = temp[0]
                            .trim()
                            .split_whitespace()
                            .map(|num| num.parse::<u32>().unwrap())
                            .collect();
                    }
                    1 => {
                        vec_card = temp[1]
                            .trim()
                            .split_whitespace()
                            .map(|num| num.parse::<u32>().unwrap())
                            .collect();
                    }

                    _ => println!("ERROR"),
                }
            }

            let mut count_matching: u32 = 0;
            vec_card.into_iter().for_each(|num| {
                if vec_winning.contains(&num) {
                    count_matching += 1;
                }
            });

            for j in 1..=count_matching as usize {
                counts[idx + j] += 1 * counts[idx];
            }

            idx += 1;
            return counts[idx - 1];
        })
        .sum::<u32>();

    return sum;
}

fn part_1(reader: &mut BufReader<File>) -> u32 {
    let sum: u32 = reader
        .lines()
        .map(|line| line.unwrap())
        .map(|line| {
            let mut sum: u32 = 0;
            let mut vec_winning: Vec<u32> = Vec::new();
            let mut vec_card: Vec<u32> = Vec::new();

            let temp: Vec<&str> = line.split(": ").collect();
            let temp: Vec<&str> = temp[1].split(" | ").collect();

            for i in 0..=1 {
                match i {
                    0 => {
                        vec_winning = temp[0]
                            .trim()
                            .split_whitespace()
                            .map(|num| num.parse::<u32>().unwrap())
                            .collect();
                    }
                    1 => {
                        vec_card = temp[1]
                            .trim()
                            .split_whitespace()
                            .map(|num| num.parse::<u32>().unwrap())
                            .collect();
                    }

                    _ => println!("ERROR"),
                }
            }

            vec_card.into_iter().for_each(|num| {
                if vec_winning.contains(&num) {
                    if sum == 0 {
                        sum = 1;
                    } else {
                        sum *= 2;
                    }
                }
            });
            return sum;
        })
        .sum::<u32>();

    return sum;
}

fn main() {
    let mut file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file); // Consumes the file handle

    let sum = part_1(&mut reader);
    println!("Part one: {sum}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beggining of the file");

    let line_count: usize = reader.lines().count(); // Consumes the reader

    file = File::open("input.txt").expect("Could not open the input file");
    reader = BufReader::new(file);

    let sum = part_2(&mut reader, line_count);
    println!("Part two: {sum}");
}
