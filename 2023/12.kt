import java.io.File

fun f(s: String, a: List<Int>): Long {
    val len = s.length
    val pDots = s.scan(0) { x, c -> x + (if (c == '.') 1 else 0) }
    fun fits(l: Int, r: Int) = r < len && pDots[l] == pDots[r] && s[r] != '#'
    val dp = LongArray(len + 1) { 0 }
    dp[0] = 1
    for (i in 1..len) {
        if (s[i - 1] != '#') {
            dp[i] += dp[i - 1]
        }
    }
    a.forEach { x ->
        for (i in len - x - 1 downTo 0) {
            if (fits(i, i + x)) {
                dp[i + x + 1] = dp[i]
            } else {
                dp[i + x + 1] = 0
            }
        }
        for (i in 0..x) {
            dp[i] = 0
        }
        for (i in 1..len) {
            if (s[i - 1] != '#') {
                dp[i] += dp[i - 1]
            }
        }
    }
    return dp.last()
}

fun solveEasy(lines: List<String>): Long {
    val sas = lines.map { line ->
        val s = line.split(' ').first() + '.'
        val a = line.split(' ').last().split(',').map(String::toInt)
        s to a
    }
    return sas.sumOf { (s, a) -> f(s, a) }
}

fun solveHard(lines: List<String>): Long {
    val sas = lines.map { line ->
        val s = line.split(' ').first()
        val a = line.split(' ').last().split(',').map(String::toInt)
        (List(5) { s }.joinToString("?") + '.') to List(5) { a }.flatten()
    }
    return sas.sumOf { (s, a) -> f(s, a) }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
