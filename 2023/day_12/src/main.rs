use std::{
    fs::File,
    io::{BufRead, BufReader, Seek, SeekFrom},
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

// NOTE: Tried to find a mathematical solution but did not find (but was very close, though)
// Best would probably be DP and recursion with memoize, but not enough time to implement that.
// Might get back to it later.
// Brute force worked for part one, too long for part two
fn find_unfolded_combinations(damaged: &String, correct: &Vec<u32>) -> u64 {
    let mut sum = 0;

    let unfolded: String = damaged.clone() + "?";
    let x = find_combinations(damaged, correct);
    let y = find_combinations(&unfolded, correct);
    sum = x * y.pow(4);

    // match (
    //     damaged.chars().nth(0).unwrap(),
    //     damaged.chars().last().unwrap(),
    // ) {
    //     ('?', '?') => {
    //         let unfolded: String = (damaged.clone() + "?").to_string();

    //         let x = find_combinations(damaged, correct);
    //         let y = find_combinations(&unfolded, correct);
    //         sum = x * y.pow(4);
    //     }
    //     (_, '?') => {
    //         let unfolded: String = ("?".to_string() + damaged.clone().as_str()).to_string();

    //         let x = find_combinations(damaged, correct);
    //         let y = find_combinations(&unfolded, correct);
    //         sum = x * y.pow(4);
    //     }
    //     ('?', _) => {
    //         let a = find_combinations(damaged, correct);

    //         let mut unfolded: String = damaged.clone() + "?";
    //         let b = find_combinations(&unfolded, correct);

    //         unfolded = "?".to_string() + damaged.clone().as_str();
    //         let c = find_combinations(&unfolded, correct);

    //         unfolded = "?".to_string() + unfolded.as_str();
    //         let d = find_combinations(&unfolded, correct);

    //         sum = a.pow(1) * b.pow(1) * c.pow(2) * d.pow(1); // 1 1 2 1
    //         println!("{sum}")
    //     }
    //     (_, _) => {
    //         let unfolded: String = ("?".to_string() + damaged.clone().as_str()).to_string();

    //         let x = find_combinations(damaged, correct);
    //         let y = find_combinations(&unfolded, correct);
    //         sum = x * y.pow(4);
    //     }
    // }

    return sum;
}

// Works flawlessly for part one
fn find_combinations(damaged: &String, correct: &Vec<u32>) -> u64 {
    let mut count = 0;

    let missing = damaged
        .chars()
        .into_iter()
        .filter(|char| char.eq(&'?'))
        .count();

    let mut char_mask: u32 = 0;
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
                    rv = if char_mask & peek_mask > 0 { '#' } else { '.' };
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

    // println!("Found {count} valid combinations for {damaged}");

    return count;
}

// Unfolding part two - for greedy solution
// fn unfold_line(line: &mut String, correct: &mut String) {
//     let unfold_count = 4;

//     let copy = line.clone();
//     for _ in 0..unfold_count {
//         line.push('?');
//         line.push_str(copy.as_str());
//     }

//     let copy = correct.clone();
//     for _ in 0..unfold_count {
//         correct.push(',');
//         correct.push_str(copy.as_str());
//     }
// }

fn part_two(reader: &mut BufReader<File>) -> u64 {
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
            return find_unfolded_combinations(&el.0, &correct);
        })
        .sum::<u64>();

    return sum;
}

// Basically brute-force for part one
fn part_one(reader: &mut BufReader<File>) -> u64 {
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
            return find_combinations(&el.0.clone(), &correct);
        })
        .sum::<u64>();

    return sum;
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let sum = part_one(&mut reader);
    println!("Sum (part one): {sum}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the file");

    let sum = part_two(&mut reader);
    println!("Sum (part two): {sum}");
}
