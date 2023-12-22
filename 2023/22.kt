import java.io.File
import kotlin.math.*

data class Brick(val x: IntRange, val y: IntRange, val z: IntRange) {
    fun intersectsProjection(other: Brick) = max(x.first, other.x.first) <= min(x.last, other.x.last)
            && max(y.first, other.y.first) <= min(y.last, other.y.last)

    fun fallOn(level: Int) = Brick(x, y, level+1..level+1+z.last-z.first)
}

fun String.parseBrick(): Brick {
    val a = this.split('~').map { it.split(',').map(String::toInt) }
    val rs = a[0].zip(a[1]).map { (x, y) -> x..y }
    return Brick(rs[0], rs[1], rs[2])
}

fun solveEasy(lines: List<String>): Int {
    val a = lines.map { it.parseBrick() }.sortedBy { it.z.first }
    check(a.all { br -> listOf(br.x, br.y, br.z).count { it.first == it.last } >= 2 })
    var badBricks = mutableSetOf<Brick>()
    val fallen = a.fold(listOf<Brick>()) { pile, brick ->
        val mx = pile.filter { it.intersectsProjection(brick) }.maxOfOrNull { it.z.last } ?: 0
        val support = pile.filter { it.intersectsProjection(brick) && it.z.last == mx }
        if (support.size == 1) {
            badBricks.add(support.single())
        }
        pile + brick.fallOn(mx)
    }
    return a.size - badBricks.size
}

fun solveHard(lines: List<String>): Int {
    val a = lines.map { it.parseBrick() }.sortedBy { it.z.first }
    check(a.all { br -> listOf(br.x, br.y, br.z).count { it.first == it.last } >= 2 })
    val fallen = a.fold(listOf<Brick>()) { pile, brick ->
        val mx = pile.filter { it.intersectsProjection(brick) }.maxOfOrNull { it.z.last } ?: 0
        pile + brick.fallOn(mx)
    }
    fun howManyFall(initialPile: List<Brick>): Int {
        var res = 0
        initialPile.fold(listOf<Brick>()) { pile, brick ->
            val mx = pile.filter { it.intersectsProjection(brick) }.maxOfOrNull { it.z.last } ?: 0
            if (mx != brick.z.first - 1) {
                res += 1
            }
            pile + brick.fallOn(mx)
        }
        return res
    }
    return fallen.indices.sumOf { howManyFall(fallen.take(it) + fallen.drop(it + 1)) }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
