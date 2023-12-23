import java.io.File
import kotlin.math.*

val dirs = listOf(-1 to 0, 1 to 0, 0 to -1, 0 to 1)
val arrows = listOf('^', 'v', '<', '>')

fun pointed(ar: Char, from: Pair<Int, Int>, to: Pair<Int, Int>): Boolean = with(arrows.indexOf(ar)) {
    from.first + dirs[this].first == to.first && from.second + dirs[this].second == to.second
}

fun List<String>.neighbors(x: Int, y: Int, all: Boolean = false) = dirs
    .map { (i, j) -> (x + i to y + j) }
    .filter { (i, j) -> i in this.indices && j in this[i].indices }
    .filter { (i, j) -> this[i][j] == '.' || (this[i][j] != '#' && (all || !pointed(this[i][j], i to j, x to y))) }

fun solveEasy(lines: List<String>): Int {
    val cache = mutableMapOf<Pair<Int, Int>, Int>()
    fun f(x: Int, y: Int): Int {
        if ((x to y) in cache) {
            return cache[x to y]!!
        }
        var (i, j) = x to y
        var prev = x to y
        var len = 0
        while (true) {
            len += 1
            val neigs = lines.neighbors(i, j).filter { it != prev }
            val empties = neigs.filter { (i, j) -> lines[i][j] == '.' }
            check(empties.size < 2)
            if (empties.isEmpty()) {
                break
            }
            if (len > 1) {
                check(empties.size == neigs.size)
            }
            prev = i to j
            i = empties.single().first
            j = empties.single().second
        }
        if (i == lines.size - 1) {
            cache[x to y] = len
            return len
        }
        cache[x to y] = -1
        val arrs = lines.neighbors(i, j).filter { it != prev }.filter { (i, j) -> lines[i][j] != '.' }
        cache[x to y] = len + arrs.maxOf { (i, j) ->
            val idx = arrows.indexOf(lines[i][j])
            1 + f(i + dirs[idx].first, j + dirs[idx].second)
        }
        return cache[x to y]!!
    }
    return f(0, lines[0].indexOf('.')) - 1
}

fun isConnected(lines: List<String>): Boolean {
    val st = mutableListOf(0 to lines[0].indexOf('.'))
    val used = List(lines.size) { BooleanArray(lines[0].length) { false } }
    used[st[0].first][st[0].second] = true
    while (st.isNotEmpty()) {
        val (x, y) = st.removeLast()
        if (x == lines.size - 1) {
            return true
        }
        dirs.forEach { (dx, dy) ->
            val (i, j) = x + dx to y + dy
            if (i !in lines.indices || j !in lines[i].indices) {
                return@forEach
            }
            if (used[i][j] || lines[i][j] == '#') {
                return@forEach
            }
            st.add(i to j)
            used[i][j] = true
        }
    }
    return false
}

fun solveHard(lines: List<String>): Int {
    val comps = mutableListOf<MutableList<Pair<Int, Int>>>()
    lines.gridDfs(
        { _, _ -> true },
        { i, j -> lines[i][j] == '.' },
        { i, j -> comps.last().add(i to j) },
        { comps.add(mutableListOf()) }
    )
    val ids = MutableList(lines.size) { MutableList(lines[0].length) { -1 } }
    comps.filter { it.size == 1 }.map { it[0] }.withIndex().forEach { ids[it.value.first][it.value.second] = it.index }
    val sz = comps.count { it.size == 1 }
    val inc = MutableList(sz) { MutableList(sz) { -1 } }

    fun addEdge(u: Int, v: Int, len: Int) {
//        println("add $u to $v, w = $len")
        if (inc[u][v] < len) {
            inc[u][v] = len
            inc[v][u] = len
        }
    }

    for (sx in lines.indices) {
        for (sy in lines[sx].indices) {
            if (ids[sx][sy] == -1) {
                continue
            }
            lines.neighbors(sx, sy).filter { !pointed(lines[it.first][it.second], it, sx to sy) }.forEach {
                var (x, y) = it
                val idx = arrows.indexOf(lines[x][y])
                x += dirs[idx].first
                y += dirs[idx].second
                var prev = x to y
                var len = 0
                while (true) {
                    len += 1
                    val neigs = lines.neighbors(x, y).filter { lines[it.first][it.second] == '.' }.filter { it != prev }
                    if (neigs.isEmpty()) {
                        break
                    }
                    prev = x to y
                    x = neigs.single().first
                    y = neigs.single().second
                }
                check(len > 1)
                lines.neighbors(x, y).filter { lines[it.first][it.second] !in ".#" }.forEach { (fx, fy) ->
                    val idx = arrows.indexOf(lines[fx][fy])
                    val x = fx + dirs[idx].first
                    val y = fy + dirs[idx].second
                    if (ids[x][y] > -1) {
                        addEdge(ids[sx][sy], ids[x][y], len + 3)
                    }
                }
            }
        }
    }

    val where = (0 until sz).map { i -> inc[i].withIndex().filter { it.value > -1 } }
    var ans = 0
    val used = BooleanArray(sz) { false }
    fun rec(v: Int, finish: Int, cur: Int) {
        if (v == finish) {
            ans = max(ans, cur)
            return
        }
        used[v] = true
        where[v].forEach { (to, w) ->
            if (!used[to]) {
                rec(to, finish, cur + w)
            }
        }
        used[v] = false
    }

    fun getLen(sx: Int, sy: Int, whatToDoWithArrow: (Int, Int) -> Unit = { _, _ -> }): Int {
        var (x, y) = sx to sy
        var prev = sx to sy
        var len = 0
        while (true) {
            len += 1
            val nx = lines.neighbors(x, y).filter { lines[it.first][it.second] == '.' }.filter { it != prev }
            if (nx.isEmpty()) {
                break
            }
            prev = x to y
            x = nx.single().first
            y = nx.single().second
        }
        with (lines.neighbors(x, y, true).filter { it != prev }.single()) {
            whatToDoWithArrow(this.first, this.second)
        }
        return len
    }
    var start = -1
    var finish = -1
    var add = 0
    add += getLen(0, lines[0].indexOf('.')) { x, y ->
        val idx = arrows.indexOf(lines[x][y])
        start = ids[x + dirs[idx].first][y + dirs[idx].second]
    }
    add += getLen(lines.size - 1, lines.last().indexOf('.')) { x, y ->
        val idx = arrows.indexOf(lines[x][y])
        finish = ids[x - dirs[idx].first][y - dirs[idx].second]
    }
    rec(start, finish, 2)
    return ans + add
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
