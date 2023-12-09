use std::{
    fs::File,
    io::{BufRead, BufReader, Seek, SeekFrom},
};

const MAPS_COUNT: usize = 7;

struct Range {
    source: u64,
    source_end: u64,
    dest: u64,
}

fn part_2(reader: &mut BufReader<File>) -> u64 {
    let mut buf: String = String::new();
    reader
        .read_line(&mut buf)
        .expect("Could not parse the first line in the file");

    let parsed: Vec<u64> = buf
        .split("seeds:")
        .nth(1)
        .unwrap()
        .split_whitespace()
        .map(|seed| seed.parse::<u64>().unwrap())
        .collect();

    let mut seeds: Vec<u64> = Vec::new();
    parsed.chunks(2).for_each(|pair| {
        for i in pair[0]..(pair[0] + pair[1] - 1) {
            seeds.push(i);
        }
    });

    let mut idx: i32 = -1;
    let mut maps: Vec<Vec<Range>> = Vec::new();

    for _ in 0..=(MAPS_COUNT - 1) {
        maps.push(Vec::new());
    }

    reader.lines().map(|line| line.unwrap()).for_each(|line| {
        match line.chars().next().unwrap_or(' ') {
            'a'..='z' | 'A'..='Z' => idx += 1,
            '0'..='9' => {
                let split: Vec<u64> = line
                    .split_whitespace()
                    .map(|num| num.parse::<u64>().unwrap())
                    .collect();

                maps[idx as usize].push(Range {
                    source: split[1],
                    source_end: split[1] + split[2],
                    dest: split[0],
                });
            }
            _ => (),
        }
    });

    return seeds
        .into_iter()
        .map(|seed| {
            let mut tmp: u64 = seed;
            for i in 0..=(MAPS_COUNT - 1) {
                let map = &maps[i];
                for j in 0..map.len() {
                    if tmp < map[j].source || tmp > map[j].source_end {
                        continue;
                    }

                    tmp += map[j].dest - map[j].source;
                    break;
                }
            }
            return tmp;
        })
        .min()
        .unwrap();
}

fn part_1(reader: &mut BufReader<File>) -> u64 {
    let mut seeds: Vec<u64> = Vec::new();

    let mut buf: String = String::new();
    reader
        .read_line(&mut buf)
        .expect("Could not parse the first line in the file");

    buf.split("seeds:")
        .nth(1)
        .unwrap()
        .split_whitespace()
        .for_each(|seed| seeds.push(seed.parse::<u64>().unwrap()));

    let mut idx: i32 = -1;
    let mut maps: Vec<Vec<Range>> = Vec::new();

    for _ in 0..=(MAPS_COUNT - 1) {
        maps.push(Vec::new());
    }

    reader.lines().map(|line| line.unwrap()).for_each(|line| {
        match line.chars().next().unwrap_or(' ') {
            'a'..='z' | 'A'..='Z' => idx += 1,
            '0'..='9' => {
                let split: Vec<u64> = line
                    .split_whitespace()
                    .map(|num| num.parse::<u64>().unwrap())
                    .collect();

                maps[idx as usize].push(Range {
                    source: split[1],
                    source_end: split[1] + split[2],
                    dest: split[0],
                });
            }
            _ => (),
        }
    });

    return seeds
        .into_iter()
        .map(|seed| {
            let mut tmp: u64 = seed;
            for i in 0..=(MAPS_COUNT - 1) {
                let map = &maps[i];
                for j in 0..map.len() {
                    if tmp < map[j].source || tmp > map[j].source_end {
                        continue;
                    }

                    tmp = map[j].dest + (tmp - map[j].source);
                    break;
                }
            }
            return tmp;
        })
        .min()
        .unwrap();
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let mut closest: u64 = part_1(&mut reader);
    println!("Closest location (part 1): {closest}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");

    closest = part_2(&mut reader); // NOTE: Runtime ~2 mins
    println!("Closest location (part 2): {closest}");
}
