import java.io.File

fun solveEasy(lines: List<String>): Int {
    return lines.sumOf {
        val ds = it.filter { c -> c.isDigit() }
        (ds[0].hashCode() - '0'.hashCode()) * 10 + (ds.last().hashCode() - '0'.hashCode())
    }
}

fun solveHard(lines: List<String>): Int {
    val names = listOf("zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine")
    return lines.sumOf {
        val ds = it.indices.mapNotNull { i ->
            if (it[i].isDigit()) {
                return@mapNotNull it[i]
            }
            for ((c, v) in names.withIndex()) {
                if (it.substring(i).startsWith(v)) {
                    return@mapNotNull c.toString()
                }
            }
            return@mapNotNull null
        }
        (ds[0].hashCode() - '0'.hashCode()) * 10 + (ds.last().hashCode() - '0'.hashCode())
    }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}