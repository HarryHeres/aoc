use std::{
    fs::File,
    io::{BufReader, Read, Seek, SeekFrom},
    ops::Range,
};

fn part_two(reader: &mut BufReader<File>, path: &Vec<usize>) -> u32 {
    let mut lines: String = String::new();
    reader
        .read_to_string(&mut lines)
        .expect("Could not read lines to string");

    let line_len: usize = lines.find("\n").unwrap() + 1;

    let end_line = lines.len() / line_len;
    let mut count = 0;

    for i in 0..end_line {
        let idx_range: Range<usize> = i * line_len..i * line_len + line_len - 1;
        let mut last_relevant: char = '\0';
        let mut inside: bool = false;

        // Jordan curve theorem algorithm
        for j in idx_range {
            let curr_char = lines.chars().nth(j).unwrap();
            match curr_char {
                '.' => {
                    last_relevant = '.';
                    if inside == true {
                        count += 1;
                    }
                }
                '|' => {
                    inside = !inside;
                }

                '-' => continue,
                // S case ???
                other => {
                    // F, 7, L, J
                    if path.contains(&j) {
                        if last_relevant == '.' {
                            last_relevant = other;
                            inside = !inside;
                        } else {
                            match (last_relevant, other) {
                                ('J', 'L') | ('L', 'J') | ('7', 'F') | ('F', '7') => {
                                    inside = !inside;
                                }

                                (_, _) => (),
                            }
                            last_relevant = '.';
                        }
                    }
                }
            }
        }
    }

    return count;
}

fn part_one(reader: &mut BufReader<File>) -> (usize, Vec<usize>) {
    let mut lines: String = String::new();
    reader
        .read_to_string(&mut lines)
        .expect("Could not read the input file");

    let line_len: usize = lines.find("\n").unwrap();

    let lookup_matrix: [isize; 4] = [(line_len + 1) as isize, 1, -((line_len + 1) as isize), -1]; //DOWN,
                                                                                                  //RIGHT,
                                                                                                  //UP,
                                                                                                  //LEFT

    let start_idx: usize = lines.find("S").unwrap();
    let mut valid_paths: Vec<Vec<usize>> = Vec::with_capacity(4);

    // Consider starting directions
    let mut starts: [isize; 4] = [0, 0, 0, 0];
    for i in 0..=3 {
        let lookup_idx: usize = (start_idx as isize + lookup_matrix[i]) as usize;
        let curr: char = lines.chars().nth(lookup_idx).unwrap_or('.');
        match (i, curr) {
            (0, '|') | (0, 'L') | (0, 'J') => starts[i] = lookup_idx as isize,
            (1, '-') | (1, '7') | (1, 'J') => starts[i] = lookup_idx as isize,
            (2, '|') | (2, '7') | (2, 'F') => starts[i] = lookup_idx as isize,
            (3, '-') | (3, 'F') | (3, 'L') => starts[i] = lookup_idx as isize,
            (_, _) => continue, // Invalid path
        }
    }

    // Loop through every possible path
    for i in 0..=3 {
        let curr_idx: isize = starts[i];
        if curr_idx < 0 {
            continue;
        }

        let mut curr_idx: usize = curr_idx as usize;
        let mut path: Vec<usize> = Vec::new();
        let mut from: usize = i;

        // Walk possible path until invalid char met or 'S'
        let mut next_idx: usize;
        let mut next_char: char;
        loop {
            let curr_char: char = lines.chars().nth(curr_idx).unwrap();
            match curr_char {
                '|' => {
                    next_idx = (curr_idx as isize + lookup_matrix[from]) as usize;
                    next_char = lines.chars().nth(next_idx).unwrap_or('.');
                    match (from, next_char) {
                        (0, 'L') | (0, 'J') => (),
                        (2, 'F') | (2, '7') => (),
                        (_, '|') => (),
                        (_, 'S') => (),
                        _ => break, // Cannot continue in this path
                    }
                }
                '-' => {
                    next_idx = (curr_idx as isize + lookup_matrix[from]) as usize;
                    next_char = lines.chars().nth(next_idx).unwrap_or('.');
                    match (from, next_char) {
                        (1, '7') | (1, 'J') => (),
                        (3, 'L') | (3, 'F') => (),
                        (_, '-') => (),
                        (_, 'S') => (),
                        _ => break, // Cannot continue in this path
                    }
                }

                'L' => {
                    let to = match from {
                        0 => 1,
                        3 => 2,
                        _ => break, // Invalid index
                    };

                    next_idx = (curr_idx as isize + lookup_matrix[to]) as usize;
                    next_char = lines.chars().nth(next_idx).unwrap_or('.');
                    match (from, next_char) {
                        (0, '-') | (0, 'J') | (0, '7') => (),
                        (3, '|') | (3, 'F') | (3, '7') => (),
                        (_, 'S') => (),
                        _ => break, // Cannot continue in this path
                    }
                    from = to;
                }

                'J' => {
                    let to = match from {
                        0 => 3,
                        1 => 2,
                        _ => break, // Invalid index
                    };

                    next_idx = (curr_idx as isize + lookup_matrix[to]) as usize;
                    next_char = lines.chars().nth(next_idx).unwrap_or('.');
                    match (from, next_char) {
                        (1, '|') | (1, '7') | (1, 'F') => (),
                        (0, '-') | (0, 'L') | (0, 'F') => (),
                        (_, 'S') => (),
                        _ => break, // Cannot continue in this path
                    }

                    from = to;
                }

                '7' => {
                    let to = match from {
                        1 => 0,
                        2 => 3,
                        _ => break, // Invalid index
                    };

                    next_idx = (curr_idx as isize + lookup_matrix[to]) as usize;
                    next_char = lines.chars().nth(next_idx).unwrap_or('.');
                    match (from, next_char) {
                        (1, '|') | (1, 'L') | (1, 'J') => (),
                        (2, '-') | (2, 'L') | (2, 'F') => (),
                        (_, 'S') => (),
                        _ => break, // Cannot continue in this path
                    }

                    from = to;
                }

                'F' => {
                    let to = match from {
                        2 => 1,
                        3 => 0,
                        _ => break, // Invalid index
                    };

                    next_idx = (curr_idx as isize + lookup_matrix[to]) as usize;
                    next_char = lines.chars().nth(next_idx).unwrap_or('.');
                    match (from, next_char) {
                        (2, '-') | (2, '7') | (2, 'J') => (),
                        (3, '|') | (3, 'L') | (3, 'J') => (),
                        (_, 'S') => (),
                        _ => break, // Cannot continue in this path
                    }

                    from = to;
                }

                'S' => {
                    path.push(curr_idx);
                    valid_paths.push(path);
                    break;
                }
                _ => break,
            }

            path.push(curr_idx);
            curr_idx = next_idx;
        }
    }

    let mut lowest_len: usize = valid_paths.iter().map(|path| path.len()).min().unwrap_or(0);
    'outer: for i in 0..lowest_len {
        let curr = valid_paths[0][i];
        for j in 1..valid_paths.len() {
            if valid_paths[j][i] != curr {
                continue 'outer;
            }
        }
        lowest_len = i + 1;
        break;
    }

    // for el in &valid_paths[0] {
    //     print!("{} -> ", lines.chars().nth(*el).unwrap());
    // }

    return (lowest_len, valid_paths[0].clone());
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let (farthest, path) = part_one(&mut reader);
    println!("Sum (part one): {farthest}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");

    let enclosed = part_two(&mut reader, &path);
    println!("Sum (part two) {enclosed}");
}
