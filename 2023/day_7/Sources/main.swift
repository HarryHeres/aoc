import Foundation

/*let CARD_VALUES: [Character: Int] = [
    "A":14, 
    "K":13, 
    "Q":12, 
    "J":11, 
    "T":10, 
    "9":9,
    "8":8, 
    "7":7, 
    "6":6, 
    "5":5, 
    "4":4, 
    "3":3, 
    "2":2, 
]*/

let CARD_VALUES: [Character: Int] = [
    "A":14, 
    "K":13, 
    "Q":12, 
    "T":10, 
    "9":9,
    "8":8, 
    "7":7, 
    "6":6, 
    "5":5, 
    "4":4, 
    "3":3, 
    "2":2, 
    "J":1, 
]


struct Hand {
    var cards: String
    var cards_value: Int
    var bid: Int
}

class Node<Hand> {
    var value: Hand
    var next: Node<Hand>?

    init(value: Hand, next: Node<Hand>? = nil) {
        self.value = value
        self.next = next
    }
}

class SortedLinkedList{
    var head: Node<Hand>?
    var len: Int = 0 

    init() {} 

    private func insert_after(node: inout Node<Hand>, newNode: Node<Hand>) -> Void {
        let tmp = Node<Hand>(value: node.value, next: node.next)
        node.next = newNode
        newNode.next = tmp.next
    }

    private func insert_before(node: inout Node<Hand>, newNode: Node<Hand>) -> Void {
        let nodeCopy = Node<Hand>(value: node.value, next: node.next)

        if (node.value.cards == head!.value.cards && node.value.bid == head!.value.bid) {
            head = newNode
            newNode.next = nodeCopy
            return
        }

        // print("Old node: \(node.value.cards) | Next: \(node.next?.value.cards)")
        node = newNode
        newNode.next = nodeCopy
        // print("New node: \(node.value.cards) | Next: \(node.next?.value.cards)")
    }

    public func getHead() -> Node<Hand>? {
        return head
    }

    public func insert(newNode: Node<Hand>) -> Void {
        if head == nil {
            head = newNode 
        }

        else {
            var node: Node<Hand> = head!
            var prev_node: Node<Hand>? = nil
            while true {
                if newNode.value.cards_value > node.value.cards_value{
                    insert_before(node: &node, newNode: newNode)
                    prev_node?.next = newNode
                    break
                }

                if newNode.value.cards_value == node.value.cards_value {
                    let newCards = newNode.value.cards
                    let currCards = node.value.cards
                    var isNewBigger: Bool = false
                    for i in 0..<newNode.value.cards.count {
                        let idx = newCards.index(_ : newCards.startIndex, offsetBy: i)
                        let newChar = newCards[idx]
                        let currChar = currCards[idx]
                        
                        if newChar == currChar{
                            continue                            
                        }

                        isNewBigger = CARD_VALUES[newChar]! > CARD_VALUES[currChar]!
                        break
                        
                    }

                    if isNewBigger == true {
                        insert_before(node: &node, newNode: newNode)
                        prev_node?.next = newNode
                        break
                    }
                }

                if(node.next == nil) {
                    node.next = newNode
                    break
                } 

                prev_node = node
                node = node.next!
            }
        }

        self.len += 1
    }

    func printSelf() -> Void {
        print("List: (\(self.len)): ", terminator: "")
        var node: Node<Hand>? = self.head!
        for _ in 0..<self.len {
            print("\(node!.value.cards)", terminator: "->")
            node = node!.next
        }
        print("nil")
    }
}

func calculateHandValue(cards: String) -> Int {
    var highestValue: Int = 0
    let JOKER_REPLACEMENT = ["A", "K", "Q", "T", "9", "8", "7", "6", "5", "4", "3", "2"]
    for i in 0..<JOKER_REPLACEMENT.count{
        let cardsCopy = cards.replacingOccurrences(of: "J", with: JOKER_REPLACEMENT[i])
        
        var counts: [String: Int] = [String: Int]()
        
        

        for i in 0..<cardsCopy.count {
            let idx: String.Index = cardsCopy.index(_ :cardsCopy.startIndex, offsetBy: i)
            let card: String = String(cardsCopy[idx])
            
            counts[card] = counts[card] == nil ? 1 : counts[card]! + 1
        }

        // Unique cardsCopy
        var value: Int = 0
        switch counts.count {
            case 1: value = 7 
            case 2: 
                // Full House or Four of a kind
                for i in 0..<cardsCopy.count{
                    let idx = cardsCopy.index(_ :cardsCopy.startIndex, offsetBy: i)
                    let val: Int = counts[String(cardsCopy[idx])]!

                    if val == 1 { // Four of a kind
                        value = 6
                        break
                    }
                }
                value = value > 0 ? value : 5
            case 3: 
               // Two pair or Three of a kind
                for i in 0..<cardsCopy.count {
                    let idx = cardsCopy.index(_ :cardsCopy.startIndex, offsetBy: i)
                    let val: Int = counts[String(cardsCopy[idx])]!

                    if val == 3 { // Three of a kind
                        value = 4
                        break
                    }
                }
                value = value > 0 ? value : 3
            case 4: value = 2
            case 5: value = 1
            default: value = 0
        }

    // print("Hand: \(cards) | Poker value: \(value) | Unique cards: \(counts.count)")
        highestValue = value > highestValue ? value : highestValue
    }

    return highestValue
}
/* func calculateHandValuePartOne(cards: String) -> Int {
    var counts: [String: Int] = [String: Int]()

    for i in 0..<cards.count {
        let idx: String.Index = cards.index(_ :cards.startIndex, offsetBy: i)
        let card: String = String(cards[idx])
        
        counts[card] = counts[card] == nil ? 1 : counts[card]! + 1
    }

    // Unique cards
    var value: Int = 0
    switch counts.count {
        case 1: value = 7 
        case 2: 
            // Full House or Four of a kind
            for i in 0..<cards.count{
                let idx = cards.index(_ :cards.startIndex, offsetBy: i)
                let val: Int = counts[String(cards[idx])]!

                if val == 1 { // Four of a kind
                    value = 6
                    break
                }
            }
            value = value > 0 ? value : 5
        case 3: 
           // Two pair or Three of a kind
            for i in 0..<cards.count {
                let idx = cards.index(_ :cards.startIndex, offsetBy: i)
                let val: Int = counts[String(cards[idx])]!

                if val == 3 { // Three of a kind
                    value = 4
                    break
                }
            }
            value = value > 0 ? value : 3
        case 4: value = 2
        case 5: value = 1
        default: value = 0
    }

    // print("Hand: \(cards) | Poker value: \(value) | Unique cards: \(counts.count)")
    return value
}


func part_two(lines: [String.SubSequence]) -> UInt32 {
    var sum: Int = 0


    
    
    return UInt32(sum)
} */

func part_one(lines: [String.SubSequence]) -> UInt32{
    var sum: Int = 0
    let sorted: SortedLinkedList = SortedLinkedList()

    lines.forEach({
        let line = $0
        let pair: [String.SubSequence] = line.split(separator: " ")
        var hand: Hand = Hand(cards: String(pair[0]), cards_value: 0, bid: Int(pair[1])!)
       
        hand.cards_value = calculateHandValue(cards: hand.cards)
        sorted.insert(newNode: Node<Hand>(value: hand))
    })

    // sorted.printSelf()

    
    var node: Node<Hand>? = sorted.getHead()
    for i in 0..<sorted.len {
        // print("Hand \(node!.value.cards) | Rank: \(sorted.len - i) | Bid: \(node!.value.bid)")
        sum += node!.value.bid * (sorted.len - i)
        node = node?.next 
    }
    

    return UInt32(sum)
}

func main() {
    let file: String = "input.txt"
    let contents: String = try! String(contentsOfFile: file)
    let lines: [String.SubSequence] = contents.split(separator: "\n")

    let sum: UInt32 = part_one(lines: lines)
    print("Sum (part two) \(sum)") 


}

func testSortedLinkedList(){
    let list: SortedLinkedList = SortedLinkedList()

    list.insert(newNode: Node<Hand>(value: Hand(cards: "A", cards_value: 1, bid: 1)))
    list.insert(newNode: Node<Hand>(value: Hand(cards: "B", cards_value: 2, bid: 1)))
    list.insert(newNode: Node<Hand>(value: Hand(cards: "CA", cards_value: 4, bid: 1)))
    list.insert(newNode: Node<Hand>(value: Hand(cards: "CK", cards_value: 3, bid: 1)))

    assert(list.len == 4)
    list.printSelf()
}

func test() {
    testSortedLinkedList()
}

// test()
main()
