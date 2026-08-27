import java.util.Random

class Game {
    companion object {
        const val MIN_NUMBER = 1
        const val MAX_NUMBER = 100
    }

    private val random = Random()
    private var secretNumber = 0

    var attempts = 0
        private set

    init {
        reset()
    }

    fun checkGuess(number: Int): String {
        require(number in MIN_NUMBER..MAX_NUMBER) {
            "El número debe estar entre 1 y 100."
        }

        attempts++

        return when {
            number < secretNumber -> "Muy bajo"
            number > secretNumber -> "Muy alto"
            else -> "¡Correcto!"
        }
    }

    fun reset() {
        secretNumber = random.nextInt(MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER
        attempts = 0
    }
}
