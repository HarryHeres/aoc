use std::{
    collections::HashMap,
    fs::File,
    io::{BufReader, Read, Seek, SeekFrom},
};

fn rotate_vector(lines: &Vec<u8>, row_count: usize, col_count: usize) -> (Vec<u8>, usize, usize) {
    let mut rotated: Vec<u8> = Vec::with_capacity(lines.len());

    for col_idx in 0..col_count - 1 {
        for row_idx in 0..row_count {
            let idx = col_idx + (row_count - 1 - row_idx) * col_count;
            rotated.push(lines[idx]);
        }
        rotated.push('\n' as u8);
    }

    return (rotated, col_count - 1, row_count + 1);
}

fn tilt(lines: &mut Vec<u8>, line_len: usize) {
    let idx_range = 0..lines.iter().count();
    for i in idx_range.clone() {
        let char = lines[i] as char;
        if char == 'O' {
            let mut lookup_idx: i32 = i as i32;
            loop {
                lookup_idx -= line_len as i32;
                if !idx_range.contains(&(lookup_idx as usize)) {
                    lines[i] = '.' as u8;
                    lines[(lookup_idx + line_len as i32) as usize] = char as u8;
                    break;
                }
                match lines[lookup_idx as usize] as char {
                    'O' | '#' | '\n' => {
                        lines[i] = '.' as u8;
                        lines[(lookup_idx + line_len as i32) as usize] = char as u8;
                        break;
                    }
                    _ => continue,
                }
            }
        }
    }
}

fn do_a_cycle(lines: &mut Vec<u8>, row_count: &mut usize, col_count: &mut usize) {
    let cycle: [char; 4] = ['N', 'W', 'S', 'E'];
    for _ in cycle {
        tilt(lines, *col_count);
        (*lines, *row_count, *col_count) = rotate_vector(lines, *row_count, *col_count);
    }

    // lines.iter().for_each(|line| {
    //     let line: char = *line as char;
    //     print!("{line}");
    // });
    // println!("-----");
}

fn part_two(reader: &mut BufReader<File>) -> u64 {
    let mut lines: String = String::new();

    reader
        .read_to_string(&mut lines)
        .expect("Could not read the input file contents into a string");

    let mut row_count = lines.split("\n").count() - 1;
    let mut col_count = lines.find("\n").unwrap() + 1;

    let mut lines: Vec<u8> = lines.chars().map(|char| char as u8).collect();

    const CYCLE_COUNT: u64 = 1_000_000_000;
    let mut map: HashMap<Vec<u8>, u64> = HashMap::new();

    for i in 0..CYCLE_COUNT {
        if i > 0 && i % 9_999_999 == 0 {
            println!("Done {}/100", i / 9_999_999);
        }
        do_a_cycle(&mut lines, &mut row_count, &mut col_count);
        match map.get(&lines) {
            Some(val) => {
                println!("Detected a cycle at {i}");
                let remaining = CYCLE_COUNT - 1 - i;
                let period = i - val;
                for _ in 0..remaining % period {
                    // Perform the remaining period
                    do_a_cycle(&mut lines, &mut row_count, &mut col_count)
                }
                break;
            }
            None => {
                map.insert(lines.clone(), i);
                continue;
            }
        }
    }

    let mut sum: u64 = 0;

    for row_idx in 0..row_count {
        for col_idx in 0..col_count {
            if lines[row_idx * col_count + col_idx] == 'O' as u8 {
                sum += (row_count - row_idx) as u64;
            }
        }
    }

    return sum;
}

fn part_one(reader: &mut BufReader<File>) -> u32 {
    let mut lines: String = String::new();

    reader
        .read_to_string(&mut lines)
        .expect("Could not read the input file contents into a string");

    let line_count = lines.split("\n").count() - 1;
    let line_len = lines.find("\n").unwrap() + 1;

    let mut idx = 0;
    let mut map: HashMap<usize, usize> = HashMap::new(); // Old position, new position

    let lines = lines.chars();
    lines.clone().for_each(|char| {
        if char == 'O' {
            let mut lookup_idx: usize = idx;
            if idx < line_len {
                map.insert(idx, line_count);
            } else {
                loop {
                    lookup_idx -= line_len;

                    match lines.clone().nth(lookup_idx) {
                        Some(val) => match val {
                            'O' => {
                                map.insert(idx, map[&lookup_idx] - 1);
                                break;
                            }
                            '#' => {
                                map.insert(idx, line_count - lookup_idx / line_len - 1);
                                break;
                            }
                            _ => {
                                if lookup_idx < line_len && map.get(&lookup_idx) == None {
                                    map.insert(idx, line_count);
                                    break;
                                }
                                continue;
                            }
                        },
                        None => {
                            map.insert(idx, line_count);
                            break;
                        }
                    }
                }
            }
        }
        idx += 1;
    });

    return map.iter().map(|(_, v)| v).sum::<usize>() as u32;
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let sum: u32 = part_one(&mut reader);
    println!("Sum (part one): {sum}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");

    let sum: u64 = part_two(&mut reader);
    println!("Sum (part two): {sum}");
}
