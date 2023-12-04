import java.io.File

fun matchingSum(good: List<String>, have: List<String>): Int {
    val sz = good.toSet().intersect(have).size
//    println("$good, $have -- $sz")
    return if (sz > 0) (1 shl (sz - 1)) else 0
}

fun solveEasy(lines: List<String>): Int {
    return lines.sumOf { line ->
        val parts = line.split(": ")[1].split(" | ").map { it.split(' ').filter { s -> s.isNotEmpty() } }
        matchingSum(parts[0], parts[1])
    }
}

fun solveHard(lines: List<String>): Long {
    val cnt = LongArray(lines.size) { 1 }
    for (i in lines.indices) {
        val parts = lines[i].split(": ")[1].split(" | ").map { it.split(' ').filter { s -> s.isNotEmpty() } }
        val sz = parts[0].toSet().intersect(parts[1]).size
        for (j in i+1..i+sz) {
            cnt[j] += cnt[i]
        }
    }
    return cnt.sum()
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}