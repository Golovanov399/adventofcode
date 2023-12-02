import java.io.File
import kotlin.math.*

val limit = mapOf("red" to 12, "green" to 13, "blue" to 14)

fun solveEasy(lines: List<String>): Int {
    return lines.sumOf { line ->
        if (line.split(": ", "; ").drop(1).all { subline ->
            subline.split(", ").all { s ->
                val (num, col) = s.split(' ')
                num.toInt() <= limit[col]!!
            }
        }) line.split(' ')[1].dropLast(1).toInt() else 0
    }
}

fun solveHard(lines: List<String>): Int {
    return lines.sumOf { line ->
        val cnt = mutableMapOf<String, Int>()
        line.split(": ", "; ").drop(1).forEach { subline ->
            subline.split(", ").forEach { s ->
                val (num, col) = s.split(' ')
                cnt[col] = max(num.toInt(), cnt[col]?:0)
            }
        }
        (cnt["red"]?:0) * (cnt["green"]?:0) * (cnt["blue"]?:0)
    }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}