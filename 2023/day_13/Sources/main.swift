import Foundation

func transpose_map(map: [String]) -> [String] {
    var transposed: [String] = [String]()

    for colIdx in 0..<map[0].count {
        var nextRow: String = String()
        for rowIdx in 0..<map.count {
            let currLine = map[rowIdx]
            let j: String.Index = currLine.index(currLine.startIndex, offsetBy: colIdx)
            let char: Character = map[rowIdx][j]
            nextRow.append(char)
        }
        transposed.append(nextRow)
    }

    return transposed
}

func find_reflection(map: [String]) -> UInt32 {
    var rv: UInt32 = 0 
    let lineLen = map[0].count
  
    outer: for j in (lineLen / 2)..<lineLen - 1 {
        for i in 0..<map.count { 
            let currLine = map[i]
            let separatorIdx = currLine.index(currLine.startIndex, offsetBy:j)
            for k in 1...lineLen - j{ // Just need to check only from half the line
                // Check if the right half is reflected properly
                let leftIdx = currLine.index(separatorIdx, offsetBy: -k)
                let rightIdx = currLine.index(separatorIdx, offsetBy: k)
                if (currLine[leftIdx] != currLine[rightIdx]){
                    continue outer
                }
            } 
        }

        // Found a reflection
        rv = UInt32(lineLen - j);        
        print("Found reflection between columns \(j) and \(j + 1)")
    }

    return rv
}


func part_one(maps: [[String]]) -> UInt32 {
    var sum: UInt32 = 0 
    
    for map in maps {
        var curr = find_reflection(map: map)     
        if curr == 0 { // No reflection found between columns, transpose and try again for rows
            let transposed = transpose_map(map: map)
            curr = find_reflection(map: transposed) * 100
        }

        sum += curr
    }

    return sum
}

func parse_maps(contents: [String.SubSequence]) -> [[String]] {
    var parsed: [[String]] = [[String]]()
    var curr: [String] = [String]()
    
    contents.forEach({(line: String.SubSequence) -> Void in 
        if line.count == 1 {
            parsed.append(curr)
            curr = [String]()
        }
        curr.append(String(line))
    })

    return parsed
}


func main(){
    let file: String = "input_example.txt"
    let contents: [String.SubSequence] = try! String(contentsOfFile: file).split(separator: "\n") 
    let maps: [[String]] = parse_maps(contents: contents)

    let sum: UInt32 = part_one(maps: maps)
    print("Sum (part one): \(sum)")
}

main()
