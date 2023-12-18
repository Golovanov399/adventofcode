import java.io.File

fun expandedArea(instructions: List<Pair<Char, Int>>): Long {
    var (x, y) = 0 to 0
    var area = 0L
    for ((dir, d) in instructions) {
        when (dir) {
            'L' -> {
                area -= 1L * y * d
                x -= d
            }
            'R' -> {
                area += 1L * y * d
                x += d
            }
            'U' -> y += d
            'D' -> y -= d
        }
    }
    if (area < 0) {
        area = -area
    }
    val per = instructions.sumOf { it.second }
    return area + per / 2 + 1
}

fun solveEasy(lines: List<String>): Long {
    return expandedArea(lines.map { line ->
        val data = line.split(' ')
        data[0].single() to data[1].toInt()
    })
}

fun Char.hexCharToInt() = if (this in '0'..'9') this.digitToInt() else (this.lowercaseChar().hashCode() - 'a'.hashCode() + 10)
fun String.hexToInt() = this.fold(0) { x, c -> x * 16 + c.hexCharToInt() }

fun solveHard(lines: List<String>): Long {
    return expandedArea(lines.map { line ->
        val info = line.split(' ')[2].slice( 2 until 8)
        "RDLU"[info[5].digitToInt()] to info.take(5).hexToInt()
    })
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
