use std::collections::VecDeque;

struct BSTNode {
    name: String,
    left: usize,
    right: usize,
}

pub struct BST {
    nodes: Vec<BSTNode>,
}

impl BSTNode {
    pub fn new(name: &str) -> Self {
        return Self {
            name: String::from(name),
            left: usize::MAX,
            right: usize::MAX,
        };
    }
}

impl BST {
    pub fn new(root_name: &str) -> Self {
        let mut nodes: Vec<BSTNode> = Vec::new();
        nodes.push(BSTNode::new(root_name));

        return Self { nodes };
    }

    fn find_node(&self, node_name: &str) -> usize {
        for i in 0..self.nodes.len() {
            if node_name == self.nodes[i].name {
                return i;
            }
        }

        return self.nodes.len();
    }

    pub fn insert_node(&mut self, parent_name: &str, new_node_name: &str, pos: u8) {
        let idx: usize = self.find_node(parent_name);
        if idx == self.nodes.len() {
            // Node not present
            self.nodes.push(BSTNode::new(parent_name));
        }

        let child_idx: usize = self.find_node(new_node_name);
        if child_idx == self.nodes.len() {
            self.nodes.push(BSTNode {
                name: String::from(new_node_name),
                left: usize::MAX,
                right: usize::MAX,
            });
        }

        match pos {
            0 => self.nodes[idx].left = child_idx,
            1 => self.nodes[idx].right = child_idx,
            _ => println!("INVALID POSITION!"),
        }
    }

    pub fn get_path_to(&self, node_name: &str, instructions: Vec<usize>) -> usize {
        let mut steps: usize = 0;

        let idx = self.find_node(node_name);
        if idx == self.nodes.len() {
            println!("{node_name} node not found in this BST!");
            return 0;
        }

        let start_idx = self.find_node("AAA");
        if start_idx == self.nodes.len() {
            println!("AAA node not found in this BST!");
            return 0;
        }

        let mut curr_node: &BSTNode = &self.nodes[start_idx];
        loop {
            if curr_node.name == node_name {
                break;
            }

            let pos: usize = instructions[steps % instructions.len()];
            match pos {
                0 => curr_node = &self.nodes[curr_node.left],
                1 => curr_node = &self.nodes[curr_node.right],
                _ => break,
            }
            steps += 1;
        }

        return steps;
    }

    fn get_all_nodes_ending_with(&self, end: &str) -> Vec<usize> {
        let mut node_idxs: Vec<usize> = Vec::new();

        for i in 0..self.nodes.len() {
            let curr_node: &BSTNode = &self.nodes[i];
            if curr_node.name.ends_with(end) {
                node_idxs.push(i);
                println!("{}", curr_node.name);
            }
        }

        return node_idxs;
    }

    pub fn get_path_to_all_ending_with(
        &self,
        node_name: &str,
        instructions: Vec<usize>,
    ) -> Vec<usize> {
        let mut steps: usize = 0;

        let start: Vec<usize> = self.get_all_nodes_ending_with("A");
        let mut steps_vec: Vec<usize> = Vec::with_capacity(start.capacity());

        for i in 0..start.len() {
            let mut curr_node: &BSTNode = &self.nodes[start[i]];
            loop {
                if curr_node.name.ends_with(node_name) {
                    break;
                }

                let pos: usize = instructions[steps % instructions.len()];
                match pos {
                    0 => curr_node = &self.nodes[curr_node.left],
                    1 => curr_node = &self.nodes[curr_node.right],
                    _ => break,
                }
                steps += 1;
            }
            steps_vec.push(steps);
            steps = 0;
        }

        return steps_vec;
    }

    pub fn print(&self) {
        let mut queue: VecDeque<&BSTNode> = VecDeque::with_capacity(self.nodes.len());

        let start_idx = self.find_node("AAA");
        if start_idx == self.nodes.len() {
            println!("AAA node not found in this BST!");
            return;
        }

        queue.push_back(&self.nodes[start_idx]);

        while !queue.is_empty() {
            let curr_node: &BSTNode = queue.pop_front().unwrap();

            print!("Node: {} -> ", curr_node.name);

            match curr_node.left {
                usize::MAX => {
                    print!("nil, ")
                }
                _ => {
                    print!("{}, ", self.nodes[curr_node.left].name);
                    if self.nodes[curr_node.left].name != curr_node.name {
                        queue.push_back(&self.nodes[curr_node.left]);
                    }
                }
            }

            match curr_node.right {
                usize::MAX => {
                    print!("nil")
                }
                _ => {
                    print!("{}", self.nodes[curr_node.right].name);
                    if self.nodes[curr_node.right].name != curr_node.name {
                        queue.push_back(&self.nodes[curr_node.right]);
                    }
                }
            }

            println!();
        }
    }
}
