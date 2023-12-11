import Foundation

struct Galaxy{
    var rowIdx: Int
    var colIdx: Int
}


func findShortestPathFromTo(lines: [String.SubSequence], from: Galaxy, to: Galaxy) -> UInt32 {
    let rowDiff = to.rowIdx - from.rowIdx
    let colDiff = abs(from.colIdx - to.colIdx)

    return UInt32(rowDiff + colDiff)
}


func expandGalaxy(lines: inout [String.SubSequence]) {
    // Parse all empty lines 
    var rowOffset = 0
    for rowIdx in 0..<lines.count {
        let currLine = lines[rowIdx + rowOffset]
         if !currLine.contains("#") {
            print("Found empty row at \(rowIdx)")
            lines.insert(currLine, at: rowIdx + rowOffset)
            rowOffset += 1
        }
     }


    var colEmpty: Bool = true
    var colOffset = 0
    for colIdx in 0..<lines[0].count{
        for rowIdx in 0..<lines.count{
            let currLine = lines[rowIdx]
            let charIdx = currLine.index(currLine.startIndex, offsetBy: Int(colIdx + colOffset))
            let currChar = currLine[charIdx]
            if currChar == "#" {
                colEmpty = false
                break
            }
        }
        if colEmpty == true {
            // print("Found empty collumn at \(colIdx)")
            for i in 0..<lines.count {
                var line = lines[i]
                let insertIdx = line.index(line.startIndex, offsetBy: Int(colIdx + colOffset))
                line.insert(".", at: insertIdx)
                lines[i] = line
            }
            colOffset += 1
        }
        colEmpty = true
    } 

    // lines.forEach({line in print(line, terminator: "\n")})
    print("New row count: \(lines.count)")
    print("New col count: \(lines[0].count)")
}


func partOne(lines: inout [String.SubSequence]) -> UInt32 {
    var sum: UInt32 = 0

    // Expand the galaxy appropriately
    expandGalaxy(lines: &lines)

    // Find all galaxies
    var galaxies: [Galaxy] = [Galaxy]()
    for i in 0..<lines.count {
        let line = lines[i]
        for j in 0..<line.count {
            let currChar = line[line.index(line.startIndex, offsetBy: j)]
            if currChar == "#"{
                galaxies.append(Galaxy(rowIdx: i, colIdx: j))
            }
        }
        
    }

    print("Found \(galaxies.count) galaxies")

    for i in 0..<galaxies.count - 1{
        for j in i + 1..<galaxies.count {
            let pathLen = findShortestPathFromTo(lines: lines, from: galaxies[i], to: galaxies[j])
            print("Path len from \(i) to \(j) is \(pathLen)")
            sum += pathLen
        }
    }

    return sum
}


func main() {
    let file: String = "input.txt";
    var contents: [String.SubSequence] = try! String(contentsOfFile: file).split(separator: "\n")
    
    let sum: UInt32 = partOne(lines: &contents)
    print("Sum (part one): \(sum)")
}

main()
