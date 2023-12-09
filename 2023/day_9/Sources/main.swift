import Foundation


func part_one_and_two(lines: [String]) -> Int64 {
    return lines.map({ (line: String) -> Int64 in
        var nums: [[Int64]] = [[Int64]]()
        nums.append(line.split(separator: " ").map( {(num: String.SubSequence) -> Int64 in Int64(num)! } ))

        // Differences until hitting 0
        var idx = 0
        while true {
            let prev_nums = nums[idx]
            var curr_nums = [Int64]()

            for j in 0..<(prev_nums.count - 1){
                curr_nums.append(prev_nums[j + 1] - prev_nums[j])
            }

            nums.append(curr_nums)
            idx += 1
            if curr_nums.contains(where: {num in return num != 0}) == false {
                break;
            }

        }

        // Now extrapolate the value
        for i in (1..<nums.count).reversed() {
            let curr_nums = nums[i]
            var next_nums = nums[i - 1]
    
            let curr_num = curr_nums[curr_nums.count - 1]
            let next_num = next_nums[next_nums.count - 1]
            next_nums.append(next_num + curr_num)
            nums[i-1] = next_nums
        }
        
        
        let extrapolated = nums[0][nums[0].count - 1]

        return extrapolated
    }).reduce(0, +)
}


func main(){
    let file: String = "input.txt"
    var lines: [String] = try! String(contentsOfFile: file).split(separator: "\n").map({(line: String.SubSequence) -> String in String(line)})

    var sum: Int64 = part_one_and_two(lines: lines)
    print("Sum (part one): \(sum)")
 
    lines = lines.map({ (line: String) -> String in 
        var reversed: String = String()
        line.split(separator: " ").reversed().forEach({element in 
            reversed += element
            reversed += " "
        })
        return reversed
    })

    sum = part_one_and_two(lines: lines)
    print("Sum (part two): \(sum)")

}

main()

