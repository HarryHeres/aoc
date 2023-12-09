use std::fs::File;
use std::io::{BufReader, Read, Seek, SeekFrom};

const NO_LOOKUP: i32 = 0;

fn get_num_from_pos(input: &[u8], pos: usize) -> u32 {
    let mut num: String = String::new();
    let mut barrier_left: bool = false;
    let mut barrier_right: bool = false;

    let mut ldx: i32 = pos as i32;
    let mut rdx: usize = pos;

    num.push(input[pos] as char);

    loop {
        ldx -= 1;
        rdx += 1;

        if ldx >= 0 && barrier_left == false {
            match input[ldx as usize] {
                // [0-9]
                0x30..=0x39 => {
                    num = (input[ldx as usize] as char).to_string() + num.as_str();
                }
                _ => barrier_left = true,
            }
        } else {
            barrier_left = true;
        }

        if rdx < input.len() && barrier_right == false {
            match input[rdx] {
                0x30..=0x39 => {
                    num.push(input[rdx] as char);
                }
                _ => barrier_right = true,
            }
        } else {
            barrier_right = true;
        }

        if barrier_right && barrier_left {
            break;
        }
    }

    return num.parse::<u32>().unwrap();
}

fn part_2(reader: &mut BufReader<File>) -> u32 {
    let mut sum: u32 = 0;

    let mut input: String = String::new();
    reader
        .read_to_string(&mut input)
        .expect("Could not read file's contents");

    let line_len: usize = input.find('\n').unwrap() + 1; // +1 cuz of newlines
    let input: &[u8] = input.as_bytes();
    let mut curr_char: char;
    let mut lookup_matrix: [i32; 9];

    let tmp_len: i32 = line_len as i32;
    for i in 0..input.len() {
        curr_char = input[i] as char;
        match curr_char {
            '*' => {
                let mut lookup_val: i32;
                let input_len: usize = input.len() as usize;

                // Default corresponds to
                // [1,1,1
                //  1,0,1
                //  1,1,1]
                lookup_matrix = [
                    -tmp_len - 1,
                    -tmp_len,
                    -tmp_len + 1,
                    -1,
                    NO_LOOKUP,
                    1,
                    tmp_len - 1,
                    tmp_len,
                    tmp_len + 1,
                ];

                // First line
                if i < line_len {
                    lookup_matrix[0] = NO_LOOKUP;
                    lookup_matrix[1] = NO_LOOKUP;
                    lookup_matrix[2] = NO_LOOKUP;
                }

                // Last line
                if i + line_len > input_len - 1 {
                    lookup_matrix[6] = NO_LOOKUP;
                    lookup_matrix[7] = NO_LOOKUP;
                    lookup_matrix[8] = NO_LOOKUP;
                }

                // Most left
                if i == 0 || (i % line_len) == 0 {
                    lookup_matrix[0] = NO_LOOKUP;
                    lookup_matrix[3] = NO_LOOKUP;
                    lookup_matrix[6] = NO_LOOKUP;
                }

                // Most right
                if i % line_len == line_len - 1 {
                    lookup_matrix[2] = NO_LOOKUP;
                    lookup_matrix[5] = NO_LOOKUP;
                    lookup_matrix[8] = NO_LOOKUP;
                }

                let mut found: Vec<u32> = Vec::new();
                for k in 0..lookup_matrix.len() {
                    lookup_val = i as i32 + lookup_matrix[k];
                    match lookup_val {
                        NO_LOOKUP => continue,
                        _ => {
                            let symbol: u8 = input[lookup_val as usize];
                            match symbol {
                                0x30..=0x39 => {
                                    let val = get_num_from_pos(input, lookup_val as usize);
                                    if !found.contains(&val) {
                                        found.push(val);
                                    }
                                }
                                _ => continue,
                            }
                        }
                    }
                }

                if found.len() == 2 {
                    sum += found[0] * found[1];
                }
            }

            _ => continue,
        }
    }

    return sum;
}

fn part_1(reader: &mut BufReader<File>) -> u32 {
    let mut sum: u32 = 0;

    let mut input: String = String::new();
    reader
        .read_to_string(&mut input)
        .expect("Could not read file's contents");

    let line_len: usize = input.find('\n').unwrap() + 1; // +1 cuz of newlines

    let input: &[u8] = input.as_bytes();
    let mut curr_char: char;
    let mut curr_num: String = String::new();
    let tmp_len: i32 = line_len as i32;
    let mut lookup_matrix: [i32; 9];

    for i in 0..input.len() {
        curr_char = input[i] as char;
        match curr_char {
            '0'..='9' => curr_num.push(curr_char),
            _ => {
                if !curr_num.is_empty() {
                    let mut valid: bool = false;
                    let mut lookup_val: i32;
                    let input_len: usize = input.len() as usize;

                    {
                        let curr_num: &[u8] = curr_num.as_bytes();
                        let mut curr_idx;
                        let curr_num_len = curr_num.len();
                        for j in 0..curr_num_len {
                            // Default corresponds to
                            // [1,1,1
                            //  1,0,1
                            //  1,1,1]
                            lookup_matrix = [
                                -tmp_len - 1,
                                -tmp_len,
                                -tmp_len + 1,
                                -1,
                                NO_LOOKUP,
                                1,
                                tmp_len - 1,
                                tmp_len,
                                tmp_len + 1,
                            ];

                            curr_idx = i - curr_num_len + j;

                            // First line
                            if curr_idx < line_len {
                                lookup_matrix[0] = NO_LOOKUP;
                                lookup_matrix[1] = NO_LOOKUP;
                                lookup_matrix[2] = NO_LOOKUP;
                            }

                            // Last line
                            if curr_idx + line_len > input_len - 1 {
                                lookup_matrix[6] = NO_LOOKUP;
                                lookup_matrix[7] = NO_LOOKUP;
                                lookup_matrix[8] = NO_LOOKUP;
                            }

                            // Most left
                            if curr_idx == 0 || (curr_idx % line_len) == 0 {
                                lookup_matrix[0] = NO_LOOKUP;
                                lookup_matrix[3] = NO_LOOKUP;
                                lookup_matrix[6] = NO_LOOKUP;
                            }

                            // Most right
                            if curr_idx % line_len == line_len - 1 {
                                lookup_matrix[2] = NO_LOOKUP;
                                lookup_matrix[5] = NO_LOOKUP;
                                lookup_matrix[8] = NO_LOOKUP;
                            }

                            for k in 0..lookup_matrix.len() {
                                lookup_val = curr_idx as i32 + lookup_matrix[k];
                                match lookup_val {
                                    NO_LOOKUP => continue,
                                    _ => {
                                        let symbol: u8 = input[lookup_val as usize];
                                        match symbol {
                                            //[0-9]| ASCII '.' | [A-Z] | [a-z] | \n
                                            0x30..=0x39
                                            | 0x2E
                                            | 0x41..=0x5A
                                            | 0x61..=0x7A
                                            | 0x0A => continue,
                                            _ => {
                                                // println!(
                                                // "Found valid symbol {} at index {lookup_val}",
                                                // symbol as char
                                                // );
                                                valid = true;
                                            }
                                        }
                                    }
                                }
                            }

                            if valid == true {
                                break;
                            }
                        }
                    }

                    if valid == true {
                        sum += curr_num.parse::<u32>().unwrap()
                    }

                    curr_num = String::new();
                }
            }
        }
    }

    return sum;
}

fn main() {
    let file: File = File::open("input.txt").expect("File could not have been opened");
    let mut reader: BufReader<File> = BufReader::new(file);

    let sum = part_1(&mut reader);
    println!("Part 1: {sum}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");
    let sum = part_2(&mut reader);
    println!("Part 2: {sum}");
}
