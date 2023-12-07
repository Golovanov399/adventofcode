import java.io.File

fun handType(hand: String) = hand.groupBy { it }.values.map { it.size }.sorted().reversed()
fun handTypeWithJoker(hand: String): List<Int> {
    val res = hand.filter { it != 'J' }.groupBy { it }.values.map { it.size }.sorted().reversed().toMutableList()
    if (res.isEmpty()) {
        res.add(hand.length)
    } else {
        res[0] += hand.count { it == 'J' }
    }
    return res
}

fun lexSmaller(a: List<Int>, b: List<Int>): Boolean {
    return when (val i = (0..a.size).first { i -> i >= a.size || i >= b.size || a[i] != b[i] }) {
        a.size -> {
            true
        }
        b.size -> {
            false
        }
        else -> {
            a[i] < b[i]
        }
    }
}

fun cardIndex(c: Char) = if (c.isDigit()) {
    c.digitToInt()
} else {
    mapOf('T' to 10, 'J' to 11, 'Q' to 12, 'K' to 13, 'A' to 14)[c]!!
}

fun cardIndexWithJoker(c: Char) = if (c.isDigit()) {
    c.digitToInt()
} else {
    mapOf('T' to 10, 'J' to 1, 'Q' to 12, 'K' to 13, 'A' to 14)[c]!!
}

fun compareHands(a: String, b: String): Int {
    val typeA = handType(a)
    val typeB = handType(b)
    if (typeA != typeB) {
        return if (lexSmaller(typeB, typeA)) -1 else 1
    }
    return if (lexSmaller(b.map { cardIndex(it) }, a.map { cardIndex(it) })) -1 else 1
}

fun compareHandsWithJoker(a: String, b: String): Int {
    val typeA = handTypeWithJoker(a)
    val typeB = handTypeWithJoker(b)
    if (typeA != typeB) {
        return if (lexSmaller(typeB, typeA)) -1 else 1
    }
    return if (lexSmaller(b.map { cardIndexWithJoker(it) }, a.map { cardIndexWithJoker(it) })) -1 else 1
}

fun solveEasy(lines: List<String>): Long {
    return lines
        .map { it.split(' ') }
        .sortedWith { x, y -> compareHands(x[0], y[0]) }
        .reversed()
        .withIndex()
        .map { (index, value) -> (index + 1) * value[1].toLong() }
        .sum()
}

fun solveHard(lines: List<String>): Long {
    return lines
        .map { it.split(' ') }
        .sortedWith { x, y -> compareHandsWithJoker(x[0], y[0]) }
        .reversed()
        .withIndex()
        .map { (index, value) -> (index + 1) * value[1].toLong() }
        .sum()
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
