import java.io.File

fun sumBetween(a: List<Int>, k: Int = 2): Long {
    var ans = 0L
    var s = 0L
    var off = 0L
    for (i in a.indices) {
        if (i > 0 && a[i] != a[i - 1]) {
            off += (k - 1).toLong() * (a[i] - a[i - 1] - 1)
        }
        ans += (a[i] + off) * i - s
        s += a[i] + off
    }
    return ans
}

fun solveEasy(lines: List<String>): Long {
    val xs = lines.indices.map { i -> List(lines[i].count { it == '#' }) { i } }.flatten()
    val ys = lines[0].indices.map { j -> List(lines.indices.count { i -> lines[i][j] == '#' }) { j } }.flatten()
    return sumBetween(xs) + sumBetween(ys)
}

fun solveHard(lines: List<String>): Long {
    val xs = lines.indices.map { i -> List(lines[i].count { it == '#' }) { i } }.flatten()
    val ys = lines[0].indices.map { j -> List(lines.indices.count { i -> lines[i][j] == '#' }) { j } }.flatten()
    return sumBetween(xs, 1000000) + sumBetween(ys, 1000000)
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
