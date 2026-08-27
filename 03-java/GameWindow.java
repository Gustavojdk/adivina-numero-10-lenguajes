import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

public class GameWindow extends JFrame {
    private final Game game;
    private final JTextField guessField;
    private final JButton guessButton;
    private final JLabel resultLabel;
    private final JLabel attemptsLabel;
    private boolean gameFinished;

    public GameWindow() {
        super("Adivina el Número");

        game = new Game();
        guessField = new JTextField(10);
        guessButton = new JButton("Adivinar");
        resultLabel = new JLabel("", SwingConstants.CENTER);
        attemptsLabel = new JLabel("Intentos: 0");
        gameFinished = false;

        configureWindow();
        configureEvents();
    }

    private void configureWindow() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(new EmptyBorder(20, 24, 20, 24));

        JLabel titleLabel = new JLabel("Adivina el Número");
        titleLabel.setFont(new Font("Arial", Font.BOLD, 20));
        titleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JLabel instructionsLabel = new JLabel("Adivina un número del 1 al 100");
        instructionsLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        guessField.setHorizontalAlignment(JTextField.CENTER);
        guessField.setMaximumSize(new Dimension(180, 30));
        guessField.setAlignmentX(Component.CENTER_ALIGNMENT);

        guessButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        resultLabel.setPreferredSize(new Dimension(300, 24));
        resultLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        attemptsLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JButton resetButton = new JButton("Reiniciar");
        resetButton.setAlignmentX(Component.CENTER_ALIGNMENT);

        panel.add(titleLabel);
        panel.add(Box.createVerticalStrut(8));
        panel.add(instructionsLabel);
        panel.add(Box.createVerticalStrut(12));
        panel.add(guessField);
        panel.add(Box.createVerticalStrut(10));
        panel.add(guessButton);
        panel.add(Box.createVerticalStrut(12));
        panel.add(resultLabel);
        panel.add(Box.createVerticalStrut(8));
        panel.add(attemptsLabel);
        panel.add(Box.createVerticalStrut(12));
        panel.add(resetButton);

        setContentPane(panel);
        pack();
        setLocationRelativeTo(null);

        resetButton.addActionListener(event -> resetGame());
    }

    private void configureEvents() {
        guessButton.addActionListener(event -> submitGuess());
        guessField.addActionListener(event -> submitGuess());
    }

    private void submitGuess() {
        if (gameFinished) {
            return;
        }

        String input = guessField.getText().trim();

        if (input.isEmpty()) {
            resultLabel.setText("Ingresa un número.");
            guessField.requestFocusInWindow();
            return;
        }

        if (!input.matches("[+-]?\\d+")) {
            resultLabel.setText("Ingresa solamente números.");
            guessField.requestFocusInWindow();
            return;
        }

        int number;

        try {
            number = Integer.parseInt(input);
        } catch (NumberFormatException error) {
            resultLabel.setText("El número debe estar entre 1 y 100.");
            guessField.requestFocusInWindow();
            return;
        }

        if (number < Game.MIN_NUMBER || number > Game.MAX_NUMBER) {
            resultLabel.setText("El número debe estar entre 1 y 100.");
            guessField.requestFocusInWindow();
            return;
        }

        String result = game.checkGuess(number);
        resultLabel.setText(result);
        attemptsLabel.setText("Intentos: " + game.getAttempts());

        if (result.equals("¡Correcto!")) {
            gameFinished = true;
            guessField.setEnabled(false);
            guessButton.setEnabled(false);
            return;
        }

        guessField.selectAll();
        guessField.requestFocusInWindow();
    }

    private void resetGame() {
        game.reset();
        gameFinished = false;

        guessField.setText("");
        guessField.setEnabled(true);
        guessButton.setEnabled(true);
        resultLabel.setText("");
        attemptsLabel.setText("Intentos: 0");
        guessField.requestFocusInWindow();
    }
}
