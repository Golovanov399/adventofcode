import java.io.File

fun String.hash() = this.fold(0) { h, c -> (h + c.hashCode()) * 17 % 256 }

fun solveEasy(lines: List<String>): Int {
    return lines[0].split(',').sumOf { it.hash() }
}

fun solveHard(lines: List<String>): Int {
    val ops = lines[0].split(',')
    val boxes = List(256) { mutableListOf<Pair<String, Int>>() }
    ops.forEach { op ->
        val label = op.takeWhile { it !in "-=" }
        val h = label.hash()
        if ('-' in op) {
            boxes[h].removeIf { it.first == label }
        } else {
            val lens = op.split('=')[1].toInt()
            if (boxes[h].any { it.first == label }) {
                boxes[h].replaceAll { if (it.first == label) label to lens else it }
            } else {
                boxes[h].add(label to lens)
            }
        }
    }
    return boxes.withIndex().sumOf { box ->
        box.value.withIndex().sumOf { (1 + it.index) * it.value.second } * (1 + box.index)
    }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
