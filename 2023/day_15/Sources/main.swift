import Foundation


func part_one(strings: [String.SubSequence]) -> UInt32{
    var sum: UInt32 = 0
    for str in strings {
        var tmp_sum: UInt32 = 0
        for i in 0..<str.count {
            let idx = str.index(str.startIndex, offsetBy: i)
            let curr_char_ascii = UInt32(str[idx].asciiValue!)

            if curr_char_ascii == Character("\n").asciiValue! {
                continue
            }

            tmp_sum = ((tmp_sum + curr_char_ascii) * 17) % 256
        }
        sum += tmp_sum
    }

    return sum
}


func main() {
    let file: String = "input.txt"
    let contents: [String.SubSequence] = try! String(contentsOfFile: file).split(separator: ",")
    
    let sum: UInt32 = part_one(strings: contents)
    print("Sum (part one): \(sum)")

}

main()

