fun <T> List<T>.split(x: T): List<List<T>> {
    val cur = mutableListOf<T>()
    val res = mutableListOf<List<T>>()
    for (y in this) {
        if (y == x) {
            res.add(cur.toList())
            cur.clear()
        } else {
            cur.add(y)
        }
    }
    if (cur.isNotEmpty()) {
        res.add(cur.toList())
    }
    return res
}

fun <T> List<T>.split(predicate: (T) -> Boolean): List<List<T>> {
    val cur = mutableListOf<T>()
    val res = mutableListOf<List<T>>()
    for (y in this) {
        if (predicate(y)) {
            res.add(cur.toList())
            cur.clear()
        } else {
            cur.add(y)
        }
    }
    if (cur.isNotEmpty()) {
        res.add(cur.toList())
    }
    return res
}
