fun <T> List<T>.split(predicate: (T) -> Boolean) = (
        listOf(-1) + this.withIndex().filter { predicate(it.value) }.map { it.index } + listOf(this.size)
    ).zipWithNext().map { this.subList(it.first + 1, it.second) }

fun <T> List<T>.split(x: T) = this.split { it == x }

@JvmName("gridDfsT")
fun <T> List<List<T>>.gridDfs(predicate: (T) -> Boolean, action: (Int, Int) -> Unit, newComponent: () -> Unit = {}) {
    val (n, m) = (this.size to this[0].size)
    val dirs = listOf(-1 to 0, 1 to 0, 0 to -1, 0 to 1)
    val used = List(n) { BooleanArray(m) { false } }
    for (i in 0 until n) {
        for (j in 0 until m) {
            if (used[i][j] || !predicate(this[i][j])) {
                continue
            }
            val st = mutableListOf(i to j)
            used[i][j] = true
            newComponent()
            while (st.isNotEmpty()) {
                val (x, y) = st.removeLast()
                action(x, y)
                for ((dx, dy) in dirs) {
                    val (nx, ny) = x + dx to y + dy
                    if (!(0 until n).contains(nx) || !(0 until m).contains(ny)) {
                        continue
                    }
                    if (used[nx][ny] || !predicate(this[nx][ny])) {
                        continue
                    }
                    used[nx][ny] = true
                    st.add(nx to ny)
                }
            }
        }
    }
}

fun List<String>.gridDfs(predicate: (Char) -> Boolean, action: (Int, Int) -> Unit, newComponent: () -> Unit = {}) =
    this.map { it.toList() }.gridDfs(predicate, action, newComponent)