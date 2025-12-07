from math import prod

input = [l.strip("\n") for l in open("data/input.txt", "r", encoding="utf-8").readlines()]


def do_op(array, op): return prod(array) if op == "*" else sum(array)
def transpose(array): return [list(a) for a in zip(*array)]


ops = input[-1].split()
input = input[:-1]

grid_lr = transpose([[int(i) for i in row.split()] for row in input])
grid_rl = transpose([list(row)[::-1] for row in input])
grid_rl = [
    [int(n) for n in i.split()]
    for i in " ".join(["".join(a).strip() for a in grid_rl]).split("  ")
]

part1 = sum([do_op(num, op) for num, op in zip(grid_lr, ops)])
part2 = sum([do_op(num, op) for num, op in zip(grid_rl, ops[::-1])])

print(f"Part 1: {part1}")
print(f"Part 2: {part2}")
