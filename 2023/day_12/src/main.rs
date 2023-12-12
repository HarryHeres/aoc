use std::{
    fs::File,
    io::{BufRead, BufReader},
};

fn check_if_comb_valid(current: &String, correct: &Vec<u32>) -> bool {
    let groups: Vec<&str> = current.split(".").filter(|group| group.len() > 0).collect();
    if groups.len() == correct.len() {
        for i in 0..groups.len() {
            if groups[i].len() != correct[i] as usize {
                return false;
            }
        }
        return true;
    }
    return false;
}

fn find_combinations(damaged: String, correct: &Vec<u32>) -> u32 {
    let mut count = 0;

    let missing = damaged
        .chars()
        .into_iter()
        .filter(|char| char.eq(&'?'))
        .count();

    let mut char_mask: u32 = 0b0000_0000_0000_0000;
    let base: u32 = 2;
    let iters: u32 = base.pow(missing as u32);

    for _ in 0..iters {
        let mut peek_mask = 1;
        let changed: String = damaged
            .chars()
            .into_iter()
            .map(|char| {
                let mut rv = char;
                if char == '?' {
                    rv = if char_mask & peek_mask == peek_mask {
                        '#'
                    } else {
                        '.'
                    };
                    peek_mask *= 2;
                }
                return rv;
            })
            .collect();
        if check_if_comb_valid(&changed, correct) == true {
            count += 1;
        }

        char_mask += 1;
    }

    println!("Found {count} valid combinations for {damaged}");

    return count;
}

fn part_one(reader: &mut BufReader<File>) -> u32 {
    let mut parsed: Vec<(String, String)> = Vec::new();

    reader.lines().map(|line| line.unwrap()).for_each(|line| {
        let split: Vec<&str> = line.split(" ").collect();
        let rv: (String, String) = (split[0].to_owned(), split[1].to_owned());
        parsed.push(rv);
    });

    let sum = parsed
        .iter()
        .map(|el| {
            let correct: Vec<u32> = el.1.split(",").map(|x| x.parse::<u32>().unwrap()).collect();
            return find_combinations(el.0.clone(), &correct);
        })
        .sum::<u32>();

    return sum;
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let sum = part_one(&mut reader);
    println!("Sum (part one): {sum}")
}
