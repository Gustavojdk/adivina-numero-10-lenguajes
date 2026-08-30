namespace AdivinaNumero;

/// <summary>Contiene la lógica y el estado de una partida.</summary>
public sealed class Game
{
    public const int MinNumber = 1;
    public const int MaxNumber = 100;

    private int secretNumber;

    public int Intentos { get; private set; }

    public Game()
    {
        Reiniciar();
    }

    public string ComprobarNumero(int number)
    {
        if (number < MinNumber || number > MaxNumber)
        {
            throw new ArgumentOutOfRangeException(
                nameof(number),
                "El número debe estar entre 1 y 100."
            );
        }

        Intentos++;

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

    public void Reiniciar()
    {
        secretNumber = Random.Shared.Next(MinNumber, MaxNumber + 1);
        Intentos = 0;
    }
}
