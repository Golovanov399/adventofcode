import java.io.File
import java.util.*

val dirs = listOf(-1 to 0, 0 to -1, 1 to 0, 0 to 1)

data class Entry(val value: Int, val x: Int, val y: Int, val d: Int) : Comparable<Entry> {
    override operator fun compareTo(e: Entry): Int {
        if (value != e.value) {
            return value.compareTo(e.value)
        }
        if (x != e.x) {
            return x.compareTo(e.x)
        }
        if (y != e.y) {
            return y.compareTo(e.y)
        }
        return d.compareTo(e.d)
    }
}

fun solveForSegmentRange(lines: List<String>, minSeg: Int, maxSeg: Int): Int {
    val (n, m) = lines.size to lines[0].length
    val dp = List(n) { List(m) { IntArray(4) { Int.MAX_VALUE / 2 } } }
    dp[0][0][0] = 0
    dp[0][0][1] = 0
    val ts = TreeSet<Entry>()
    ts.add(Entry(0, 0, 0, 0))
    ts.add(Entry(0, 0, 0, 1))
    while (ts.isNotEmpty()) {
        val e = ts.first()
        ts.remove(e)
        if (dp[e.x][e.y][e.d] != e.value) {
            continue
        }
        for (d in 0 until 4) {
            if (d % 2 == e.d % 2) {
                continue
            }
            var cur = e.value
            var (x, y) = e.x to e.y
            for (it in 0 until maxSeg) {
                x += dirs[d].first
                y += dirs[d].second
                if (x !in 0 until n || y !in 0 until m) {
                    break
                }
                cur += lines[x][y].digitToInt()
                if (it + 1 >= minSeg && dp[x][y][d] > cur) {
                    dp[x][y][d] = cur
                    ts.add(Entry(cur, x, y, d))
                }
            }
        }
    }
    return dp[n - 1][m - 1].minOrNull()!!
}

fun solveEasy(lines: List<String>): Int {
    return solveForSegmentRange(lines, 1, 3)
}

fun solveHard(lines: List<String>): Int {
    return solveForSegmentRange(lines, 4, 10)
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
