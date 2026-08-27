namespace AdivinaNumero;

public sealed class Game
{
    public const int MinNumber = 1;
    public const int MaxNumber = 100;

    private int secretNumber;

    public int Attempts { get; private set; }

    public Game()
    {
        Reset();
    }

    public string CheckGuess(int number)
    {
        if (number < MinNumber || number > MaxNumber)
        {
            throw new ArgumentOutOfRangeException(
                nameof(number),
                "El número debe estar entre 1 y 100."
            );
        }

        Attempts++;

        if (number < secretNumber)
        {
            return "Muy bajo";
        }

        if (number > secretNumber)
        {
            return "Muy alto";
        }

        return "¡Correcto!";
    }

    public void Reset()
    {
        secretNumber = Random.Shared.Next(MinNumber, MaxNumber + 1);
        Attempts = 0;
    }
}
