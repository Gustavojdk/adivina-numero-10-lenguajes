import java.awt.Component
import java.awt.Dimension
import java.awt.Font
import javax.swing.Box
import javax.swing.BoxLayout
import javax.swing.JButton
import javax.swing.JFrame
import javax.swing.JLabel
import javax.swing.JPanel
import javax.swing.JTextField
import javax.swing.SwingConstants
import javax.swing.border.EmptyBorder

class GameWindow : JFrame("Adivina el Número") {
    private val game = Game()
    private val guessField = JTextField(10)
    private val guessButton = JButton("Adivinar")
    private val resetButton = JButton("Reiniciar")
    private val resultLabel = JLabel("", SwingConstants.CENTER)
    private val attemptsLabel = JLabel("Intentos: 0")
    private var gameFinished = false

    init {
        configureWindow()
        configureEvents()
    }

    private fun configureWindow() {
        defaultCloseOperation = JFrame.EXIT_ON_CLOSE
        isResizable = false

        val panel = JPanel()
        panel.layout = BoxLayout(panel, BoxLayout.Y_AXIS)
        panel.border = EmptyBorder(20, 24, 20, 24)

        val titleLabel = JLabel("Adivina el Número")
        titleLabel.font = Font("Arial", Font.BOLD, 20)
        titleLabel.alignmentX = Component.CENTER_ALIGNMENT

        val instructionsLabel = JLabel("Adivina un número del 1 al 100")
        instructionsLabel.alignmentX = Component.CENTER_ALIGNMENT

        guessField.horizontalAlignment = JTextField.CENTER
        guessField.maximumSize = Dimension(180, 30)
        guessField.alignmentX = Component.CENTER_ALIGNMENT

        guessButton.alignmentX = Component.CENTER_ALIGNMENT
        resultLabel.preferredSize = Dimension(300, 24)
        resultLabel.alignmentX = Component.CENTER_ALIGNMENT
        attemptsLabel.alignmentX = Component.CENTER_ALIGNMENT
        resetButton.alignmentX = Component.CENTER_ALIGNMENT

        panel.add(titleLabel)
        panel.add(Box.createVerticalStrut(8))
        panel.add(instructionsLabel)
        panel.add(Box.createVerticalStrut(12))
        panel.add(guessField)
        panel.add(Box.createVerticalStrut(10))
        panel.add(guessButton)
        panel.add(Box.createVerticalStrut(12))
        panel.add(resultLabel)
        panel.add(Box.createVerticalStrut(8))
        panel.add(attemptsLabel)
        panel.add(Box.createVerticalStrut(12))
        panel.add(resetButton)

        contentPane = panel
        pack()
        setLocationRelativeTo(null)
    }

    private fun configureEvents() {
        guessButton.addActionListener { submitGuess() }
        guessField.addActionListener { submitGuess() }
        resetButton.addActionListener { resetGame() }
    }

    private fun submitGuess() {
        if (gameFinished) {
            return
        }

        val input = guessField.text.trim()

        if (input.length == 0) {
            resultLabel.text = "Ingresa un número."
            guessField.requestFocusInWindow()
            return
        }

        if (!input.matches(Regex("[+-]?\\d+"))) {
            resultLabel.text = "Ingresa solamente números."
            guessField.requestFocusInWindow()
            return
        }

        val number = input.toIntOrNull()

        if (number == null || number < Game.MIN_NUMBER || number > Game.MAX_NUMBER) {
            resultLabel.text = "El número debe estar entre 1 y 100."
            guessField.requestFocusInWindow()
            return
        }

        val result = game.checkGuess(number)
        resultLabel.text = result
        attemptsLabel.text = "Intentos: ${game.attempts}"

        if (result == "¡Correcto!") {
            gameFinished = true
            guessField.isEnabled = false
            guessButton.isEnabled = false
            return
        }

        guessField.selectAll()
        guessField.requestFocusInWindow()
    }

    private fun resetGame() {
        game.reset()
        gameFinished = false

        guessField.text = ""
        guessField.isEnabled = true
        guessButton.isEnabled = true
        resultLabel.text = ""
        attemptsLabel.text = "Intentos: 0"
        guessField.requestFocusInWindow()
    }
}
