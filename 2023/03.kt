import java.io.File

data class Seg(val row: Int, val from: Int, val to: Int)

fun getNumbers(lines: List<String>): List<Seg> {
    val res = mutableListOf<Seg>()
    lines.withIndex().forEach { (idx, line) ->
        val digitIndices = line.indices.filter { line[it].isDigit() }
        var i = 0
        while (i < digitIndices.size) {
            var j = i + 1
            while (j < digitIndices.size && digitIndices[j] == digitIndices[j - 1] + 1) {
                j += 1
            }
            res.add(Seg(idx, digitIndices[i], digitIndices[j - 1]))
            i = j
        }
    }
    return res
}

fun solveEasy(lines: List<String>): Int {
    val (n, m) = lines.size to lines[0].length

    fun isOk(s: Seg): Boolean {
        return (s.row-1..s.row+1).intersect(0 until n).sumOf { i ->
            (s.from-1..s.to+1).intersect(0 until m).count { j -> lines[i][j] != '.' }
        } > s.to - s.from + 1
    }
    fun toNum(s: Seg) = lines[s.row].substring(s.from..s.to).toInt()

    return getNumbers(lines).filter { isOk(it) }.sumOf { toNum(it) }
}

fun solveHard(lines: List<String>): Long {
    val (n, m) = lines.size to lines[0].length
    val neighbors = List(n) { List(m) { mutableListOf<Seg>() } }
    val segs = getNumbers(lines)
    segs.forEach { seg ->
        (seg.row - 1..seg.row + 1).intersect(0 until n).forEach { i ->
            (seg.from - 1..seg.to + 1).intersect(0 until m).forEach { j ->
                neighbors[i][j].add(seg)
            }
        }
    }
    fun toNum(s: Seg) = lines[s.row].substring(s.from..s.to).toLong()

    return (0 until n).sumOf { i ->
        (0 until m).filter { j -> lines[i][j] == '*' && neighbors[i][j].size == 2 }.sumOf { j -> neighbors[i][j].map { toNum(it) }.reduce(Long::times) }
    }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}