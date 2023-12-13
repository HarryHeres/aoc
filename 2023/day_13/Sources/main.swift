import Foundation

func parse_maps(contents: [String.SubSequence]) -> [[String]] {
    var parsed: [[String]] = [[String]]()
    var curr: [String] = [String]()
    
    contents.forEach({(line: String.SubSequence) -> Void in 
        if line.count == 1 {
            parsed.append(curr)
            curr = [String]()
        }
        else{
            curr.append(line.replacingOccurrences(of: ";", with: ""))
        }

    })

    return parsed
}

func transpose_map(map: [String]) -> [String] {
    var transposed: [String] = [String]()

    for colIdx in 0..<map[0].count {
        var nextRow: String = String()
        for rowIdx in 0..<map.count {
            let currLine = map[rowIdx]
            let j: String.Index = currLine.index(currLine.startIndex, offsetBy: currLine.count - 1 - colIdx)
            let char: Character = map[rowIdx][j]
            nextRow.append(char)
        }
        transposed.append(nextRow)
    }

    return transposed
}

func find_reflection(previous_reflection: Int, map: [String], transposed: Bool) -> UInt32 {
    var rv: UInt32 = 0
    let lineLen = map[0].count
  
    outer: for j in 1..<lineLen {
        // print("Separator between \(j) and \(j + 1)")
        for i in 0..<map.count { 
            let currLine = map[i]
            let separatorIdx = currLine.index(currLine.startIndex, offsetBy: j)
            for k in 1...min(j, lineLen - j){ 
                let leftIdx = currLine.index(separatorIdx, offsetBy: -k)
                let rightIdx = currLine.index(separatorIdx, offsetBy: k - 1)
                if (currLine[leftIdx] != currLine[rightIdx]){
                    // print("Difference at line \(i + 1): [\(currLine[leftIdx]);\(j - k)] != [\(currLine[rightIdx]);\(j + k - 1)]")
                    continue outer
                }
            } 
       }
        
        // print("Found reflection between \(j) and \(j + 1)")
        if previous_reflection == -1 {
            rv = UInt32(j)
            break
        }
        else {
            let temp = transposed == true ? j * 100 : j
            if temp != previous_reflection { // Found a different solution, no need to continue
                // print("Prev: \(previous_reflection) => New: \(j)")
                rv = UInt32(j)
                break
            }
            else {
                continue // Found previous solution, continue to find another one
            }
        }
    }
    
    return transposed == true ? rv * 100 : rv
}

func part_one(maps: [[String]]) -> [UInt32] {
    var differences: [UInt32] = [UInt32]() 
    
    for i in 0..<maps.count {
        let map = maps[i]
        var curr = find_reflection(previous_reflection: -1, map: map, transposed: false) 
        if curr == 0 { // No reflection found between columns, transpose and try again for rows
            let transposed = transpose_map(map: map)
            curr = find_reflection(previous_reflection: -1, map: transposed, transposed: true) 
        }

        if curr == 0 {
            // print("No reflection found for map \(i+1)")
        }
        
        // print("Score for map \(i + 1): \(curr)")
        differences.append(curr)
    }

    return differences 
}
 
func switch_char_in_map(map: inout [String], idx: Int) -> Void {
    let rowIdx = idx / map[0].count 
    let colIdx = idx % map[0].count
    let sIdx = map[rowIdx].index(map[rowIdx].startIndex, offsetBy: colIdx)

    let newChar = map[rowIdx][sIdx] == "#" ? "." : "#"
    map[rowIdx] = map[rowIdx].replacingCharacters(in: sIdx...sIdx, with: newChar)
}

func part_two(prev: inout [UInt32], maps: [[String]]) -> UInt32 {
    var sum: UInt32 = 0 
    let mapsCount = maps.count

    outer: for i in 0..<mapsCount {
        let map: [String] = maps[i]
        let lineLen = map[0].count
        for j in 0..<map.count * lineLen {
            var map_copy = map
            switch_char_in_map(map: &map_copy, idx: j) 
            var curr = find_reflection(previous_reflection: Int(prev[i]), map: map_copy, transposed: false) 
            if curr == 0 { // No reflection found between columns, transpose and try again for rows
                let transposed = transpose_map(map: map_copy)
                curr = find_reflection(previous_reflection: Int(prev[i]) , map: transposed, transposed: true) 
            }
            
            if curr == 0 {
                if j < map.count * lineLen - 1 {
                    // print("No reflection found for map \(i+1)")
                    continue
                }

                curr = prev[i]
            }
            
            print("Score for map \(i + 1): \(curr)")
            sum += curr
            continue outer
        }

        
    }
        
    return sum
}

func main(){
    let file: String = "input.txt"
    let contents: [String.SubSequence] = try! String(contentsOfFile: file).replacingOccurrences(of: "\n", with: ";\n").split(separator: "\n")

    let maps: [[String]] = parse_maps(contents: contents)
    print("Parsed \(maps.count) maps")

    var prev = part_one(maps: maps)   
    var sum: UInt32 = prev.reduce(0, +)
    print("Sum (part one): \(sum)") // 34100

    sum = part_two(prev: &prev, maps: maps)
    print("Sum (part two): \(sum)") // 33106
}

main()
