import java.io.File

data class Edge(val to: Int, val idx: Int)

fun solveEasy(lines: List<String>): Int {
    val ids = lines
        .asSequence()
        .map { line -> listOf(line.takeWhile { it != ':' }) + line.split(": ")[1].split(" ") }
        .flatten()
        .toSet()
        .toList()
        .withIndex()
        .map { it.value to it.index }
        .toList()
        .toMap()
    val n = ids.size
    val a = List(n) { mutableListOf<Edge>() }
    var cur = 0
    lines.forEach { line ->
        val (fst, rem) = line.split(": ")
        rem.split(" ").forEach { snd ->
            val u = ids[fst]!!
            val v = ids[snd]!!
            a[u].add(Edge(v, cur))
            a[v].add(Edge(u, cur))
            cur += 1
        }
    }

    val m = cur
    val weight = MutableList(m) { 0L }
    val used = BooleanArray(n) { false }
    var banned = listOf<Int>()
    var sz = 0
    fun dfs(v: Int, pid: Int) {
        used[v] = true
        sz += 1
        for ((to, id) in a[v]) {
            if (id in banned) {
                continue
            }
            if (!used[to]) {
                dfs(to, id)
                weight[id] = a[to].fold(0L) { x, e -> x xor weight[e.idx] }
            } else if (id != pid && weight[id] == 0L) {
                weight[id] = (0..Long.MAX_VALUE).random()
            }
        }
    }
    println("$n, $m")
    dfs(0, -1)
    val byWeight = mutableMapOf<Long, Int>()
    for (i in 0 until m) {
        for (j in 0 until i) {
            val w = weight[i] xor weight[j]
            if (byWeight.getOrDefault(w, m) < j) {
                banned = listOf(i, j, byWeight[w]!!)
            }
        }
        byWeight[weight[i]] = i
    }
    used.fill(false)
    sz = 0
    dfs(0, -1)
    return sz * (n - sz)
}

fun solveHard(lines: List<String>): Long {
    TODO()
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
//    println(solveHard(input))
}
