import java.io.File

fun solveEasy(lines: List<String>): Int {
    return lines[0].indices.sumOf { j ->
        var cur = 0
        var ans = 0
        for (i in lines.indices) {
            if (lines[i][j] == 'O') {
                ans += lines.size - cur
                cur += 1
            } else if (lines[i][j] == '#') {
                cur = i + 1
            }
        }
        ans
    }
}

fun List<String>.tilt(dx: Int, dy: Int): List<String> {
    val res = List(this.size) { i -> this[i].toCharArray() }
    val used = List(this.size) { BooleanArray(this[0].length) { false } }
    for (i in -1..this.size) {
        for (j in -1..this[0].length) {
            if (i in this.indices && j in this[0].indices && (res[i][j] != '#' || used[i][j])) {
                continue
            }
            var (x, y) = (i - dx) to (j - dy)
            var cnt = 0
            while (x in this.indices && y in this[0].indices && res[x][y] != '#') {
                if (res[x][y] == 'O') {
                    cnt += 1
                    res[x][y] = '.'
                }
                used[x][y] = true
                x -= dx
                y -= dy
            }
            x = i
            y = j
            repeat(cnt) {
                x -= dx
                y -= dy
                res[x][y] = 'O'
            }
        }
    }
    return res.map { it.joinToString("") }
}

fun List<String>.cycle(): List<String> = this.tilt(-1, 0).tilt(0, -1).tilt(1, 0).tilt(0, 1)
fun List<String>.score() = indices.sumOf { i -> this[i].count { it == 'O' } * (size - i) }

fun solveHard(lines: List<String>): Int {
    var cur = lines
    val cache = mutableMapOf(cur to 0)
    val iters = 1_000_000_000
    for (it in 1..iters) {
        cur = cur.cycle()
        if (cur in cache) {
            val old = cache[cur]!!
            val period = it - old
            cur = cache.toList().single { p -> p.second == old + (iters - old) % period }.first
            break
        }
        cache[cur] = it
    }
    return cur.score()
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
