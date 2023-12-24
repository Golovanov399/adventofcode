import java.io.File
import java.math.BigInteger
import kotlin.math.*

fun sign(x: Long) = if (x < 0) -1 else if (x > 0) 1 else 0

data class Point(val x: Long, val y: Long)

private operator fun Point.minus(other: Point) = Point(this.x - other.x, this.y - other.y)
private operator fun Point.plus(other: Point) = Point(this.x + other.x, this.y + other.y)
private fun Point.cross(other: Point) = this.x * other.y - this.y * other.x

fun Point.onLine(p: Point, q: Point) = (p - this).cross(q - p) == 0L

fun rayIntersectsLine(p: Point, vp: Point, q: Point, vq: Point) =
    !p.onLine(q, q + vq) && sign((q - p).cross(vq)) == sign(vp.cross(vq))

fun intersectionPoint(p: Point, vp: Point, q: Point, vq: Point): Pair<Double, Double> {
    // p + t * vp
    // [p + t * vp - q, vq] = 0
    // t * [vp, vq] = [q - p, vq]
    val t = (q - p).cross(vq).toDouble() / vp.cross(vq)
    return p.x + t * vp.x to p.y + t * vp.y
}

fun solveEasy(lines: List<String>): Int {
    val movingPoints = lines.map { line ->
        val pts = line.split(" @ ")
        pts.map { with (it.split(", ").dropLast(1).map{ x -> x.dropWhile { c -> c == ' ' }.dropLastWhile { c -> c == ' ' }.toLong() }) { Point(this[0], this[1]) } }
    }
//    fun good(x: Double) = x in 7.0..27.0
    fun good(x: Double) = x in 200000000000000.0..400000000000000.0
    return lines.indices.sumOf { i ->
        (0 until i).count { j ->
            val (p, vp) = movingPoints[i]
            val (q, vq) = movingPoints[j]

            if (vp.cross(vq) == 0L) {
                check((p - q).cross(vp) != 0L)
                false
            } else if (rayIntersectsLine(p, vp, q, vq) && rayIntersectsLine(q, vq, p, vp)) {
                val pt = intersectionPoint(p, vp, q, vq)
//                println(pt)
                good(pt.first) && good(pt.second)
            } else {
                false
            }
        }
    }
}

class Fraction(val p: BigInteger, val q: BigInteger) {
    operator fun minus(other: Fraction) = Fraction(p * other.q - q * other.p, q * other.q)
    operator fun plus(other: Fraction) = Fraction(p * other.q + q * other.p, q * other.q)
    operator fun times(other: Fraction) = Fraction(p * other.p, q * other.q)
    operator fun div(other: Fraction) = Fraction(p * other.q, q * other.p)
}

fun solveHard(lines: List<String>): Long {
    val lns = lines.map { line ->
        val pts = line.split(" @ ")
        pts.map { it
            .split(", ")
            .map { x -> x.dropWhile { c -> c == ' ' }.dropLastWhile { c -> c == ' ' }.toLong() }
        }
    }
    val newLines = lns.drop(1).map {
        it.indices.map { j ->
            it[j].zip(lns[0][j]).map { (x, y) -> x - y }
        }
    }
    val (p, vp) = newLines[0]
    val (q, vq) = newLines[1]
    fun project(p: List<Long>) = p.drop(1).map { Fraction(it.toBigInteger(), p[0].toBigInteger()) }
    val pp = project(p)
    val vpp = project(p.zip(vp).map { (x, y) -> x + y }).zip(project(p)).map { (x, y) -> x - y }
    val qq = project(q)
    val vqq = project(q.zip(vq).map { (x, y) -> x + y }).zip(project(q)).map { (x, y) -> x - y }
    val rr = qq.zip(pp).map { (x, y) -> x - y }
    val num = rr[0] * vqq[1] - rr[1] * vqq[0]
    val denom = vpp[0] * vqq[1] - vpp[1] * vqq[0]
    val t = num / denom
    val ip = pp.indices.map { pp[it] + t * vpp[it] }
    val time = newLines.map { (p, vp) ->
        val num = ip[0] * Fraction(p[2].toBigInteger(), BigInteger.ONE) - ip[1] * Fraction(p[1].toBigInteger(), BigInteger.ONE)
        val denom = ip[0] * Fraction(vp[2].toBigInteger(), BigInteger.ONE) - ip[1] * Fraction(vp[1].toBigInteger(), BigInteger.ONE)
        val t = num / denom
        -t.p / t.q
    }.map { it.toLong() }
    val vel = (0 until 3).map { j -> (newLines[1][0][j] + time[1] * newLines[1][1][j] - newLines[0][0][j] - time[0] * newLines[0][1][j]) / (time[1] - time[0]) }
    val start = (0 until 3).map { j -> newLines[0][0][j] + time[0] * newLines[0][1][j] - vel[j] * time[0] }.zip(lns[0][0]).map { (x, y) -> x + y }
    return start.sum()
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
