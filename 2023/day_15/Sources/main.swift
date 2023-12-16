import Foundation

struct Lens {
    let label: String
    var focalLen : UInt32
}

struct Box {
    var lenses: [Lens]  


    mutating func removeLens(toRemove: Int) {
        lenses.remove(at: toRemove)
    }

    mutating func addLens(toAdd: Lens){
        lenses.append(toAdd)
    }
}


func partTwo(strings: [String.SubSequence]) -> UInt64 {
    var sum: UInt64 = 0
    var boxList: [Box] = [Box](repeating: Box(lenses: [Lens]()), count: 256)

    for tmp in strings {
        let opIdx: String.Index = tmp.firstIndex(where: {(el) -> Bool in el == "=" || el == "-"})!

        let label: String = String(tmp[..<opIdx])
        let op: Character = tmp[opIdx] 




        let boxId = Int(hash(string: label))
        var currBox = boxList[boxId]
        switch(op){
            case "-": 
                let found = currBox.lenses.firstIndex(where: {(lens) -> Bool in lens.label == label})
                if found == nil {
                    continue
                }
                
                currBox.removeLens(toRemove: found!)
                boxList[boxId] = currBox
                
            case "=": 
                let focalLenIdx: String.Index = tmp.index(after: opIdx)
                let focalLen: UInt32 = UInt32(String(tmp[focalLenIdx]))!

                let found = currBox.lenses.firstIndex(where: {(lens) -> Bool in lens.label == label})
                if found == nil {
                    currBox.addLens(toAdd: Lens(label: label, focalLen: focalLen))
                }
                else {
                    currBox.lenses[found!].focalLen = focalLen
                }

                boxList[boxId] = currBox
                
            default: continue
        }
    }

    for i in 0..<boxList.count {
        let currBox: Box = boxList[i]
        let currLenses: [Lens] = currBox.lenses

        if currLenses.isEmpty {
            continue
        }
        
        for j in 0..<currLenses.count {
            let currLens: Lens = currLenses[j]
            let focalLen: UInt32 = currLens.focalLen

            sum += UInt64(i + 1) * UInt64(j + 1) * UInt64(focalLen)
        }

    }
    
    return sum
}




func hash(string: String) -> UInt32{
    var sum: UInt32 = 0
    for i in 0..<string.count {
        let idx = string.index(string.startIndex, offsetBy: i)
        let curr_char_ascii = UInt32(string[idx].asciiValue!)

        if curr_char_ascii == Character("\n").asciiValue! {
            continue
        }

        sum = ((sum + curr_char_ascii) * 17) % 256
    }

    return sum
}


func partOne(strings: [String.SubSequence]) -> UInt32{
    var sum: UInt32 = 0
    for str in strings {
        sum += hash(string: String(str)) 
    }

    return sum
}


func main() {
    let file: String = "input.txt"
    let contents: [String.SubSequence] = try! String(contentsOfFile: file).split(separator: ",")
    
    let sum: UInt32 = partOne(strings: contents)
    print("Sum (part one): \(sum)")

    let sum2: UInt64 = partTwo(strings: contents)
    print("Sum (part two): \(sum2)")

}

main()

