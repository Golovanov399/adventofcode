fun <T> List<T>.split(predicate: (T) -> Boolean) = (
        listOf(-1) + this.withIndex().filter { predicate(it.value) }.map { it.index} + listOf(this.size)
    ).zipWithNext().map { this.subList(it.first + 1, it.second) }

fun <T> List<T>.split(x: T) = this.split { it == x }
