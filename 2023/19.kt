import java.io.File
import kotlin.math.*

data class Rule(val key: Char, val sign: Int, val thres: Int, val outcome: String)

fun getNextWorkflow(ruleset: List<Rule>, detail: Map<Char, Int>): String {
    for (rule in ruleset) {
        if (rule.key.hashCode() == 0 || (detail[rule.key]!! - rule.thres) * rule.sign > 0) {
            return rule.outcome
        }
    }
    check(false)
    return ""
}

fun getRules(lines: List<String>) = lines.split("").first().map { line ->
    val name = line.takeWhile { it != '{' }
    val ruleset = line.split('{')[1].dropLast(1).split(',').map { check ->
        if (':' !in check) {
            Rule(0.toChar(), 0, 0, check)
        } else {
            Rule(
                check[0],
                if (check[1] == '>') 1 else -1,
                check.drop(2).takeWhile { it != ':' }.toInt(),
                check.split(':').last()
            )
        }
    }
    name to ruleset
}.toMap()

fun solveEasy(lines: List<String>): Int {
    val rules = getRules(lines)

    return lines.split("").last().map { line ->
        line.drop(1).dropLast(1).split(',').map { s -> with(s.split('=')) { this[0].first() to this[1].toInt() } }.toMap()
    }.filter { detail ->
        var workflow = "in"
        while (workflow !in listOf("R", "A")) {
            workflow = getNextWorkflow(rules[workflow]!!, detail)
        }
        workflow == "A"
    }.sumOf { it.values.sum() }
}

const val XMAS = "xmas"
const val MX = 4000

fun IntRange.intersectRanges(other: IntRange): IntRange {
    val l = max(this.first, other.first)
    val r = min(this.last, other.last)
    return if (l <= r) l..r else IntRange.EMPTY
}

fun solveHard(lines: List<String>): Long {
    val rules = getRules(lines)
    val visited = mutableSetOf<String>()
    fun acceptable(wf: String): List<List<IntRange>> {
        if (wf == "A") {
            return listOf(List(4) { 1..MX })
        }
        if (wf == "R") {
            return listOf()
        }
        check(wf !in visited)
        visited.add(wf)
        val cur = MutableList(4) { 1..MX }
        return rules[wf]!!.map { rule ->
            val sub = acceptable(rule.outcome)
            if (rule.key.hashCode() != 0) {
                val thisCondition = cur[XMAS.indexOf(rule.key)].intersectRanges(if (rule.sign > 0) rule.thres+1..MX else 1 until rule.thres)
                val nextCondition = cur[XMAS.indexOf(rule.key)].intersectRanges(if (rule.sign > 0) 1..rule.thres else rule.thres..MX)
                cur[XMAS.indexOf(rule.key)] = thisCondition
                val res = sub.map { it.zip(cur).map { (x, y) -> x.intersectRanges(y) } }.filter { it.all { rng -> !rng.isEmpty() } }
                cur[XMAS.indexOf(rule.key)] = nextCondition
                res
            } else {
                sub.map { it.zip(cur).map { (x, y) -> x.intersectRanges(y) } }.filter { it.all { rng -> !rng.isEmpty() } }
            }
        }.flatten()
    }
    return acceptable("in").sumOf { it.fold(1L) { x, ir -> x * (ir.last - ir.first + 1) } }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
