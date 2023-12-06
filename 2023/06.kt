import java.io.File

fun countWays(time: Long, distance: Long): Long {
    // k * (time - k) > distance
    var (l, r) = (0L to time / 2)
    if (time - r <= distance / r) {
        return 0
    }
    while (r > l + 1) {
        val m = (l + r) / 2
        if (time - m <= distance / m) {
            l = m
        } else {
            r = m
        }
    }
    return (time - r) - r + 1
}

fun solveEasy(lines: List<String>): Long {
    val (times, distances) = lines.map { line -> line.split(' ').filter { it.isNotEmpty() }.drop(1).map(String::toLong) }
    val res = times.zip(distances).map { (time, distance) -> countWays(time, distance) }
    return res.reduce(Long::times)
}

fun solveHard(lines: List<String>): Long {
    val (time, distance) = lines.map { line -> line.split(' ').drop(1).joinToString("").toLong() }
    return countWays(time, distance)
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
