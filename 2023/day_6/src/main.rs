use std::{
    fs::File,
    io::{BufRead, BufReader, Seek, SeekFrom},
};

fn part_two(reader: &mut BufReader<File>) -> u64 {
    let mut result: u64 = 1;

    let mut buf: String = String::new();
    reader
        .read_line(&mut buf)
        .expect("Could not read line in the file");

    let mut time: String = String::new();
    buf.split(":")
        .nth(1)
        .unwrap()
        .trim()
        .split_whitespace()
        .for_each(|num| time += num);

    let time: u64 = time.parse::<u64>().unwrap();

    buf.clear();
    reader
        .read_line(&mut buf)
        .expect("Could not read line in the file");

    let mut distance: String = String::new();
    buf.split(":")
        .nth(1)
        .unwrap()
        .trim()
        .split_whitespace()
        .for_each(|num| distance += num);

    let distance: u64 = distance.parse::<u64>().unwrap();

    let mut count: u64 = 0;

    for j in 0..(time - 1) {
        if (j * (time - j)) > distance {
            count += 1;
        }
    }

    if count > 0 {
        result *= count;
    }

    return result;
}

fn part_one(reader: &mut BufReader<File>) -> u32 {
    let mut result: u32 = 1;

    let mut buf: String = String::new();
    reader
        .read_line(&mut buf)
        .expect("Could not read line in the file");

    let times: Vec<u32> = buf
        .split(":")
        .nth(1)
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|num| num.parse::<u32>().unwrap())
        .collect();

    buf.clear();
    reader
        .read_line(&mut buf)
        .expect("Could not read line in the file");

    let distances: Vec<u32> = buf
        .split(":")
        .nth(1)
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|num| num.parse::<u32>().unwrap())
        .collect();

    for i in 0..=(times.len() - 1) {
        let mut count: u32 = 0;
        let curr_time: u32 = times[i];
        let curr_dist: u32 = distances[i];

        for j in 0..(curr_time - 1) {
            if (j * (curr_time - j)) > curr_dist {
                count += 1;
            }
        }
        if count > 0 {
            result *= count;
        }
    }

    return result;
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let result: u32 = part_one(&mut reader);
    println!("Result (part one): {result}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");

    let result: u64 = part_two(&mut reader);
    println!("Result (part two): {result}");
}
