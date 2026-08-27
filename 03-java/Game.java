import java.util.Random;

public class Game {
    public static final int MIN_NUMBER = 1;
    public static final int MAX_NUMBER = 100;

    private final Random random;
    private int secretNumber;
    private int attempts;

    public Game() {
        random = new Random();
        reset();
    }

    public String checkGuess(int number) {
        if (number < MIN_NUMBER || number > MAX_NUMBER) {
            throw new IllegalArgumentException("El número debe estar entre 1 y 100.");
        }

        attempts++;

        if (number < secretNumber) {
            return "Muy bajo";
        }

        if (number > secretNumber) {
            return "Muy alto";
        }

        return "¡Correcto!";
    }

    public int getAttempts() {
        return attempts;
    }

    public void reset() {
        secretNumber = random.nextInt(MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER;
        attempts = 0;
    }
}
