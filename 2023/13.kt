import java.io.File

fun List<String>.transpose() = List(this[0].length) { i -> List(this.size) { j -> this[j][i] }.joinToString("") }

fun String.hamming(other: String) = this.zip(other).count { (x, y) -> x != y }

fun solveEasy(lines: List<String>): Int {
    return lines.split("").sumOf { pat ->
        var res = 0
        var cnt = 0
        for (i in 1 until pat.size) {
            if (pat.take(i).reversed().zip(pat.drop(i)).all { (x, y) -> x == y }) {
                res += 100 * i
                cnt += 1
            }
        }
        val pt = pat.transpose()
        for (i in 1 until pt.size) {
            if (pt.take(i).reversed().zip(pt.drop(i)).all { (x, y) -> x == y }) {
                res += i
                cnt += 1
            }
        }
        check(cnt == 1)
        res
    }
}

fun solveHard(lines: List<String>): Int {
    return lines.split("").sumOf { pat ->
        var res = 0
        var cnt = 0
        for (i in 1 until pat.size) {
            if (pat.take(i).reversed().zip(pat.drop(i)).sumOf { (x, y) -> x.hamming(y) } == 1) {
                res += 100 * i
                cnt += 1
            }
        }
        val pt = pat.transpose()
        for (i in 1 until pt.size) {
            if (pt.take(i).reversed().zip(pt.drop(i)).sumOf { (x, y) -> x.hamming(y) } == 1) {
                res += i
                cnt += 1
            }
        }
        check(cnt == 1)
        res
    }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
