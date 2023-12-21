import java.io.File
import java.util.*
import kotlin.math.*

fun findDistances(lines: List<String>, sX: Int, sY: Int) : List<List<Int>> {
    val d = List(lines.size) { MutableList(lines[it].length) { -1 } }
    d[sX][sY] = 0
    val q: Queue<Pair<Int, Int>> = LinkedList()
    q.add(sX to sY)
    while (q.isNotEmpty()) {
        val (x, y) = q.remove()
        for (i in -1..1) {
            for (j in -1..1) {
                if (abs(i) + abs(j) != 1) {
                    continue
                }
                val nx = x + i
                val ny = y + j
                if (nx !in lines.indices || ny !in lines[x].indices) {
                    continue
                }
                if (lines[nx][ny] == '#' || d[nx][ny] != -1) {
                    continue
                }
                d[nx][ny] = d[x][y] + 1
                q.add(nx to ny)
            }
        }
    }
    return d
}

fun solveEasy(lines: List<String>): Int {
    val d = findDistances(lines, lines.indexOfFirst { 'S' in it }, lines.single { 'S' in it }.indexOf('S'))
    val steps = 64
    return d.flatten().filter { it != -1 }.count { it <= steps && it % 2 == steps % 2 }
}

fun solveHard(lines: List<String>): Long {
    val n = lines.size
    val m = lines[0].length

    check(lines[0].all { it == '.' } && lines.last().all { it == '.' } && lines.all { it[0] == '.' && it.last() == '.' })
    check(n == m)
    val sX = lines.indexOfFirst { 'S' in it }
    val sY = lines.single { 'S' in it }.indexOf('S')
    check(2 * sX + 1 == n)
    check(2 * sY + 1 == m)
    val d = findDistances(lines, sX, sY)
    val dUL = findDistances(lines, 0, 0)
    val dUR = findDistances(lines, 0, m - 1)
    val dDL = findDistances(lines, n - 1, 0)
    val dDR = findDistances(lines, n - 1, m - 1)
    val dU = findDistances(lines, 0, sY)
    val dD = findDistances(lines, n - 1, sY)
    val dL = findDistances(lines, sX, 0)
    val dR = findDistances(lines, sX, m - 1)
    val steps = 26501365 // not 596857397105023

    fun f(mx: Int, par: Int): Long {
        if (mx < 0) {
            return 0L
        }
        val x = mx - (mx + par) % 2 + 1
        if (x < 0) {
            return 0L
        }
        return 1L * ((x + 1) / 2) * (x + x - 2 * ((x + 1) / 2 - 1)) / 2
    }

    var ans = d.flatten().count { it != -1 && it <= steps && it % 2 == steps % 2 }.toLong()

    for (i in 0 until n) {
        for (j in 0 until m) {
            if (d[i][j] == -1) {
                continue
            }

            val par = (sX + sY + i + j + steps) % 2

            for (mx in listOf(
                steps - n / 2 - 1 - dD[i][j],
                steps - n / 2 - 1 - dU[i][j],
                steps - n / 2 - 1 - dL[i][j],
                steps - n / 2 - 1 - dR[i][j],
            )) {
                if (mx >= 0) {
                    ans += (mx / n + 1 + par) / 2
                }
            }

            for (mx in listOf(
                (steps - d[0][0] - dDR[i][j] - 2),
                (steps - d[0][m - 1] - dDL[i][j] - 2),
                (steps - d[n - 1][0] - dUR[i][j] - 2),
                (steps - d[n - 1][m - 1] - dUL[i][j] - 2),
            )) {
                if (mx >= 0) {
                    ans += f(mx / n, par)
                }
            }
        }
    }
    return ans
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
