import java.io.File
import java.util.*

enum class Pulse {
    Low,
    High
}
data class FlipFlop(val type: Char, val to: List<String>, val from: MutableMap<String, Pulse>, var last: Pulse)
data class SignalSend(val from: String, val to: String, val pulse: Pulse)

fun getConfiguration(lines: List<String>): Map<String, FlipFlop> {
    val flops = lines.map { line ->
        val (kindaName, rest) = line.split(" -> ")
        val type = if (kindaName[0] in "%&") kindaName[0] else ')'
        val name = kindaName.drop(if (kindaName[0] in "%&") 1 else 0)
        name to FlipFlop(type, rest.split(", "), mutableMapOf(), Pulse.Low)
    }.toMap()
    flops.forEach { (name, flop) ->
        flop.to.forEach {
            flops[it]?.from?.put(name, Pulse.Low)
        }
    }
    return flops
}

fun sendOnce(flops: Map<String, FlipFlop>, callback: (String, Pulse) -> Unit) {
    val q: Queue<SignalSend> = LinkedList()
    q.add(SignalSend("button", "broadcaster", Pulse.Low))
    fun send(from: String, to: String, pulse: Pulse) {
//            println("$from -$pulse-> $to")
        flops[from]!!.last = pulse
        q.add(SignalSend(from, to, pulse))
    }
    while (q.isNotEmpty()) {
        val (from, flop, inPulse) = q.remove()
        callback(flop, inPulse)
        if (flop !in flops) {
            continue
        }
        val entry = flops[flop]!!
        entry.from[from] = inPulse
        when (entry.type) {
            ')' -> {
                check(flop == "broadcaster")
                entry.to.forEach {
                    send(flop, it, inPulse)
                }
            }
            '%' -> {
                if (inPulse == Pulse.Low) {
                    entry.last = if (entry.last == Pulse.Low) Pulse.High else Pulse.Low
                    entry.to.forEach {
                        send(flop, it, entry.last)
                    }
                }
            }
            '&' -> {
                val outPulse = if (entry.from.all { it.value == Pulse.High }) Pulse.Low else Pulse.High
                entry.to.forEach {
                    send(flop, it, outPulse)
                }
            }
        }
    }
}

fun solveEasy(lines: List<String>): Long {
    val flops = getConfiguration(lines)
    val pulsesSent = mutableMapOf(Pulse.Low to 0, Pulse.High to 0)

    repeat(1000) { sendOnce(flops) { _, pulse -> pulsesSent[pulse] = pulsesSent[pulse]!! + 1 } }
//    println(pulsesSent)
    return pulsesSent.values.fold(1L) { x, y -> x * y }
}

fun gcd(x: Long, y: Long): Long = if (y == 0L) x else gcd(y, x % y)
fun lcm(x: Long, y: Int) = x / gcd(x, y.toLong()) * y

fun solveHard(lines: List<String>): Long {
    val flops = getConfiguration(lines)

    val guys = with(flops.filter { (_, entry) -> "rx" in entry.to }.keys.single()) {
        flops[this]!!.from.keys
    }
    println(guys)

    val m = mutableMapOf<String, Int>()
    var it = 0
    while (m.size < guys.size) {
        it += 1
        sendOnce(flops) { flop, pulse ->
            if (flop in guys && flop !in m && pulse == Pulse.Low) {
                m[flop] = it
            }
        }
    }

    return m.values.fold(1L) { l, x -> lcm(l, x) }
}

fun main() {
    val input = File("src/main/kotlin", "in.in").readLines()
    println(solveEasy(input))
    println(solveHard(input))
}
