use std::{
    fs::{self, File},
    io::{BufRead, BufReader, Seek, SeekFrom},
};

fn part_1(reader: &mut BufReader<File>) -> u32 {
    const RED_MAX: u32 = 12;
    const GREEN_MAX: u32 = 13;
    const BLUE_MAX: u32 = 14;

    let result: u32 = reader
        .lines()
        .map(|line| line.unwrap())
        .map(|line| {
            let tmp: Vec<&str> = line.split(":").collect();
            let tmp2: Vec<&str> = tmp[0].split(" ").collect();
            let game_index: u32 = tmp2[1].parse::<u32>().unwrap();
            let mut possible: bool = true;

            tmp[1].split(";").for_each(|set| {
                set.split(",")
                    .map(|extract| extract.trim())
                    .for_each(|pair| {
                        let split: Vec<&str> = pair.split(" ").collect();
                        let number = split[0].parse::<u32>().unwrap();

                        match split[1] {
                            "red" => {
                                if number > RED_MAX {
                                    possible = false;
                                }
                            }
                            "green" => {
                                if number > GREEN_MAX {
                                    possible = false;
                                }
                            }
                            "blue" => {
                                if number > BLUE_MAX {
                                    possible = false;
                                }
                            }
                            _ => print!("ERROR!"),
                        }
                    });
            });

            if possible {
                println!("Possible game: {game_index}");
                return game_index;
            }

            return 0;
        })
        .sum::<u32>();

    return result;
}

fn part_2(reader: &mut BufReader<File>) -> u32 {
    let result: u32 = reader
        .lines()
        .map(|line| line.unwrap())
        .map(|line| {
            let tmp: Vec<&str> = line.split(":").collect();

            let mut red: u32 = 0;
            let mut green: u32 = 0;
            let mut blue: u32 = 0;

            tmp[1].split(";").for_each(|set| {
                set.split(",")
                    .map(|extract| extract.trim())
                    .for_each(|pair| {
                        let split: Vec<&str> = pair.split(" ").collect();
                        let number = split[0].parse::<u32>().unwrap();

                        match split[1] {
                            "red" => {
                                if number > red {
                                    red = number;
                                }
                            }
                            "green" => {
                                if number > green {
                                    green = number;
                                }
                            }
                            "blue" => {
                                if number > blue {
                                    blue = number;
                                }
                            }
                            _ => print!("ERROR!"),
                        }
                    });
            });

            return red * green * blue;
        })
        .sum::<u32>();

    return result;
}

fn main() {
    let file: File =
        fs::File::open("input.txt").expect("File could not have been opened for reading");
    let mut reader: BufReader<fs::File> = BufReader::new(file);

    let sum = part_1(&mut reader);
    println!("Sum of possible IDs: {sum}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");

    let sum = part_2(&mut reader);
    println!("Sum of all games: {sum}");
}
