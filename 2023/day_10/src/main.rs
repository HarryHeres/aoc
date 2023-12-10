use std::{
    fs::File,
    io::{BufReader, Read},
};

fn part_one(reader: &mut BufReader<File>) -> u32 {
    let mut lines: String = String::new();
    reader
        .read_to_string(&mut lines)
        .expect("Could not read the input file");

    let line_len: usize = lines.find("\n").unwrap();

    let lookup_matrix: [isize; 4] = [line_len as isize, 1, -(line_len as isize), -1]; //DOWN,
                                                                                      //RIGHT, UP,
                                                                                      //LEFT

    let start_idx: usize = lines.find("S").unwrap();
    let valid_paths: [Vec<usize>; 4];

    // Consider starting directions
    let mut starts: Vec<usize> = Vec::new();
    for i in 0..=3 {
        let lookup_idx: usize = (start_idx as isize + lookup_matrix[i]) as usize;
        let curr: char = lines.chars().nth(lookup_idx).unwrap_or('S');
        match (i, curr) {
            (0, '|') | (0, 'L') | (0, 'J') => starts.push(lookup_idx),
            (1, '-') | (1, '7') | (1, 'J') => starts.push(lookup_idx),
            (2, '|') | (2, '7') | (2, 'F') => starts.push(lookup_idx),
            (3, '-') | (3, 'F') | (3, 'L') => starts.push(lookup_idx),
            (_, _) => continue, // Invalid path
        }
    }

    for i in 0..starts.len() {
        let curr_idx: usize = starts[i];
        let curr_char: char = lines.chars().nth(curr_idx).unwrap();
        let from = i;
        let path: Vec<usize> = Vec::new();

        loop {
            match curr_char {
                '|' => match from {
                    0 => {}
                    2 => {}
                    _ => (),
                },
                _ => break,
            }
        }
    }

    return 0;
}

fn main() {
    let file: File = File::open("input_example.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let farthest = part_one(&mut reader);
    println!("Sum (part one): {farthest}")
}
