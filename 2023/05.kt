import java.io.File

data class MapRange(val src: Long, val dst: Long, val len: Long) {
    fun contains(id: Long) = (src until src + len).contains(id)
    fun dstContains(id: Long) = (dst until dst + len).contains(id)
}

fun getMappings(lines: List<String>): List<List<MapRange>> {
    var lastType = "seed"
    val mappings = lines.split("").drop(1).map { map ->
        val (fromType, toType) = map.first().split(' ').first().split("-to-")
        check(fromType == lastType)
        lastType = toType

        map.drop(1).map { line ->
            val (dst, src, len) = line.split(' ').map(String::toLong)
            MapRange(src, dst, len)
        }.sortedBy { it.src }
    }
    check(lastType == "location")
    return mappings
}

fun solveEasy(lines: List<String>): Long {
    val mappings = getMappings(lines)

    return lines[0].split(' ').drop(1).map(String::toLong).map {
        mappings.fold(it) { id, mapping ->
            for (rng in mapping) {
                if (rng.contains(id)) {
                    return@fold id + (rng.dst - rng.src)
                }
            }
            id
        }
    }.minOrNull()!!
}

fun solveHard(lines: List<String>): Long {
    val mappings = getMappings(lines)
    val inputRanges = lines[0].split(' ').drop(1).map(String::toLong).chunked(2)

    val keyPoints = mappings.reversed().fold(listOf<Long>()) { pts, mapping ->
        (pts.map { x ->
            for (rng in mapping) {
                if (rng.dstContains(x)) {
                    return@map x + (rng.src - rng.dst)
                }
            }
            x
        } + mapping.map { listOf(it.src, it.src + it.len) }.flatten()).toSet().sorted()
    }.filter { x -> inputRanges.any { lst -> (lst[0] until lst[0]+lst[1]).contains(x) } } + inputRanges.map { it[0] }

    return keyPoints.map {
        mappings.fold(it) { id, mapping ->
            for (rng in mapping) {
                if (rng.contains(id)) {
                    return@fold id + (rng.dst - rng.src)
                }
            }
            id
        }
    }.minOrNull()!!
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
