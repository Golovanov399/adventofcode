import java.io.File

fun getSeqAndTransitions(lines: List<String>): Pair<List<Int>, Map<String, List<String>>> {
    val seq = lines[0].map { if (it == 'L') 0 else 1 }
    val transitions = lines.drop(2).map { line ->
        val (lhs, rhs) = line.split(" = ")
        lhs to (rhs.drop(1).dropLast(1).split(", "))
    }.toMap()
    return seq to transitions
}

fun solveEasy(lines: List<String>): Int {
    val (seq, transitions) = getSeqAndTransitions(lines)

    var ans = 0
    var cur = "AAA"
    var i = 0
    while (cur != "ZZZ") {
        cur = transitions[cur]!![seq[i]]
        i = (i + 1) % seq.size
        ans += 1
    }
    return ans
}

data class PathLenInfo(val prePeriod: Int, val period: Int, val good: List<Int>)

tailrec fun gcd(x: Long, y: Long): Long {
    return if (y == 0L) {
        x
    } else {
        gcd(y, x % y)
    }
}

fun inv(a: Long, b: Long): Long {
    return if (a == 1L) {
        1L
    } else {
        b - inv(b % a, a) * b / a % b
    }
}

fun solveHard(lines: List<String>): Long {
    val (seq, transitions) = getSeqAndTransitions(lines)
    val keys = transitions.keys.toList()
    val where = keys.withIndex().map { it.value to it.index }.toMap()
    val endWithA = keys.filter { it.last() == 'A' }
    val paths = endWithA.map { start ->
        val lastIter = List(transitions.size) { IntArray(seq.size) { -1 } }
        var cur = 0
        var v = where[start]!!
        val good = mutableListOf<Int>()
        while (lastIter[v][cur % seq.size] == -1) {
            lastIter[v][cur % seq.size] = cur
            if (keys[v].last() == 'Z') {
                good.add(cur)
            }
            v = where[transitions[keys[v]]!![seq[cur % seq.size]]]!!
            cur += 1
        }
        PathLenInfo(lastIter[v][cur % seq.size], cur - lastIter[v][cur % seq.size], good)
    }
    check(paths.all { it.good.size == 1 })
    val totalPeriod = paths.fold(1L to 0L) { modRem, path ->
        val newRem = path.good.single().toLong()
        val newMod = path.period.toLong()
        val (mod, rem) = modRem
        val g = gcd(newMod, mod)
        check(rem % g == newRem % g)
        // rem + k * mod = R (mod M)
        // k * mod = R - rem (mod M)
        // k * (mod / g) = (R - rem) / g (mod M / g)
        mod / g * newMod to rem + ((newRem - rem) % (newMod / g) + newMod / g) * inv(mod / g, newMod / g) % (newMod / g) * mod
    }
    check(paths.all { totalPeriod.second % it.period == it.good.single().toLong() % it.period })
    var res = totalPeriod.second
    while (!paths.all { path ->
            if (res < path.prePeriod) {
                res.toInt() in path.good
            } else {
                (res - path.prePeriod) % path.period in path.good.map { x -> ((x.toLong() - path.prePeriod) % path.period + path.period) % path.period }
            }
    }) {
        res += totalPeriod.first
    }
    return res
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
