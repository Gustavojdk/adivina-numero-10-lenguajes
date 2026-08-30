import java.util.Random

/** Mantiene la lógica y el estado de una partida. */
class Game {
    companion object {
        const val MIN_NUMBER = 1
        const val MAX_NUMBER = 100
    }

    private val random = Random()
    private var secretNumber = 0

    var intentos = 0
        private set

    init {
        reiniciar()
    }

    fun comprobarNumero(number: Int): String {
        require(number in MIN_NUMBER..MAX_NUMBER) {
            "El número debe estar entre 1 y 100."
        }

        intentos++

        return when {
            number < secretNumber -> "Muy bajo"
            number > secretNumber -> "Muy alto"
            else -> "¡Correcto!"
        }
    }

    fun reiniciar() {
        secretNumber = random.nextInt(MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER
        intentos = 0
    }
}
