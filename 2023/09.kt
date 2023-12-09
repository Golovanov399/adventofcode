import java.io.File

fun f(a: List<Long>): Long {
    return if (a.all { it == 0L }) {
        0
    } else {
        a.last() + f(a.zipWithNext().map { (x, y) -> y - x })
    }
}

fun solveEasy(lines: List<String>): Long {
    return lines.sumOf { line ->
        f(line.split(' ').map(String::toLong))
    }
}

fun solveHard(lines: List<String>): Long {
    return lines.sumOf { line ->
        f(line.split(' ').map(String::toLong).reversed())
    }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
