import java.io.File

val dirs = listOf(-1 to 0, 1 to 0, 0 to -1, 0 to 1)
val pipes = mapOf(
    '|' to 0b0011,
    '-' to 0b1100,
    'L' to 0b1001,
    'F' to 0b1010,
    '7' to 0b0110,
    'J' to 0b0101,
)

fun findLoop(lines: List<String>): List<Pair<Int, Int>> {
    val startX = lines.indexOfFirst { 'S' in it }
    val startY = lines[startX].indexOf('S')

    for (firstDir in dirs.indices) {
        val loop = mutableListOf<Pair<Int, Int>>()
        var (x, y) = startX to startY
        var d = firstDir
        while (true) {
            loop.add(x to y)
            x += dirs[d].first
            y += dirs[d].second
            if (x !in lines.indices || y !in lines[x].indices) {
                break
            }
            if (lines[x][y] !in pipes) {
                break
            }
            d = pipes[lines[x][y]]!! xor (1 shl (d xor 1))
            if (d.countOneBits() != 1) {
                break
            }
            d = d.countTrailingZeroBits()
        }
        if (x in lines.indices && y in lines[x].indices && lines[x][y] == 'S') {
            return loop
        }
    }
    check(false)
    return listOf()
}

fun solveEasy(lines: List<String>): Int {
    return findLoop(lines).size / 2
}

fun solveHard(lines: List<String>): Int {
    val loop = findLoop(lines)
    var area = 0
    var last = loop.last()
    loop.forEach { (x, y) ->
        if (x != last.first) {
            area += y * (x - last.first)
        }
        last = x to y
    }
    if (area < 0) {
        area = -area
    }
    return area + 1 - loop.size / 2
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
