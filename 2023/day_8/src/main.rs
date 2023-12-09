use std::{
    fs::File,
    io::{BufRead, BufReader, Seek, SeekFrom},
};

use bst::BST;

mod bst;

fn lcm_vec(nums: Vec<usize>) -> usize {
    let mut previous = nums[0];
    for i in 1..nums.len() {
        println!("Num: {}", nums[i]);
        previous = lcm(nums[i], previous);
    }

    return previous;
}

fn lcm(first: usize, second: usize) -> usize {
    first * second / gcd(first, second)
}

fn gcd(first: usize, second: usize) -> usize {
    let mut max = first;
    let mut min = second;
    if min > max {
        let val = max;
        max = min;
        min = val;
    }

    loop {
        let res = max % min;
        if res == 0 {
            return min;
        }

        max = min;
        min = res;
    }
}

fn part_two(reader: &mut BufReader<File>) -> usize {
    let mut buffer: String = String::new();
    reader
        .read_line(&mut buffer)
        .expect("Could not read the first line of the file");

    let instructions: Vec<usize> = buffer
        .chars()
        .filter(|char| match char {
            'R' => return true,
            'L' => return true,
            _ => return false,
        })
        .map(|char| match char {
            'R' => return 1,
            'L' => return 0,
            _ => return 2,
        })
        .collect();
    buffer.clear();

    // Empty line
    reader
        .read_line(&mut buffer)
        .expect("Could not read line from input file");
    buffer.clear();

    reader
        .read_line(&mut buffer)
        .expect("Could not read line from input file");

    let split: Vec<&str> = buffer.split(" = ").collect();
    let root: &str = split[0];
    let children: Vec<&str> = split[1][1..(split[1].len() - 2)].split(", ").collect();

    let mut bst = BST::new(root);
    bst.insert_node(root, children[0], 0);
    bst.insert_node(root, children[1], 1);

    reader
        .lines()
        .map(|line| line.unwrap())
        .filter(|line| line.len() > 0)
        .for_each(|line| {
            let split: Vec<&str> = line.split(" = ").collect();
            let node_name: &str = split[0];
            let children: Vec<&str> = split[1][1..(split[1].len() - 1)].split(", ").collect();

            bst.insert_node(node_name, children[0], 0);
            bst.insert_node(node_name, children[1], 1);
        });

    // bst.print();

    println!("Calculating path to all nodes ending with Z...");
    let steps: Vec<usize> = bst.get_path_to_all_ending_with("Z", instructions);

    println!("Calculating the lowest common multiplier...");
    return lcm_vec(steps);
}

fn part_one(reader: &mut BufReader<File>) -> usize {
    let mut buffer: String = String::new();
    reader
        .read_line(&mut buffer)
        .expect("Could not read the first line of the file");

    let instructions: Vec<usize> = buffer
        .chars()
        .filter(|char| match char {
            'R' => return true,
            'L' => return true,
            _ => return false,
        })
        .map(|char| match char {
            'R' => return 1,
            'L' => return 0,
            _ => return 2,
        })
        .collect();
    buffer.clear();

    // Empty line
    reader
        .read_line(&mut buffer)
        .expect("Could not read line from input file");
    buffer.clear();

    reader
        .read_line(&mut buffer)
        .expect("Could not read line from input file");

    let split: Vec<&str> = buffer.split(" = ").collect();
    let root: &str = split[0];
    let children: Vec<&str> = split[1][1..(split[1].len() - 2)].split(", ").collect();

    let mut bst = BST::new(root);
    bst.insert_node(root, children[0], 0);
    bst.insert_node(root, children[1], 1);

    reader
        .lines()
        .map(|line| line.unwrap())
        .filter(|line| line.len() > 0)
        .for_each(|line| {
            let split: Vec<&str> = line.split(" = ").collect();
            let node_name: &str = split[0];
            let children: Vec<&str> = split[1][1..(split[1].len() - 1)].split(", ").collect();

            bst.insert_node(node_name, children[0], 0);
            bst.insert_node(node_name, children[1], 1);
        });

    // bst.print();

    println!("Calculating path to ZZZ...");
    return bst.get_path_to("ZZZ", instructions);
}

fn main() {
    let file: File = File::open("input.txt").expect("Could not open the input file");
    let mut reader: BufReader<File> = BufReader::new(file);

    let mut steps = part_one(&mut reader);
    println!("Number of steps: {steps}");

    reader
        .seek(SeekFrom::Start(0))
        .expect("Could not seek to the beginning of the input file");

    steps = part_two(&mut reader);
    println!("Number of steps (part two): {steps}");
}
