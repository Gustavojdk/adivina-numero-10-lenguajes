import javax.swing.SwingUtilities

fun main() {
    SwingUtilities.invokeLater {
        GameWindow().isVisible = true
    }
}
