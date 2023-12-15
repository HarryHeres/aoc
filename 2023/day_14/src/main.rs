use std::{
    collections::HashMap,
    fs::File,
    io::{BufReader, Read},
};

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
}
