use std::{
    fs::File,
    io::{BufReader, Read},
    thread, time,
};

enum Direction {
    N,
    S,
    W,
    E,
}

struct Ray {
    curr_idx: usize,
    visited_nodes: Vec<usize>,
    curr_direction: Direction,
}

fn part_one(reader: &mut BufReader<File>) -> u32 {
    let mut remaining_rays: Vec<Ray> = Vec::new();

    let mut lines: String = String::new();
    reader
        .read_to_string(&mut lines)
        .expect("Could not read the contents of the input file");

    // let mut lines_copy = lines.clone(); // For visualization

    let line_len: usize = lines.find("\n").unwrap() + 1;
    let line_count: usize = lines.chars().filter(|char| char == &'\n').count();

    let mut energized_nodes: Vec<usize> = Vec::with_capacity(line_count * line_len);

    remaining_rays.push(Ray {
        curr_idx: 0,
        visited_nodes: Vec::new(),
        curr_direction: Direction::S,
    });

    loop {
        let curr_ray: Option<Ray> = remaining_rays.pop();
        if curr_ray.is_none() {
            break;
        }

        let mut curr_ray: Ray = curr_ray.unwrap();
        let mut counter = 0;
        loop {
            if curr_ray.visited_nodes.contains(&curr_ray.curr_idx) {
                counter += 1;
                if counter == 2 {
                    break;
                }
            } else {
                counter = 0;
            }

            energized_nodes.push(curr_ray.curr_idx);
            curr_ray.visited_nodes.push(curr_ray.curr_idx);

            // Visualization
            // print!("{esc}c", esc = 27 as char);
            // lines_copy.replace_range(curr_ray.curr_idx..curr_ray.curr_idx + 1, "#");
            // println!("{lines_copy}");
            // thread::sleep(time::Duration::from_millis(10));

            let mut next: i32 = curr_ray.curr_idx as i32;

            match curr_ray.curr_direction {
                Direction::N => {
                    next += -(line_len as i32);

                    match lines.chars().nth(next as usize) {
                        None => break,
                        Some(char) => match char {
                            '/' => curr_ray.curr_direction = Direction::E,
                            '\\' => curr_ray.curr_direction = Direction::W,
                            '|' => (),
                            '-' => {
                                // Cycle detection
                                if !energized_nodes.contains(&(next as usize)) {
                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::E,
                                    });

                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::W,
                                    });
                                }

                                break;
                            }
                            _ => (),
                        },
                    }
                }
                Direction::E => {
                    next += 1;

                    match lines.chars().nth(next as usize) {
                        None => break,
                        Some(char) => match char {
                            '/' => curr_ray.curr_direction = Direction::N,
                            '\\' => curr_ray.curr_direction = Direction::S,
                            '|' => {
                                // Cycle detection
                                if !energized_nodes.contains(&(next as usize)) {
                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::N,
                                    });

                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::S,
                                    });
                                }
                                break;
                            }
                            '-' => (),
                            '\n' => break,
                            _ => (),
                        },
                    }
                }
                Direction::W => {
                    next += -1;

                    match lines.chars().nth(next as usize) {
                        None => break,
                        Some(char) => match char {
                            '/' => curr_ray.curr_direction = Direction::S,
                            '\\' => curr_ray.curr_direction = Direction::N,
                            '|' => {
                                if !energized_nodes.contains(&(next as usize)) {
                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::N,
                                    });

                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::S,
                                    });
                                }
                                break;
                            }
                            '-' => (),
                            '\n' => break,
                            _ => (),
                        },
                    }
                }
                Direction::S => {
                    next += line_len as i32;

                    match lines.chars().nth(next as usize) {
                        None => break,
                        Some(char) => match char {
                            '/' => curr_ray.curr_direction = Direction::W,
                            '\\' => curr_ray.curr_direction = Direction::E,
                            '|' => (),
                            '-' => {
                                if !energized_nodes.contains(&(next as usize)) {
                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::E,
                                    });

                                    remaining_rays.push(Ray {
                                        curr_idx: next as usize,
                                        visited_nodes: Vec::new(),
                                        curr_direction: Direction::W,
                                    });
                                }
                                break;
                            }
                            _ => (),
                        },
                    }
                }
            }

            curr_ray.curr_idx = next as usize;
        }
    }

    let mut tmp: Vec<usize> = Vec::new();

    energized_nodes.iter().for_each(|node| {
        if !tmp.contains(node) {
            tmp.push(*node);
        }
    });

    return tmp.iter().count() as u32;
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    // Part two was just manually changing start positions
    let sum: u32 = part_one(&mut reader);
    println!("Sum (part one): {sum}");
}
